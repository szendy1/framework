# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ifrag/downloads/szendy/framework/Framework

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ifrag/downloads/szendy/framework/Framework/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/framework.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/framework.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/framework.dir/flags.make

CMakeFiles/framework.dir/main.cpp.o: CMakeFiles/framework.dir/flags.make
CMakeFiles/framework.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ifrag/downloads/szendy/framework/Framework/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/framework.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/framework.dir/main.cpp.o -c /home/ifrag/downloads/szendy/framework/Framework/main.cpp

CMakeFiles/framework.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/framework.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ifrag/downloads/szendy/framework/Framework/main.cpp > CMakeFiles/framework.dir/main.cpp.i

CMakeFiles/framework.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/framework.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ifrag/downloads/szendy/framework/Framework/main.cpp -o CMakeFiles/framework.dir/main.cpp.s

CMakeFiles/framework.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/framework.dir/main.cpp.o.requires

CMakeFiles/framework.dir/main.cpp.o.provides: CMakeFiles/framework.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/framework.dir/build.make CMakeFiles/framework.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/framework.dir/main.cpp.o.provides

CMakeFiles/framework.dir/main.cpp.o.provides.build: CMakeFiles/framework.dir/main.cpp.o


CMakeFiles/framework.dir/src/Node.cpp.o: CMakeFiles/framework.dir/flags.make
CMakeFiles/framework.dir/src/Node.cpp.o: ../src/Node.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ifrag/downloads/szendy/framework/Framework/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/framework.dir/src/Node.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/framework.dir/src/Node.cpp.o -c /home/ifrag/downloads/szendy/framework/Framework/src/Node.cpp

CMakeFiles/framework.dir/src/Node.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/framework.dir/src/Node.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ifrag/downloads/szendy/framework/Framework/src/Node.cpp > CMakeFiles/framework.dir/src/Node.cpp.i

CMakeFiles/framework.dir/src/Node.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/framework.dir/src/Node.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ifrag/downloads/szendy/framework/Framework/src/Node.cpp -o CMakeFiles/framework.dir/src/Node.cpp.s

CMakeFiles/framework.dir/src/Node.cpp.o.requires:

.PHONY : CMakeFiles/framework.dir/src/Node.cpp.o.requires

CMakeFiles/framework.dir/src/Node.cpp.o.provides: CMakeFiles/framework.dir/src/Node.cpp.o.requires
	$(MAKE) -f CMakeFiles/framework.dir/build.make CMakeFiles/framework.dir/src/Node.cpp.o.provides.build
.PHONY : CMakeFiles/framework.dir/src/Node.cpp.o.provides

CMakeFiles/framework.dir/src/Node.cpp.o.provides.build: CMakeFiles/framework.dir/src/Node.cpp.o


CMakeFiles/framework.dir/src/Log.cpp.o: CMakeFiles/framework.dir/flags.make
CMakeFiles/framework.dir/src/Log.cpp.o: ../src/Log.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ifrag/downloads/szendy/framework/Framework/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/framework.dir/src/Log.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/framework.dir/src/Log.cpp.o -c /home/ifrag/downloads/szendy/framework/Framework/src/Log.cpp

CMakeFiles/framework.dir/src/Log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/framework.dir/src/Log.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ifrag/downloads/szendy/framework/Framework/src/Log.cpp > CMakeFiles/framework.dir/src/Log.cpp.i

CMakeFiles/framework.dir/src/Log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/framework.dir/src/Log.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ifrag/downloads/szendy/framework/Framework/src/Log.cpp -o CMakeFiles/framework.dir/src/Log.cpp.s

CMakeFiles/framework.dir/src/Log.cpp.o.requires:

.PHONY : CMakeFiles/framework.dir/src/Log.cpp.o.requires

CMakeFiles/framework.dir/src/Log.cpp.o.provides: CMakeFiles/framework.dir/src/Log.cpp.o.requires
	$(MAKE) -f CMakeFiles/framework.dir/build.make CMakeFiles/framework.dir/src/Log.cpp.o.provides.build
.PHONY : CMakeFiles/framework.dir/src/Log.cpp.o.provides

CMakeFiles/framework.dir/src/Log.cpp.o.provides.build: CMakeFiles/framework.dir/src/Log.cpp.o


CMakeFiles/framework.dir/src/Generation.cpp.o: CMakeFiles/framework.dir/flags.make
CMakeFiles/framework.dir/src/Generation.cpp.o: ../src/Generation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ifrag/downloads/szendy/framework/Framework/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/framework.dir/src/Generation.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/framework.dir/src/Generation.cpp.o -c /home/ifrag/downloads/szendy/framework/Framework/src/Generation.cpp

CMakeFiles/framework.dir/src/Generation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/framework.dir/src/Generation.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ifrag/downloads/szendy/framework/Framework/src/Generation.cpp > CMakeFiles/framework.dir/src/Generation.cpp.i

CMakeFiles/framework.dir/src/Generation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/framework.dir/src/Generation.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ifrag/downloads/szendy/framework/Framework/src/Generation.cpp -o CMakeFiles/framework.dir/src/Generation.cpp.s

CMakeFiles/framework.dir/src/Generation.cpp.o.requires:

.PHONY : CMakeFiles/framework.dir/src/Generation.cpp.o.requires

CMakeFiles/framework.dir/src/Generation.cpp.o.provides: CMakeFiles/framework.dir/src/Generation.cpp.o.requires
	$(MAKE) -f CMakeFiles/framework.dir/build.make CMakeFiles/framework.dir/src/Generation.cpp.o.provides.build
.PHONY : CMakeFiles/framework.dir/src/Generation.cpp.o.provides

CMakeFiles/framework.dir/src/Generation.cpp.o.provides.build: CMakeFiles/framework.dir/src/Generation.cpp.o


CMakeFiles/framework.dir/src/GenProg.cpp.o: CMakeFiles/framework.dir/flags.make
CMakeFiles/framework.dir/src/GenProg.cpp.o: ../src/GenProg.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ifrag/downloads/szendy/framework/Framework/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/framework.dir/src/GenProg.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/framework.dir/src/GenProg.cpp.o -c /home/ifrag/downloads/szendy/framework/Framework/src/GenProg.cpp

CMakeFiles/framework.dir/src/GenProg.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/framework.dir/src/GenProg.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ifrag/downloads/szendy/framework/Framework/src/GenProg.cpp > CMakeFiles/framework.dir/src/GenProg.cpp.i

CMakeFiles/framework.dir/src/GenProg.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/framework.dir/src/GenProg.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ifrag/downloads/szendy/framework/Framework/src/GenProg.cpp -o CMakeFiles/framework.dir/src/GenProg.cpp.s

CMakeFiles/framework.dir/src/GenProg.cpp.o.requires:

.PHONY : CMakeFiles/framework.dir/src/GenProg.cpp.o.requires

CMakeFiles/framework.dir/src/GenProg.cpp.o.provides: CMakeFiles/framework.dir/src/GenProg.cpp.o.requires
	$(MAKE) -f CMakeFiles/framework.dir/build.make CMakeFiles/framework.dir/src/GenProg.cpp.o.provides.build
.PHONY : CMakeFiles/framework.dir/src/GenProg.cpp.o.provides

CMakeFiles/framework.dir/src/GenProg.cpp.o.provides.build: CMakeFiles/framework.dir/src/GenProg.cpp.o


CMakeFiles/framework.dir/src/Func.cpp.o: CMakeFiles/framework.dir/flags.make
CMakeFiles/framework.dir/src/Func.cpp.o: ../src/Func.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ifrag/downloads/szendy/framework/Framework/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/framework.dir/src/Func.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/framework.dir/src/Func.cpp.o -c /home/ifrag/downloads/szendy/framework/Framework/src/Func.cpp

CMakeFiles/framework.dir/src/Func.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/framework.dir/src/Func.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ifrag/downloads/szendy/framework/Framework/src/Func.cpp > CMakeFiles/framework.dir/src/Func.cpp.i

CMakeFiles/framework.dir/src/Func.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/framework.dir/src/Func.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ifrag/downloads/szendy/framework/Framework/src/Func.cpp -o CMakeFiles/framework.dir/src/Func.cpp.s

CMakeFiles/framework.dir/src/Func.cpp.o.requires:

.PHONY : CMakeFiles/framework.dir/src/Func.cpp.o.requires

CMakeFiles/framework.dir/src/Func.cpp.o.provides: CMakeFiles/framework.dir/src/Func.cpp.o.requires
	$(MAKE) -f CMakeFiles/framework.dir/build.make CMakeFiles/framework.dir/src/Func.cpp.o.provides.build
.PHONY : CMakeFiles/framework.dir/src/Func.cpp.o.provides

CMakeFiles/framework.dir/src/Func.cpp.o.provides.build: CMakeFiles/framework.dir/src/Func.cpp.o


# Object files for target framework
framework_OBJECTS = \
"CMakeFiles/framework.dir/main.cpp.o" \
"CMakeFiles/framework.dir/src/Node.cpp.o" \
"CMakeFiles/framework.dir/src/Log.cpp.o" \
"CMakeFiles/framework.dir/src/Generation.cpp.o" \
"CMakeFiles/framework.dir/src/GenProg.cpp.o" \
"CMakeFiles/framework.dir/src/Func.cpp.o"

# External object files for target framework
framework_EXTERNAL_OBJECTS =

libframework.so: CMakeFiles/framework.dir/main.cpp.o
libframework.so: CMakeFiles/framework.dir/src/Node.cpp.o
libframework.so: CMakeFiles/framework.dir/src/Log.cpp.o
libframework.so: CMakeFiles/framework.dir/src/Generation.cpp.o
libframework.so: CMakeFiles/framework.dir/src/GenProg.cpp.o
libframework.so: CMakeFiles/framework.dir/src/Func.cpp.o
libframework.so: CMakeFiles/framework.dir/build.make
libframework.so: CMakeFiles/framework.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ifrag/downloads/szendy/framework/Framework/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX shared library libframework.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/framework.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/framework.dir/build: libframework.so

.PHONY : CMakeFiles/framework.dir/build

CMakeFiles/framework.dir/requires: CMakeFiles/framework.dir/main.cpp.o.requires
CMakeFiles/framework.dir/requires: CMakeFiles/framework.dir/src/Node.cpp.o.requires
CMakeFiles/framework.dir/requires: CMakeFiles/framework.dir/src/Log.cpp.o.requires
CMakeFiles/framework.dir/requires: CMakeFiles/framework.dir/src/Generation.cpp.o.requires
CMakeFiles/framework.dir/requires: CMakeFiles/framework.dir/src/GenProg.cpp.o.requires
CMakeFiles/framework.dir/requires: CMakeFiles/framework.dir/src/Func.cpp.o.requires

.PHONY : CMakeFiles/framework.dir/requires

CMakeFiles/framework.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/framework.dir/cmake_clean.cmake
.PHONY : CMakeFiles/framework.dir/clean

CMakeFiles/framework.dir/depend:
	cd /home/ifrag/downloads/szendy/framework/Framework/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ifrag/downloads/szendy/framework/Framework /home/ifrag/downloads/szendy/framework/Framework /home/ifrag/downloads/szendy/framework/Framework/cmake-build-debug /home/ifrag/downloads/szendy/framework/Framework/cmake-build-debug /home/ifrag/downloads/szendy/framework/Framework/cmake-build-debug/CMakeFiles/framework.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/framework.dir/depend

