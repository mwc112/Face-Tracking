include_directories( /usr/local/include/ )
find_package( OpenCV REQUIRED )

add_executable( MainApp MainApp.cpp )
target_link_libraries( MainApp LINK_PUBLIC Tracker WM ${OpenCV_LIBS} )
