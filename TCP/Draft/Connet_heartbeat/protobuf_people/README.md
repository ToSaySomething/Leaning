1.protobuf 的proto编译
proto  **.proto --cpp_out=./
加.h

2.tcp+protobuf
protoc  people.proto --cpp_out=./