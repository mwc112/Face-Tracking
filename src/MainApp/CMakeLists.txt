include_directories( /usr/local/include/ )
find_package( OpenCV REQUIRED )
file(GLOB Main_SRC "*.h" "*.cpp")

add_executable( MainApp ${Main_SRC} )
target_link_libraries( MainApp LINK_PUBLIC Tracker WM ${OpenCV_LIBS} )
