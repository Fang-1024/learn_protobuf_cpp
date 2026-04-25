#include <iostream>
#include <string>
#include <google/protobuf/stubs/common.h>
#include "core/pb/pb_binary_io.h"

std::string GetOutputPath(const int argc, char *argv[]) {
    // 支持命令行覆盖输出路径，避免程序被“当前工作目录”强绑定。
    // 不传参数时，默认写到仓库下的 data/output/addressbook.bin。
    if (argc >= 2) {
        return argv[1];
    }
    return "data/output/addressbook.bin";
}

int main(const int argc, char *argv[]) {
    GOOGLE_PROTOBUF_VERSION;
    const std::string output_path = GetOutputPath(argc, argv);

    return EXIT_SUCCESS;
}
