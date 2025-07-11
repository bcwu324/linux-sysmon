cmake_minimum_required(VERSION 3.10)
project(LinuxSysmon CXX)

set(CMAKE_CXX_STANDARD 17) # 使用 C++17 標準

# 添加可執行文件
add_executable(linux-sysmon src/main.cpp)
