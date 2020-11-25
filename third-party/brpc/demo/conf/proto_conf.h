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
private:
    Msg msg;
};


template <typename Msg>
int Configure<Msg>::load(const std::string& conf_file) {
    using google::protobuf::FieldDescriptor;
    YAML::Node config = YAML::LoadFile(conf_file);
    google::protobuf::Message* message = NULL;
    auto des = msg.GetDescriptor();
    const google::protobuf::Message * prototype = google::protobuf::MessageFactory::generated_factory()->GetPrototype(des);
    if (!prototype) {
        return -1;
    }
    message = prototype->New();
    const google::protobuf::Reflection* ref = message->GetReflection();

    for (int i = 0; i < des->field_count(); ++i) {
        const google::protobuf::FieldDescriptor* field = des->field(i);
        std::string field_name = field->name();
        auto node = config[field->name()];
        const google::protobuf::FieldDescriptor* fdes = des->FindFieldByName(field_name);
        if (field->is_repeated()) {
            if (YAML::NodeType::Sequence == node.Type()) {
                for (auto s: node) {
                    std::cout<<s<<std::endl;
                }
            } else {
                std::cout<<"type error" << std::endl;
            }
        } 
        switch (field->cpp_type()) {
            case google::protobuf::FieldDescriptor::CPPTYPE_ENUM: {
                break;
            }
            case google::protobuf::FieldDescriptor::CPPTYPE_INT32: {
                break;
            }
            case google::protobuf::FieldDescriptor::CPPTYPE_INT64: {
                break;
            }
            case google::protobuf::FieldDescriptor::CPPTYPE_UINT32: {
                break;
            }
            case google::protobuf::FieldDescriptor::CPPTYPE_UINT64: {
                break;
            }
            case google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE: {
                break;
            }
            case google::protobuf::FieldDescriptor::CPPTYPE_FLOAT: {
                break;
            }
            case google::protobuf::FieldDescriptor::CPPTYPE_BOOL: {
                break;
            }
            case google::protobuf::FieldDescriptor::CPPTYPE_STRING: {
                break;
            }
            case google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE: {
                break;
            }
        }
            std::cout<<field->name()<<" "<<node << std::endl;
    }

    return 0;
}

}
