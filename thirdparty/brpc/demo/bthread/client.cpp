// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

// A client sending requests to server every 1 second.

#include <gflags/gflags.h>
#include <butil/logging.h>
#include <butil/time.h>
#include <brpc/channel.h>
#include <bthread/bthread.h>
#include <iostream>
#include "echo.pb.h"

DEFINE_string(attachment, "", "Carry this along with requests");
DEFINE_string(protocol, "baidu_std", "Protocol type. Defined in src/brpc/options.proto");
DEFINE_string(connection_type, "", "Connection type. Available values: single, pooled, short");
DEFINE_string(server, "0.0.0.0:8000", "IP Address of server");
DEFINE_string(load_balancer, "", "The algorithm for load balancing");
DEFINE_int32(timeout_ms, 100, "RPC timeout in milliseconds");
DEFINE_int32(max_retry, 3, "Max retries(not including the first RPC)"); 
DEFINE_int32(interval_ms, 1000, "Milliseconds between consecutive requests");

template<class Fn, class... Args>
void call_bthread(bthread_t& th, const bthread_attr_t* attr, Fn&& fn, Args&&... args) {
    auto p_wrap_fn = new auto([=]{ fn(args...);   });
    auto call_back = [](void* ar) ->void* {
        auto f = reinterpret_cast<decltype(p_wrap_fn)>(ar);
        (*f)();
        delete f;
        return nullptr;
    };

    bthread_start_background(&th, attr, call_back, p_wrap_fn);
}

class Bthread {
public:
    template<class Fn, class... Args>
    Bthread(const bthread_attr_t* attr, Fn&& fn, Args&&... args) {
        auto p_wrap_fn = new auto([=]{ fn(args...);   });
        auto call_back = [](void* ar) ->void* {
            auto f = reinterpret_cast<decltype(p_wrap_fn)>(ar);
            (*f)();
            delete f;
            return nullptr;
        };

        bthread_start_background(&th_, attr, call_back, (void*)p_wrap_fn);
        joinable_ = true;
    }

    void join() {
        if (joinable_) {
            bthread_join(th_, NULL);
            joinable_ = false;
        }
    }

    bool joinable() const noexcept {
        return joinable_;
    }

    bthread_t get_id() {
        return th_;
    }
private:
    bthread_t th_;
    bool joinable_ = false;
};

void echo (const std::string& xxx) {
    std::cout<<"-------------------------------------------" << std::endl;
    std::cout << xxx << ":" << &xxx << std::endl;
}

int main(int argc, char* argv[]) {
    //Bthread bth(NULL, echo, "abc");
    bthread_t th;
    call_bthread(th, NULL, echo, "abc");
    bthread_join(th, NULL);

    //Bthread bt(echo, "hello world");
    Bthread bt(NULL, echo, "hello world");
    bt.join();
    // Parse gflags. We recommend you to use gflags as well.
    GFLAGS_NS::ParseCommandLineFlags(&argc, &argv, true);
    
    // A Channel represents a communication line to a Server. Notice that 
    // Channel is thread-safe and can be shared by all threads in your program.
    brpc::Channel channel;
    
    // Initialize the channel, NULL means using default options.
    brpc::ChannelOptions options;
    options.protocol = FLAGS_protocol;
    options.connection_type = FLAGS_connection_type;
    options.timeout_ms = FLAGS_timeout_ms/*milliseconds*/;
    options.max_retry = FLAGS_max_retry;
    if (channel.Init(FLAGS_server.c_str(), FLAGS_load_balancer.c_str(), &options) != 0) {
        LOG(ERROR) << "Fail to initialize channel";
        return -1;
    }

    // Normally, you should not call a Channel directly, but instead construct
    // a stub Service wrapping it. stub can be shared by all threads as well.
    example::EchoService_Stub stub(&channel);

    // Send a request and wait for the response every 1 second.
    int log_id = 0;
    while (!brpc::IsAskedToQuit()) {
        // We will receive response synchronously, safe to put variables
        // on stack.
        example::EchoRequest request;
        example::EchoResponse response;
        brpc::Controller cntl;

        request.set_message("hello world");

        cntl.set_log_id(log_id ++);  // set by user
        // Set attachment which is wired to network directly instead of 
        // being serialized into protobuf messages.
        cntl.request_attachment().append(FLAGS_attachment);

        // Because `done'(last parameter) is NULL, this function waits until
        // the response comes back or error occurs(including timedout).
        stub.Echo(&cntl, &request, &response, NULL);
        if (!cntl.Failed()) {
            LOG(INFO) << "Received response from " << cntl.remote_side()
                << " to " << cntl.local_side()
                << ": " << response.message() << " (attached="
                << cntl.response_attachment() << ")"
                << " latency=" << cntl.latency_us() << "us";
        } else {
            LOG(WARNING) << cntl.ErrorText();
        }
        usleep(FLAGS_interval_ms * 1000L);
    }

    LOG(INFO) << "EchoClient is going to quit";
    return 0;
}
