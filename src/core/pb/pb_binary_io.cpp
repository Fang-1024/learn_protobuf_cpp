#include "pb_binary_io.h"
#include <fstream>
#include <string>
#include <google/protobuf/message.h>
#include "log.h"

namespace learn_pb::pb {
    namespace {
        void SetError(std::string *error_message, const std::string &value) {
            if (error_message != nullptr) {
                *error_message = value;
                LOG_ERROR("%s", value.c_str());
            }
        }
    }

    bool SaveMessageToBinaryFile(const google::protobuf::Message &message, const std::string &file_path,
                                 std::string *error_message) {
        SetError(error_message, "");
        // 用二进制的方式打开文件
        std::ofstream output(file_path, std::ios::binary | std::ios::trunc);
        if (!output.is_open()) {
            SetError(error_message, "failed to open output file: " + file_path);
            return false;
        }

        // 关键动作：把内存中的message对象序列化为protobuf binary
        if (!message.SerializeToOstream(&output)) {
            SetError(error_message, "SerializeToOstream failed for file: " + file_path);
            return false;
        }

        // Serialize 成功并不总能代表底层文件状态一定无问题，
        // 再检查一次流状态，更容易定位 I/O 类错误。
        if (!output.good()) {
            SetError(error_message, "output stream is not in a good state after serialization: " + file_path);
            return false;
        }

        return true;
    }

    bool LoadMessageFromBinaryFile(const std::string &file_path, google::protobuf::Message &message,
                                   std::string *error_message) {
        SetError(error_message, "");

        std::ifstream input(file_path, std::ios::binary);
        if (!input.is_open()) {
            SetError(error_message, "failed to open input file: " + file_path);
            return false;
        }
        // 关键动作：把 protobuf binary 重新解析回“具体类型的 message 对象”。
        // 注意：
        // 这里的 message 必须是调用方已经创建好的具体类型，
        // 比如 tutorial::AddressBook address_book;
        if (!message.ParseFromIstream(&input)) {
            SetError(error_message, "failed to parse input file: " + file_path);
            return false;
        }
        return true;
    }
}
