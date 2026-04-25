#pragma once
#include <string>

namespace google::protobuf {
    class Message;
}

namespace learn_pb::pb {
    // 将任意 protobuf message 序列化为二进制文件。
    // 这里用 Message 基类引用，而不是具体的 AddressBook，
    // 是因为后续所有 generated message 都能复用这一层能力。
    bool SaveMessageToBinaryFile(const google::protobuf::Message &message, const std::string &file_path,
                                 std::string *error_message = nullptr);

    // 从二进制文件中解析 protobuf message。
    // 这里要求调用方先传入一个“具体类型的 message 对象”，
    // 例如 tutorial::AddressBook，然后由 ParseFromIstream() 往里填充内容。
    bool LoadMessageFromBinaryFile(const std::string &file_path, google::protobuf::Message &message,
                                   std::string *error_message = nullptr);
}
