# learn_protobuf_cpp

这是一个用于学习 Protobuf 与 C++ 项目结合方式的实战仓库。

当前阶段目标不是覆盖 Protobuf 的全部功能，而是先打通最小闭环：

```text
.proto
  -> protoc / CMake
  -> generated .pb.h / .pb.cc
  -> C++ generated class
  -> SerializeToOstream
  -> binary file
  -> ParseFromIstream
  -> C++ message object