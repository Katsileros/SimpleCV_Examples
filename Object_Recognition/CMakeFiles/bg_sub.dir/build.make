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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/katsi/PANDORA/Object_Recognition/CODE

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/katsi/PANDORA/Object_Recognition/CODE

# Include any dependencies generated for this target.
include CMakeFiles/bg_sub.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bg_sub.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bg_sub.dir/flags.make

CMakeFiles/bg_sub.dir/demo.cpp.o: CMakeFiles/bg_sub.dir/flags.make
CMakeFiles/bg_sub.dir/demo.cpp.o: demo.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/katsi/PANDORA/Object_Recognition/CODE/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/bg_sub.dir/demo.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/bg_sub.dir/demo.cpp.o -c /home/katsi/PANDORA/Object_Recognition/CODE/demo.cpp

CMakeFiles/bg_sub.dir/demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bg_sub.dir/demo.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/katsi/PANDORA/Object_Recognition/CODE/demo.cpp > CMakeFiles/bg_sub.dir/demo.cpp.i

CMakeFiles/bg_sub.dir/demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bg_sub.dir/demo.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/katsi/PANDORA/Object_Recognition/CODE/demo.cpp -o CMakeFiles/bg_sub.dir/demo.cpp.s

CMakeFiles/bg_sub.dir/demo.cpp.o.requires:
.PHONY : CMakeFiles/bg_sub.dir/demo.cpp.o.requires

CMakeFiles/bg_sub.dir/demo.cpp.o.provides: CMakeFiles/bg_sub.dir/demo.cpp.o.requires
	$(MAKE) -f CMakeFiles/bg_sub.dir/build.make CMakeFiles/bg_sub.dir/demo.cpp.o.provides.build
.PHONY : CMakeFiles/bg_sub.dir/demo.cpp.o.provides

CMakeFiles/bg_sub.dir/demo.cpp.o.provides.build: CMakeFiles/bg_sub.dir/demo.cpp.o

# Object files for target bg_sub
bg_sub_OBJECTS = \
"CMakeFiles/bg_sub.dir/demo.cpp.o"

# External object files for target bg_sub
bg_sub_EXTERNAL_OBJECTS =

bg_sub: CMakeFiles/bg_sub.dir/demo.cpp.o
bg_sub: CMakeFiles/bg_sub.dir/build.make
bg_sub: CMakeFiles/bg_sub.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable bg_sub"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bg_sub.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bg_sub.dir/build: bg_sub
.PHONY : CMakeFiles/bg_sub.dir/build

CMakeFiles/bg_sub.dir/requires: CMakeFiles/bg_sub.dir/demo.cpp.o.requires
.PHONY : CMakeFiles/bg_sub.dir/requires

CMakeFiles/bg_sub.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bg_sub.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bg_sub.dir/clean

CMakeFiles/bg_sub.dir/depend:
	cd /home/katsi/PANDORA/Object_Recognition/CODE && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/katsi/PANDORA/Object_Recognition/CODE /home/katsi/PANDORA/Object_Recognition/CODE /home/katsi/PANDORA/Object_Recognition/CODE /home/katsi/PANDORA/Object_Recognition/CODE /home/katsi/PANDORA/Object_Recognition/CODE/CMakeFiles/bg_sub.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bg_sub.dir/depend
