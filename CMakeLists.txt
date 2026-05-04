cmake_minimum_required(VERSION 3.28)

project(learn_protobuf_cpp LANGUAGES CXX)

# 第一阶段先固定到 C++17。
# 原因：
# 1. 对你当前 gcc 13.3 / CMake 3.28 环境没有压力。
# 2. 足够现代。
# 3. 不把学习重心转移到语言新特性上。
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 导出compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 使用 CMake 的 Protobuf 查找模块。
# 第一阶段这么写通常在 Linux 环境最直接。
find_package(Protobuf CONFIG REQUIRED)

# protoc 编译器是 build-time 生成代码必须具备的。
if (NOT TARGET protobuf::protoc)
    message(FATAL_ERROR "protobuf::protoc target not found. Please install the protobuf compiler (protoc).")
endif ()

message(STATUS "Found Protobuf version: ${Protobuf_VERSION}")
message(STATUS "Using protoc: ${Protobuf_PROTOC_EXECUTABLE}")

add_subdirectory(lib)

# 生成出来的 .pb.h / .pb.cc 不应污染源码树，
# 放到 build/generated 是最清晰的做法。
set(PROTO_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
file(MAKE_DIRECTORY "${PROTO_BINARY_DIR}")

# 当前阶段只有一个 proto，后面阶段你会在这里继续追加。
set(PROTO_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/proto/tutorial/addressbook.proto"
)

# proto_generated：专门承载“由 .proto 生成出来的代码”。
# 这样做的重点不是“炫 target 设计”，而是把 schema 产物和手写代码隔离。
add_library(proto_generated STATIC
        ${PROTO_FILES}
)

# 生成类最终需要链接 protobuf runtime。
target_link_libraries(proto_generated
        PUBLIC
        protobuf::libprotobuf
)

# 生成的头文件位于 build/generated/... 下，
# 所以必须把这个目录暴露给使用者。
target_include_directories(proto_generated
        PUBLIC
        "$<BUILD_INTERFACE:${PROTO_BINARY_DIR}>"
)

# 关键步骤：
# 1. TARGET proto_generated：
#    表示把这个 target 中的 .proto 文件作为输入。
# 2. IMPORT_DIRS 指向 repo/proto：
#    这样生成出来的路径会保留 tutorial/addressbook.pb.h 这种层级。
# 3. PROTOC_OUT_DIR 指向 build/generated：
#    表示生成文件落到构建目录。
protobuf_generate(
        TARGET proto_generated
        IMPORT_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/proto"
        PROTOC_OUT_DIR "${PROTO_BINARY_DIR}"
)

# 你的手写 protobuf 工具层。
add_library(pb_core STATIC
        src/core/pb/pb_binary_io.cpp
)

target_include_directories(pb_core
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(pb_core
        PUBLIC
        protobuf::libprotobuf
        learn_cpp::log
)

# 写消息：构造 message 并写入文件。
add_executable(addressbook_write
        src/apps/addressbook_write_main.cpp
)

target_link_libraries(addressbook_write
        PRIVATE
        pb_core
        proto_generated
)

# 读消息：从文件读回 message 并打印内容。
add_executable(addressbook_read
        src/apps/addressbook_read_main.cpp
)

target_link_libraries(addressbook_read
        PRIVATE
        pb_core
        proto_generated
)
