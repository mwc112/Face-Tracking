cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "-std=c++11")
project( Demo )
include_directories( /usr/local/include/ )

add_library(WM wm.cpp wm.h)
target_include_directories(WM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

message( WARNING "There is no WM implementation for your system. This will not prevent compilation, instead screens won't focus at runtime" )