# CMake 最低版本号要求
cmake_minimum_required(VERSION 3.10)

# 项目信息
project(Data_Structure)
set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_COMPILER clang++)

# 指定生成目标
add_executable(Data_Structure main.cpp fibonacci/Fib.cpp fibonacci/Fib.h vector/Vector.h list/ListNode.h list/List.h stack/Stack.h stack/StackUse.cpp stack/StackUse.h)
