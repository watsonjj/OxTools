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
include CMakeFiles/run_simulation.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/run_simulation.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/run_simulation.dir/flags.make

CMakeFiles/run_simulation.dir/src_exe/run_simulation.cpp.o: CMakeFiles/run_simulation.dir/flags.make
CMakeFiles/run_simulation.dir/src_exe/run_simulation.cpp.o: ../src_exe/run_simulation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Jason/Software/OxTools/source/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/run_simulation.dir/src_exe/run_simulation.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/run_simulation.dir/src_exe/run_simulation.cpp.o -c /Users/Jason/Software/OxTools/source/src_exe/run_simulation.cpp

CMakeFiles/run_simulation.dir/src_exe/run_simulation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/run_simulation.dir/src_exe/run_simulation.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Jason/Software/OxTools/source/src_exe/run_simulation.cpp > CMakeFiles/run_simulation.dir/src_exe/run_simulation.cpp.i

CMakeFiles/run_simulation.dir/src_exe/run_simulation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/run_simulation.dir/src_exe/run_simulation.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Jason/Software/OxTools/source/src_exe/run_simulation.cpp -o CMakeFiles/run_simulation.dir/src_exe/run_simulation.cpp.s

CMakeFiles/run_simulation.dir/src_exe/run_simulation.cpp.o.requires:

.PHONY : CMakeFiles/run_simulation.dir/src_exe/run_simulation.cpp.o.requires

CMakeFiles/run_simulation.dir/src_exe/run_simulation.cpp.o.provides: CMakeFiles/run_simulation.dir/src_exe/run_simulation.cpp.o.requires
	$(MAKE) -f CMakeFiles/run_simulation.dir/build.make CMakeFiles/run_simulation.dir/src_exe/run_simulation.cpp.o.provides.build
.PHONY : CMakeFiles/run_simulation.dir/src_exe/run_simulation.cpp.o.provides

CMakeFiles/run_simulation.dir/src_exe/run_simulation.cpp.o.provides.build: CMakeFiles/run_simulation.dir/src_exe/run_simulation.cpp.o


# Object files for target run_simulation
run_simulation_OBJECTS = \
"CMakeFiles/run_simulation.dir/src_exe/run_simulation.cpp.o"

# External object files for target run_simulation
run_simulation_EXTERNAL_OBJECTS =

bin/run_simulation: CMakeFiles/run_simulation.dir/src_exe/run_simulation.cpp.o
bin/run_simulation: CMakeFiles/run_simulation.dir/build.make
bin/run_simulation: lib/libOxTools_LIB.a
bin/run_simulation: /Users/Jason/Software/root-6.06.00/lib/libCore.so
bin/run_simulation: /Users/Jason/Software/root-6.06.00/lib/libRIO.so
bin/run_simulation: /Users/Jason/Software/root-6.06.00/lib/libNet.so
bin/run_simulation: /Users/Jason/Software/root-6.06.00/lib/libHist.so
bin/run_simulation: /Users/Jason/Software/root-6.06.00/lib/libGraf.so
bin/run_simulation: /Users/Jason/Software/root-6.06.00/lib/libGraf3d.so
bin/run_simulation: /Users/Jason/Software/root-6.06.00/lib/libGpad.so
bin/run_simulation: /Users/Jason/Software/root-6.06.00/lib/libTree.so
bin/run_simulation: /Users/Jason/Software/root-6.06.00/lib/libRint.so
bin/run_simulation: /Users/Jason/Software/root-6.06.00/lib/libPostscript.so
bin/run_simulation: /Users/Jason/Software/root-6.06.00/lib/libMatrix.so
bin/run_simulation: /Users/Jason/Software/root-6.06.00/lib/libPhysics.so
bin/run_simulation: /Users/Jason/Software/root-6.06.00/lib/libMathCore.so
bin/run_simulation: /Users/Jason/Software/root-6.06.00/lib/libThread.so
bin/run_simulation: /Users/Jason/Software/root-6.06.00/lib/libMultiProc.so
bin/run_simulation: /usr/local/lib/libboost_regex-mt.a
bin/run_simulation: /usr/local/lib/libboost_filesystem-mt.a
bin/run_simulation: /usr/local/lib/libboost_system-mt.a
bin/run_simulation: CMakeFiles/run_simulation.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Jason/Software/OxTools/source/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/run_simulation"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/run_simulation.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/run_simulation.dir/build: bin/run_simulation

.PHONY : CMakeFiles/run_simulation.dir/build

CMakeFiles/run_simulation.dir/requires: CMakeFiles/run_simulation.dir/src_exe/run_simulation.cpp.o.requires

.PHONY : CMakeFiles/run_simulation.dir/requires

CMakeFiles/run_simulation.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/run_simulation.dir/cmake_clean.cmake
.PHONY : CMakeFiles/run_simulation.dir/clean

CMakeFiles/run_simulation.dir/depend:
	cd /Users/Jason/Software/OxTools/source/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Jason/Software/OxTools/source /Users/Jason/Software/OxTools/source /Users/Jason/Software/OxTools/source/cmake-build-debug /Users/Jason/Software/OxTools/source/cmake-build-debug /Users/Jason/Software/OxTools/source/cmake-build-debug/CMakeFiles/run_simulation.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/run_simulation.dir/depend
