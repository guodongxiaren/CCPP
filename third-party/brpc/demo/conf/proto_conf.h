#pragma once
#include <string>
#include <iostream>
#include <yaml-cpp/yaml.h>
#include "yaml-cpp/node/parse.h"
#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
namespace proto_conf {

template <typename Msg>
class Configure {
public:
    int load(const std::string& conf_file);

    Msg& instance() {
        return msg;
    }
private:
    Msg msg;
};


template <typename Msg>
int Configure<Msg>::load(const std::string& conf_file) {
    using google::protobuf::FieldDescriptor;
    YAML::Node config = YAML::LoadFile(conf_file);
    google::protobuf::Message* message = &msg;
    auto des = msg.GetDescriptor();
    const google::protobuf::Reflection* ref = msg.GetReflection();

    for (int i = 0; i < des->field_count(); ++i) {
        const google::protobuf::FieldDescriptor* field = des->field(i);
        std::string field_name = field->name();
        auto node = config[field->name()];
        const google::protobuf::FieldDescriptor* fdes = des->FindFieldByName(field_name);
        if (!fdes) {
            continue;
        }
        if (field->is_repeated()) {
            if (YAML::NodeType::Sequence != node.Type()) {
                continue;
            }
            for (auto s: node) {
                std::cout<<s<<std::endl;
            }
        } else {
            switch (field->cpp_type()) {
                case google::protobuf::FieldDescriptor::CPPTYPE_ENUM: {
                    break;
                }
                case google::protobuf::FieldDescriptor::CPPTYPE_INT32: {
                    ref->SetInt32(message, fdes, node.as<int32_t>());
                    break;
                }
                case google::protobuf::FieldDescriptor::CPPTYPE_INT64: {
                    ref->SetInt64(message, fdes, node.as<int64_t>());
                    break;
                }
                case google::protobuf::FieldDescriptor::CPPTYPE_UINT32: {
                    ref->SetUInt32(message, fdes, node.as<uint32_t>());
                    break;
                }
                case google::protobuf::FieldDescriptor::CPPTYPE_UINT64: {
                    ref->SetUInt64(message, fdes, node.as<uint64_t>());
                    break;
                }
                case google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE: {
                    ref->SetDouble(message, fdes, node.as<double>());
                    break;
                }
                case google::protobuf::FieldDescriptor::CPPTYPE_FLOAT: {
                    ref->SetFloat(message, fdes, node.as<float>());
                    break;
                }
                case google::protobuf::FieldDescriptor::CPPTYPE_BOOL: {
                    ref->SetBool(message, fdes, node.as<bool>());
                    break;
                }
                case google::protobuf::FieldDescriptor::CPPTYPE_STRING: {
                    ref->SetString(message, fdes, node.as<std::string>());
                    break;
                }
                case google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE: {
                    break;
                }
            }
        }
        std::cout<<field->name()<<" "<<node << std::endl;
    }

    return 0;
}

}
