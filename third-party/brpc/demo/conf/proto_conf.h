#pragma once
#include <string>
#include <iostream>
#include <yaml-cpp/yaml.h>
#include "yaml-cpp/node/parse.h"
#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
namespace proto_conf {

int load_yaml_to_pb(const std::string& conf_file, google::protobuf::Message * message);

template <typename Msg>
class Configure {
public:
    static Configure& instance() {
        static Configure inst;
        return inst;
    }

    int load(const std::string& conf_file);

    Msg& pb() {
        return _msg;
    }
private:
    Msg _msg;
};


template <typename Msg>
int Configure<Msg>::load(const std::string& conf_file) {
    load_yaml_to_pb(conf_file, &_msg);
    return 0;
}

}
