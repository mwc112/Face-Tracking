cmake_minimum_required(VERSION 2.8)
SET(CMAKE_C_FLAGS "-std=c99")
project( Demo )
include_directories( /usr/local/include/ )

add_library(WM wm.c wm.h)

add_subdirectory(lib/googletest/googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(runUnitTests tests/tests.cpp)
target_link_libraries(runUnitTests gtest gtest_main WM)
add_test(runUnitTests runUnitTests)

