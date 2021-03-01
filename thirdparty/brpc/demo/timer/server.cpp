#include <gflags/gflags.h>
#include <brpc/server.h>
#include <bthread/unstable.h>                  // bthread_timer_add
#include <iostream>
#include "echo.pb.h"
using namespace std;

DEFINE_int32(port, 8000, "TCP Port of this server");

class TimerGuard {
    typedef void (*on_timer_t)(void*);
public:
    TimerGuard(on_timer_t timer_func, int interval_s):_timer_func(timer_func), _interval_s(interval_s) {}
    ~TimerGuard() {
        bthread_timer_t timer;
        if (bthread_timer_add(&timer, butil::seconds_from_now(_interval_s),
                              _timer_func, NULL) != 0) {
            cerr << "add timer task failed"<< endl;
        }
    }

private:
    on_timer_t _timer_func;
    int _interval_s; // 定时任务执行间隔，单位秒
};

class EchoServiceImpl : public EchoService {
public:
    EchoServiceImpl() {};
    virtual ~EchoServiceImpl() {};
    virtual void Echo(google::protobuf::RpcController* cntl_base,
                      const EchoRequest* request,
                      EchoResponse* response,
                      google::protobuf::Closure* done) {
        brpc::ClosureGuard done_guard(done);

        response->set_message(request->message());
        done->Run();
    }
};

static void timer_func(void* arg) {
    TimerGuard tg(timer_func, 60);
    cout << "run timer fun:" << time(NULL) << endl;
    // 其他逻辑
    // ...
}

int main() {
    // 先执行一次，然后每分钟执行一次
    timer_func(NULL);

    brpc::Server server;
    EchoServiceImpl echo_service_impl;
    if (server.AddService(&echo_service_impl, 
                          brpc::SERVER_DOESNT_OWN_SERVICE) != 0) {
        cerr << "Fail to add service";
        return -1;
    }
    brpc::ServerOptions options;
    if (server.Start(FLAGS_port, &options) != 0) {
        cerr << "Fail to start EchoServer";
        return -1;
    }

    server.RunUntilAskedToQuit();
    return 0;
}
