# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Jason/Software/OxTools/source

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Jason/Software/OxTools/source/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/plot_pixel_positions.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/plot_pixel_positions.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/plot_pixel_positions.dir/flags.make

CMakeFiles/plot_pixel_positions.dir/src_exe/plot_pixel_positions.cpp.o: CMakeFiles/plot_pixel_positions.dir/flags.make
CMakeFiles/plot_pixel_positions.dir/src_exe/plot_pixel_positions.cpp.o: ../src_exe/plot_pixel_positions.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Jason/Software/OxTools/source/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/plot_pixel_positions.dir/src_exe/plot_pixel_positions.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/plot_pixel_positions.dir/src_exe/plot_pixel_positions.cpp.o -c /Users/Jason/Software/OxTools/source/src_exe/plot_pixel_positions.cpp

CMakeFiles/plot_pixel_positions.dir/src_exe/plot_pixel_positions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/plot_pixel_positions.dir/src_exe/plot_pixel_positions.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Jason/Software/OxTools/source/src_exe/plot_pixel_positions.cpp > CMakeFiles/plot_pixel_positions.dir/src_exe/plot_pixel_positions.cpp.i

CMakeFiles/plot_pixel_positions.dir/src_exe/plot_pixel_positions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/plot_pixel_positions.dir/src_exe/plot_pixel_positions.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Jason/Software/OxTools/source/src_exe/plot_pixel_positions.cpp -o CMakeFiles/plot_pixel_positions.dir/src_exe/plot_pixel_positions.cpp.s

CMakeFiles/plot_pixel_positions.dir/src_exe/plot_pixel_positions.cpp.o.requires:

.PHONY : CMakeFiles/plot_pixel_positions.dir/src_exe/plot_pixel_positions.cpp.o.requires

CMakeFiles/plot_pixel_positions.dir/src_exe/plot_pixel_positions.cpp.o.provides: CMakeFiles/plot_pixel_positions.dir/src_exe/plot_pixel_positions.cpp.o.requires
	$(MAKE) -f CMakeFiles/plot_pixel_positions.dir/build.make CMakeFiles/plot_pixel_positions.dir/src_exe/plot_pixel_positions.cpp.o.provides.build
.PHONY : CMakeFiles/plot_pixel_positions.dir/src_exe/plot_pixel_positions.cpp.o.provides

CMakeFiles/plot_pixel_positions.dir/src_exe/plot_pixel_positions.cpp.o.provides.build: CMakeFiles/plot_pixel_positions.dir/src_exe/plot_pixel_positions.cpp.o


# Object files for target plot_pixel_positions
plot_pixel_positions_OBJECTS = \
"CMakeFiles/plot_pixel_positions.dir/src_exe/plot_pixel_positions.cpp.o"

# External object files for target plot_pixel_positions
plot_pixel_positions_EXTERNAL_OBJECTS =

bin/plot_pixel_positions: CMakeFiles/plot_pixel_positions.dir/src_exe/plot_pixel_positions.cpp.o
bin/plot_pixel_positions: CMakeFiles/plot_pixel_positions.dir/build.make
bin/plot_pixel_positions: lib/libOxTools_LIB.a
bin/plot_pixel_positions: /Users/Jason/Software/root-6.06.00/lib/libCore.so
bin/plot_pixel_positions: /Users/Jason/Software/root-6.06.00/lib/libRIO.so
bin/plot_pixel_positions: /Users/Jason/Software/root-6.06.00/lib/libNet.so
bin/plot_pixel_positions: /Users/Jason/Software/root-6.06.00/lib/libHist.so
bin/plot_pixel_positions: /Users/Jason/Software/root-6.06.00/lib/libGraf.so
bin/plot_pixel_positions: /Users/Jason/Software/root-6.06.00/lib/libGraf3d.so
bin/plot_pixel_positions: /Users/Jason/Software/root-6.06.00/lib/libGpad.so
bin/plot_pixel_positions: /Users/Jason/Software/root-6.06.00/lib/libTree.so
bin/plot_pixel_positions: /Users/Jason/Software/root-6.06.00/lib/libRint.so
bin/plot_pixel_positions: /Users/Jason/Software/root-6.06.00/lib/libPostscript.so
bin/plot_pixel_positions: /Users/Jason/Software/root-6.06.00/lib/libMatrix.so
bin/plot_pixel_positions: /Users/Jason/Software/root-6.06.00/lib/libPhysics.so
bin/plot_pixel_positions: /Users/Jason/Software/root-6.06.00/lib/libMathCore.so
bin/plot_pixel_positions: /Users/Jason/Software/root-6.06.00/lib/libThread.so
bin/plot_pixel_positions: /Users/Jason/Software/root-6.06.00/lib/libMultiProc.so
bin/plot_pixel_positions: /usr/local/lib/libboost_regex-mt.a
bin/plot_pixel_positions: /usr/local/lib/libboost_filesystem-mt.a
bin/plot_pixel_positions: /usr/local/lib/libboost_system-mt.a
bin/plot_pixel_positions: CMakeFiles/plot_pixel_positions.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Jason/Software/OxTools/source/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/plot_pixel_positions"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/plot_pixel_positions.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/plot_pixel_positions.dir/build: bin/plot_pixel_positions

.PHONY : CMakeFiles/plot_pixel_positions.dir/build

CMakeFiles/plot_pixel_positions.dir/requires: CMakeFiles/plot_pixel_positions.dir/src_exe/plot_pixel_positions.cpp.o.requires

.PHONY : CMakeFiles/plot_pixel_positions.dir/requires

CMakeFiles/plot_pixel_positions.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/plot_pixel_positions.dir/cmake_clean.cmake
.PHONY : CMakeFiles/plot_pixel_positions.dir/clean

CMakeFiles/plot_pixel_positions.dir/depend:
	cd /Users/Jason/Software/OxTools/source/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Jason/Software/OxTools/source /Users/Jason/Software/OxTools/source /Users/Jason/Software/OxTools/source/cmake-build-debug /Users/Jason/Software/OxTools/source/cmake-build-debug /Users/Jason/Software/OxTools/source/cmake-build-debug/CMakeFiles/plot_pixel_positions.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/plot_pixel_positions.dir/depend

