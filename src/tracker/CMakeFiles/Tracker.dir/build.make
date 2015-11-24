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
include CMakeFiles/Tracker.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Tracker.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Tracker.dir/flags.make

CMakeFiles/Tracker.dir/FeatureTracker.cpp.o: CMakeFiles/Tracker.dir/flags.make
CMakeFiles/Tracker.dir/FeatureTracker.cpp.o: FeatureTracker.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /homes/sx813/EyeTrackWM/src/tracker/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Tracker.dir/FeatureTracker.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Tracker.dir/FeatureTracker.cpp.o -c /homes/sx813/EyeTrackWM/src/tracker/FeatureTracker.cpp

CMakeFiles/Tracker.dir/FeatureTracker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tracker.dir/FeatureTracker.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /homes/sx813/EyeTrackWM/src/tracker/FeatureTracker.cpp > CMakeFiles/Tracker.dir/FeatureTracker.cpp.i

CMakeFiles/Tracker.dir/FeatureTracker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tracker.dir/FeatureTracker.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /homes/sx813/EyeTrackWM/src/tracker/FeatureTracker.cpp -o CMakeFiles/Tracker.dir/FeatureTracker.cpp.s

CMakeFiles/Tracker.dir/FeatureTracker.cpp.o.requires:
.PHONY : CMakeFiles/Tracker.dir/FeatureTracker.cpp.o.requires

CMakeFiles/Tracker.dir/FeatureTracker.cpp.o.provides: CMakeFiles/Tracker.dir/FeatureTracker.cpp.o.requires
	$(MAKE) -f CMakeFiles/Tracker.dir/build.make CMakeFiles/Tracker.dir/FeatureTracker.cpp.o.provides.build
.PHONY : CMakeFiles/Tracker.dir/FeatureTracker.cpp.o.provides

CMakeFiles/Tracker.dir/FeatureTracker.cpp.o.provides.build: CMakeFiles/Tracker.dir/FeatureTracker.cpp.o

CMakeFiles/Tracker.dir/HeadTracker.cpp.o: CMakeFiles/Tracker.dir/flags.make
CMakeFiles/Tracker.dir/HeadTracker.cpp.o: HeadTracker.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /homes/sx813/EyeTrackWM/src/tracker/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Tracker.dir/HeadTracker.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Tracker.dir/HeadTracker.cpp.o -c /homes/sx813/EyeTrackWM/src/tracker/HeadTracker.cpp

CMakeFiles/Tracker.dir/HeadTracker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tracker.dir/HeadTracker.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /homes/sx813/EyeTrackWM/src/tracker/HeadTracker.cpp > CMakeFiles/Tracker.dir/HeadTracker.cpp.i

CMakeFiles/Tracker.dir/HeadTracker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tracker.dir/HeadTracker.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /homes/sx813/EyeTrackWM/src/tracker/HeadTracker.cpp -o CMakeFiles/Tracker.dir/HeadTracker.cpp.s

CMakeFiles/Tracker.dir/HeadTracker.cpp.o.requires:
.PHONY : CMakeFiles/Tracker.dir/HeadTracker.cpp.o.requires

CMakeFiles/Tracker.dir/HeadTracker.cpp.o.provides: CMakeFiles/Tracker.dir/HeadTracker.cpp.o.requires
	$(MAKE) -f CMakeFiles/Tracker.dir/build.make CMakeFiles/Tracker.dir/HeadTracker.cpp.o.provides.build
.PHONY : CMakeFiles/Tracker.dir/HeadTracker.cpp.o.provides

CMakeFiles/Tracker.dir/HeadTracker.cpp.o.provides.build: CMakeFiles/Tracker.dir/HeadTracker.cpp.o

# Object files for target Tracker
Tracker_OBJECTS = \
"CMakeFiles/Tracker.dir/FeatureTracker.cpp.o" \
"CMakeFiles/Tracker.dir/HeadTracker.cpp.o"

# External object files for target Tracker
Tracker_EXTERNAL_OBJECTS =

libTracker.a: CMakeFiles/Tracker.dir/FeatureTracker.cpp.o
libTracker.a: CMakeFiles/Tracker.dir/HeadTracker.cpp.o
libTracker.a: CMakeFiles/Tracker.dir/build.make
libTracker.a: CMakeFiles/Tracker.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libTracker.a"
	$(CMAKE_COMMAND) -P CMakeFiles/Tracker.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Tracker.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Tracker.dir/build: libTracker.a
.PHONY : CMakeFiles/Tracker.dir/build

CMakeFiles/Tracker.dir/requires: CMakeFiles/Tracker.dir/FeatureTracker.cpp.o.requires
CMakeFiles/Tracker.dir/requires: CMakeFiles/Tracker.dir/HeadTracker.cpp.o.requires
.PHONY : CMakeFiles/Tracker.dir/requires

CMakeFiles/Tracker.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Tracker.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Tracker.dir/clean

CMakeFiles/Tracker.dir/depend:
	cd /homes/sx813/EyeTrackWM/src/tracker && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /homes/sx813/EyeTrackWM/src/tracker /homes/sx813/EyeTrackWM/src/tracker /homes/sx813/EyeTrackWM/src/tracker /homes/sx813/EyeTrackWM/src/tracker /homes/sx813/EyeTrackWM/src/tracker/CMakeFiles/Tracker.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Tracker.dir/depend

