#include "proto_conf.h"
#include <yaml-cpp/yaml.h>
#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
namespace proto_conf {

static int make_field(int cpp_type, const google::protobuf::Reflection* ref, google::protobuf::Message* message, const google::protobuf::FieldDescriptor* fdes, const YAML::Node& node, bool is_repeated=false) {
    if (node.IsNull()) {
        return -1;
    }
#define CASE_FILED(x, y, z) case google::protobuf::FieldDescriptor::CPPTYPE_##x: { \
                                if (is_repeated) { \
                                    ref->Add##y(message, fdes, node.as<z>()); \
                                } else { \
                                    ref->Set##y(message, fdes, node.as<z>()); \
                                } break; \
                            }
    switch(cpp_type) {
        CASE_FILED(ENUM, Int32, int32_t)
        CASE_FILED(INT32, Int32, int32_t)
        CASE_FILED(INT64, Int64, int64_t)
        CASE_FILED(UINT64, UInt64, uint64_t)
        CASE_FILED(UINT32, UInt32, uint32_t)
        CASE_FILED(DOUBLE, Double, double)
        CASE_FILED(FLOAT, Float, float)
        CASE_FILED(STRING, String, std::string)
    }
    return 0;
}

static int yaml_node_to_pb(const YAML::Node& node, google::protobuf::Message* message) {
    if (node.IsNull() || !message) {
        return -1;
    }
    auto des = message->GetDescriptor();
    auto ref = message->GetReflection();
    //for (auto& filed: des->field()) {
    for (int i = 0; i < des->field_count(); ++i) {
        auto field = des->field(i);
        auto& field_name = field->name();
        auto fdes = des->FindFieldByName(field_name);
        if (!fdes) {
            // LOG
            continue;
        }
        auto cpp_type = field->cpp_type();
        if (field->is_repeated()) {
            for (auto n : node[field_name]) {
                if (cpp_type != google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE) {
                    make_field(cpp_type, ref, message, fdes, n, true);
                } else {
                    auto sub_message = ref->AddMessage(message, fdes);
                    yaml_node_to_pb(n, sub_message);
                }
            }
        } else {
            if (cpp_type != google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE) {
                make_field(cpp_type, ref, message, fdes, node[field_name]);
            } else {
                auto sub_message = ref->MutableMessage(message, fdes);
                yaml_node_to_pb(node[field_name], sub_message);
            }
        }
    }
    return 0;
}

int load_yaml_to_pb(const std::string& conf_file, google::protobuf::Message * message) {
    YAML::Node node = YAML::LoadFile(conf_file);
    return yaml_node_to_pb(node, message);

}

} // end of proto_conf
