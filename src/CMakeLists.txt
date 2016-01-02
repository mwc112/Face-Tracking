cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "-std=c++11")


project( MainAppParent)

add_subdirectory(lib/googletest/googletest)


add_subdirectory(tracker)
add_subdirectory(MainApp)
