#include <iostream>
#include <string>

#include <google/protobuf/stubs/common.h>

#include "core/pb/pb_binary_io.h"
#include "tutorial/addressbook.pb.h"

namespace {
    void FillDemoAddressBook(tutorial::AddressBook *address_book) {
        if (address_book == nullptr) {
            return;
        } {
            tutorial::Person *person = address_book->add_people();
            person->set_name("Alice");
            person->set_id(1001);
            person->set_email("alice@example.com");
        } {
            tutorial::Person *person = address_book->add_people();
            person->set_name("Bob");
            person->set_id(1002);
            person->set_email("bob@example.com");
        }
    }

    std::string GetOutputPath(const int argc, char *argv[]) {
        if (argc >= 2) {
            return argv[1];
        }
        return "data/output/addressbook.bin";
    }
}

int main(const int argc, char *argv[]) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    const std::string output_path = GetOutputPath(argc, argv);

    tutorial::AddressBook address_book;
    FillDemoAddressBook(&address_book);

    std::string error_message{};
    if (!learn_pb::pb::SaveMessageToBinaryFile(address_book, output_path, &error_message)) {
        std::cerr << "Failed to write address book. error=" << error_message << '\n';
        google::protobuf::ShutdownProtobufLibrary();
        return EXIT_FAILURE;
    }
    std::cout << "Address book has been written successfully.\n";
    std::cout << "Output file: " << output_path << '\n';
    std::cout << "People count: " << address_book.people_size() << '\n';

    google::protobuf::ShutdownProtobufLibrary();
    return EXIT_SUCCESS;
}
