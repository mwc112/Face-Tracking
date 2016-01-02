cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "-std=c++11")
project( Demo )
link_libraries(X11)
include_directories( /usr/local/include/ )

add_library(WM wm.cpp wm.h)


enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_include_directories(WM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(runWmTests tests/tests.cpp)
target_link_libraries(runWmTests gtest gtest_main WM X11)
add_test(runWmTests runWmTests)

