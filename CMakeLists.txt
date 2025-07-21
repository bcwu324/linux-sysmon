cmake_minimum_required(VERSION 3.10)
project(LinuxSysmon CXX)

set(CMAKE_CXX_STANDARD 17)

add_library(meminfo src/meminfo.cpp)
target_include_directories(meminfo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(linux-sysmon src/main.cpp)
target_link_libraries(linux-sysmon PRIVATE meminfo)

# Testing
enable_testing()
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(meminfo_test tests/test_meminfo.cpp)
target_link_libraries(meminfo_test PRIVATE meminfo gtest_main)

include(GoogleTest)
gtest_discover_tests(meminfo_test)
