cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "-std=c++11")
set (CMAKE_SHARED_LINKER_FLAGS "-Wl,--as-needed")
project( MainAppParent)

add_subdirectory(lib/googletest/googletest)

find_library(xlib X11)
if(xlib AND NOT APPLE)
	add_subdirectory(wm)
else()
	add_subdirectory(wm-nox11)
endif()

add_subdirectory(tracker)
add_subdirectory(MainApp)

add_custom_target(run cd MainApp && ./MainApp DEPENDS MainApp)