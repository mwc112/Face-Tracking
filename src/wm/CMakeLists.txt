cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "-std=c++11")
project( Demo )
include_directories( /usr/local/include/ )


add_library(WM wm.cpp wm.h)
target_link_libraries(WM X11)
target_include_directories(WM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(runWmTests tests/tests.cpp)
target_link_libraries(runWmTests gtest gtest_main WM)
add_test(runWmTests runWmTests)

