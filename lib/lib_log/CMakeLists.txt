# 简单的日志库：log.h / log.cpp
# 工程化要点：
#  - add_library() 定义库目标
#  - PUBLIC/PRIVATE include 路径与链接关系
#  - 别名目标 learn_cpp::log（对外暴露稳定名字）

add_library(lib_log
        log.cpp
)

# 头文件位于当前源目录（即本目录）
# BUILD_INTERFACE：编译本项目时使用的包含路径
# INSTALL_INTERFACE：假如我们安装此库，暴露的安装后包含路径（示例填了一个惯例路径）
target_include_directories(lib_log
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

# 告知使用 C++17 能力
target_compile_features(lib_log PUBLIC cxx_std_17)

# 给库取一个“命名空间别名”，让上层用 learn_cpp::log 来引用
add_library(learn_cpp::log ALIAS lib_log)
