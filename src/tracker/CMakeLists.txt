cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "-std=c++0x")
project( Tracker )
include_directories( /usr/local/include/ )
find_package( OpenCV REQUIRED )


file(GLOB Tracker_SRC "*.h" "*.cpp")

add_definitions ("-Wno-deprecated-register")

include(dlib/dlib/cmake)

add_library(Tracker ${Tracker_SRC})
target_include_directories(Tracker PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Tracker ${OpenCV_LIBS} dlib)

enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(runUnitTests tests.cpp)
target_link_libraries(runUnitTests gtest gtest_main Tracker)
add_test(runUnitTests runUnitTests)
