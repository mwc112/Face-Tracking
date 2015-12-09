# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /homes/sx813/EyeTrackWM/src/tracker

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /homes/sx813/EyeTrackWM/src/tracker

# Include any dependencies generated for this target.
include CMakeFiles/Demo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Demo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Demo.dir/flags.make

CMakeFiles/Demo.dir/demo.cpp.o: CMakeFiles/Demo.dir/flags.make
CMakeFiles/Demo.dir/demo.cpp.o: demo.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /homes/sx813/EyeTrackWM/src/tracker/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Demo.dir/demo.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Demo.dir/demo.cpp.o -c /homes/sx813/EyeTrackWM/src/tracker/demo.cpp

CMakeFiles/Demo.dir/demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Demo.dir/demo.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /homes/sx813/EyeTrackWM/src/tracker/demo.cpp > CMakeFiles/Demo.dir/demo.cpp.i

CMakeFiles/Demo.dir/demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Demo.dir/demo.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /homes/sx813/EyeTrackWM/src/tracker/demo.cpp -o CMakeFiles/Demo.dir/demo.cpp.s

CMakeFiles/Demo.dir/demo.cpp.o.requires:
.PHONY : CMakeFiles/Demo.dir/demo.cpp.o.requires

CMakeFiles/Demo.dir/demo.cpp.o.provides: CMakeFiles/Demo.dir/demo.cpp.o.requires
	$(MAKE) -f CMakeFiles/Demo.dir/build.make CMakeFiles/Demo.dir/demo.cpp.o.provides.build
.PHONY : CMakeFiles/Demo.dir/demo.cpp.o.provides

CMakeFiles/Demo.dir/demo.cpp.o.provides.build: CMakeFiles/Demo.dir/demo.cpp.o

# Object files for target Demo
Demo_OBJECTS = \
"CMakeFiles/Demo.dir/demo.cpp.o"

# External object files for target Demo
Demo_EXTERNAL_OBJECTS =

Demo: CMakeFiles/Demo.dir/demo.cpp.o
Demo: CMakeFiles/Demo.dir/build.make
Demo: libTracker.a
Demo: /usr/lib/x86_64-linux-gnu/libopencv_videostab.so.2.4.8
Demo: /usr/lib/x86_64-linux-gnu/libopencv_ts.so.2.4.8
Demo: /usr/lib/x86_64-linux-gnu/libopencv_superres.so.2.4.8
Demo: /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.2.4.8
Demo: /usr/lib/x86_64-linux-gnu/libopencv_ocl.so.2.4.8
Demo: /usr/lib/x86_64-linux-gnu/libopencv_gpu.so.2.4.8
Demo: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.2.4.8
Demo: /usr/lib/x86_64-linux-gnu/libopencv_legacy.so.2.4.8
Demo: /usr/lib/x86_64-linux-gnu/libopencv_contrib.so.2.4.8
Demo: /usr/lib/x86_64-linux-gnu/libopencv_video.so.2.4.8
Demo: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.2.4.8
Demo: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.2.4.8
Demo: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.2.4.8
Demo: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.2.4.8
Demo: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.2.4.8
Demo: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.2.4.8
Demo: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.2.4.8
Demo: /usr/lib/x86_64-linux-gnu/libopencv_core.so.2.4.8
Demo: CMakeFiles/Demo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable Demo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Demo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Demo.dir/build: Demo
.PHONY : CMakeFiles/Demo.dir/build

CMakeFiles/Demo.dir/requires: CMakeFiles/Demo.dir/demo.cpp.o.requires
.PHONY : CMakeFiles/Demo.dir/requires

CMakeFiles/Demo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Demo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Demo.dir/clean

CMakeFiles/Demo.dir/depend:
	cd /homes/sx813/EyeTrackWM/src/tracker && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /homes/sx813/EyeTrackWM/src/tracker /homes/sx813/EyeTrackWM/src/tracker /homes/sx813/EyeTrackWM/src/tracker /homes/sx813/EyeTrackWM/src/tracker /homes/sx813/EyeTrackWM/src/tracker/CMakeFiles/Demo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Demo.dir/depend

