#include <iostream>
#include <string>

#include <google/protobuf/stubs/common.h>

#include "core/pb/pb_binary_io.h"
#include "tutorial/addressbook.pb.h"

namespace {
    std::string GetInputPath(int argc, char *argv[]) {
        if (argc >= 2) {
            return argv[1];
        }
        return "data/output/addressbook.bin";
    }

    void PrintAddressBook(const tutorial::AddressBook &address_book) {
        std::cout << "AddressBook.people_size = " << address_book.people_size() << "\n\n";

        for (int i = 0; i < address_book.people_size(); ++i) {
            // repeated message 的只读访问方式：people(i)
            const tutorial::Person &person = address_book.people(i);

            std::cout << "Person[" << i << "]\n";
            std::cout << "  name  = " << person.name() << '\n';
            std::cout << "  id    = " << person.id() << '\n';
            std::cout << "  email = " << person.email() << '\n';
            std::cout << '\n';
        }
    }
} // namespace

int main(int argc, char *argv[]) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    const std::string input_path = GetInputPath(argc, argv);

    tutorial::AddressBook address_book;
    std::string error_message;
    if (!learn_pb::pb::LoadMessageFromBinaryFile(input_path, address_book, &error_message)) {
        std::cerr << "Failed to read address book. error=" << error_message << '\n';
        google::protobuf::ShutdownProtobufLibrary();
        return 1;
    }

    std::cout << "Address book loaded successfully.\n";
    std::cout << "Input file: " << input_path << "\n\n";

    PrintAddressBook(address_book);

    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
