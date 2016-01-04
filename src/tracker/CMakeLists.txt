cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "-std=c++11")
project( Tracker )
include_directories( /usr/local/include/ )
find_package( OpenCV REQUIRED )


file(GLOB Tracker_SRC "*.h" "*.cpp")

#needed because image lib's used by dlib output this warning a lot
add_definitions ("-Wno-deprecated-register")

#needed to work on lab machines because http://intel.ly/15OrBec
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--no-as-needed")

#we don't need GUI support from dlib
set(DLIB_NO_GUI_SUPPORT 1)

#makes face detection run faster
set(USE_SSE4_INSTRUCTIONS 1)

include(dlib/dlib/cmake)

add_library(Tracker ${Tracker_SRC})
target_include_directories(Tracker PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Tracker ${OpenCV_LIBS} dlib)

enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(runUnitTests tests.cpp)
target_link_libraries(runUnitTests gtest gtest_main Tracker)
add_test(runUnitTests runUnitTests)
