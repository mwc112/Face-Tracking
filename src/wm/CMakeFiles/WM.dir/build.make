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
CMAKE_SOURCE_DIR = /homes/sx813/EyeTrackWM/src/wm

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /homes/sx813/EyeTrackWM/src/wm

# Include any dependencies generated for this target.
include CMakeFiles/WM.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/WM.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/WM.dir/flags.make

CMakeFiles/WM.dir/wm.c.o: CMakeFiles/WM.dir/flags.make
CMakeFiles/WM.dir/wm.c.o: wm.c
	$(CMAKE_COMMAND) -E cmake_progress_report /homes/sx813/EyeTrackWM/src/wm/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/WM.dir/wm.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/WM.dir/wm.c.o   -c /homes/sx813/EyeTrackWM/src/wm/wm.c

CMakeFiles/WM.dir/wm.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/WM.dir/wm.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /homes/sx813/EyeTrackWM/src/wm/wm.c > CMakeFiles/WM.dir/wm.c.i

CMakeFiles/WM.dir/wm.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/WM.dir/wm.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /homes/sx813/EyeTrackWM/src/wm/wm.c -o CMakeFiles/WM.dir/wm.c.s

CMakeFiles/WM.dir/wm.c.o.requires:
.PHONY : CMakeFiles/WM.dir/wm.c.o.requires

CMakeFiles/WM.dir/wm.c.o.provides: CMakeFiles/WM.dir/wm.c.o.requires
	$(MAKE) -f CMakeFiles/WM.dir/build.make CMakeFiles/WM.dir/wm.c.o.provides.build
.PHONY : CMakeFiles/WM.dir/wm.c.o.provides

CMakeFiles/WM.dir/wm.c.o.provides.build: CMakeFiles/WM.dir/wm.c.o

# Object files for target WM
WM_OBJECTS = \
"CMakeFiles/WM.dir/wm.c.o"

# External object files for target WM
WM_EXTERNAL_OBJECTS =

libWM.a: CMakeFiles/WM.dir/wm.c.o
libWM.a: CMakeFiles/WM.dir/build.make
libWM.a: CMakeFiles/WM.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C static library libWM.a"
	$(CMAKE_COMMAND) -P CMakeFiles/WM.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/WM.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/WM.dir/build: libWM.a
.PHONY : CMakeFiles/WM.dir/build

CMakeFiles/WM.dir/requires: CMakeFiles/WM.dir/wm.c.o.requires
.PHONY : CMakeFiles/WM.dir/requires

CMakeFiles/WM.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/WM.dir/cmake_clean.cmake
.PHONY : CMakeFiles/WM.dir/clean

CMakeFiles/WM.dir/depend:
	cd /homes/sx813/EyeTrackWM/src/wm && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /homes/sx813/EyeTrackWM/src/wm /homes/sx813/EyeTrackWM/src/wm /homes/sx813/EyeTrackWM/src/wm /homes/sx813/EyeTrackWM/src/wm /homes/sx813/EyeTrackWM/src/wm/CMakeFiles/WM.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/WM.dir/depend

