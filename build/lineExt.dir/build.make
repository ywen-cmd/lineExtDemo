# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ywen/code/lineExtDemo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ywen/code/lineExtDemo/build

# Include any dependencies generated for this target.
include CMakeFiles/../lineExt.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/../lineExt.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/../lineExt.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/../lineExt.dir/flags.make

CMakeFiles/../lineExt.dir/src/Algorithm.cpp.o: CMakeFiles/../lineExt.dir/flags.make
CMakeFiles/../lineExt.dir/src/Algorithm.cpp.o: ../src/Algorithm.cpp
CMakeFiles/../lineExt.dir/src/Algorithm.cpp.o: CMakeFiles/../lineExt.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ywen/code/lineExtDemo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/../lineExt.dir/src/Algorithm.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/../lineExt.dir/src/Algorithm.cpp.o -MF CMakeFiles/../lineExt.dir/src/Algorithm.cpp.o.d -o CMakeFiles/../lineExt.dir/src/Algorithm.cpp.o -c /home/ywen/code/lineExtDemo/src/Algorithm.cpp

CMakeFiles/../lineExt.dir/src/Algorithm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/../lineExt.dir/src/Algorithm.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ywen/code/lineExtDemo/src/Algorithm.cpp > CMakeFiles/../lineExt.dir/src/Algorithm.cpp.i

CMakeFiles/../lineExt.dir/src/Algorithm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/../lineExt.dir/src/Algorithm.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ywen/code/lineExtDemo/src/Algorithm.cpp -o CMakeFiles/../lineExt.dir/src/Algorithm.cpp.s

CMakeFiles/../lineExt.dir/src/Cache.cpp.o: CMakeFiles/../lineExt.dir/flags.make
CMakeFiles/../lineExt.dir/src/Cache.cpp.o: ../src/Cache.cpp
CMakeFiles/../lineExt.dir/src/Cache.cpp.o: CMakeFiles/../lineExt.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ywen/code/lineExtDemo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/../lineExt.dir/src/Cache.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/../lineExt.dir/src/Cache.cpp.o -MF CMakeFiles/../lineExt.dir/src/Cache.cpp.o.d -o CMakeFiles/../lineExt.dir/src/Cache.cpp.o -c /home/ywen/code/lineExtDemo/src/Cache.cpp

CMakeFiles/../lineExt.dir/src/Cache.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/../lineExt.dir/src/Cache.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ywen/code/lineExtDemo/src/Cache.cpp > CMakeFiles/../lineExt.dir/src/Cache.cpp.i

CMakeFiles/../lineExt.dir/src/Cache.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/../lineExt.dir/src/Cache.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ywen/code/lineExtDemo/src/Cache.cpp -o CMakeFiles/../lineExt.dir/src/Cache.cpp.s

CMakeFiles/../lineExt.dir/src/main.cpp.o: CMakeFiles/../lineExt.dir/flags.make
CMakeFiles/../lineExt.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/../lineExt.dir/src/main.cpp.o: CMakeFiles/../lineExt.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ywen/code/lineExtDemo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/../lineExt.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/../lineExt.dir/src/main.cpp.o -MF CMakeFiles/../lineExt.dir/src/main.cpp.o.d -o CMakeFiles/../lineExt.dir/src/main.cpp.o -c /home/ywen/code/lineExtDemo/src/main.cpp

CMakeFiles/../lineExt.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/../lineExt.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ywen/code/lineExtDemo/src/main.cpp > CMakeFiles/../lineExt.dir/src/main.cpp.i

CMakeFiles/../lineExt.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/../lineExt.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ywen/code/lineExtDemo/src/main.cpp -o CMakeFiles/../lineExt.dir/src/main.cpp.s

CMakeFiles/../lineExt.dir/src/pch.cpp.o: CMakeFiles/../lineExt.dir/flags.make
CMakeFiles/../lineExt.dir/src/pch.cpp.o: ../src/pch.cpp
CMakeFiles/../lineExt.dir/src/pch.cpp.o: CMakeFiles/../lineExt.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ywen/code/lineExtDemo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/../lineExt.dir/src/pch.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/../lineExt.dir/src/pch.cpp.o -MF CMakeFiles/../lineExt.dir/src/pch.cpp.o.d -o CMakeFiles/../lineExt.dir/src/pch.cpp.o -c /home/ywen/code/lineExtDemo/src/pch.cpp

CMakeFiles/../lineExt.dir/src/pch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/../lineExt.dir/src/pch.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ywen/code/lineExtDemo/src/pch.cpp > CMakeFiles/../lineExt.dir/src/pch.cpp.i

CMakeFiles/../lineExt.dir/src/pch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/../lineExt.dir/src/pch.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ywen/code/lineExtDemo/src/pch.cpp -o CMakeFiles/../lineExt.dir/src/pch.cpp.s

CMakeFiles/../lineExt.dir/src/tool.cpp.o: CMakeFiles/../lineExt.dir/flags.make
CMakeFiles/../lineExt.dir/src/tool.cpp.o: ../src/tool.cpp
CMakeFiles/../lineExt.dir/src/tool.cpp.o: CMakeFiles/../lineExt.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ywen/code/lineExtDemo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/../lineExt.dir/src/tool.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/../lineExt.dir/src/tool.cpp.o -MF CMakeFiles/../lineExt.dir/src/tool.cpp.o.d -o CMakeFiles/../lineExt.dir/src/tool.cpp.o -c /home/ywen/code/lineExtDemo/src/tool.cpp

CMakeFiles/../lineExt.dir/src/tool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/../lineExt.dir/src/tool.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ywen/code/lineExtDemo/src/tool.cpp > CMakeFiles/../lineExt.dir/src/tool.cpp.i

CMakeFiles/../lineExt.dir/src/tool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/../lineExt.dir/src/tool.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ywen/code/lineExtDemo/src/tool.cpp -o CMakeFiles/../lineExt.dir/src/tool.cpp.s

# Object files for target ../lineExt
__/lineExt_OBJECTS = \
"CMakeFiles/../lineExt.dir/src/Algorithm.cpp.o" \
"CMakeFiles/../lineExt.dir/src/Cache.cpp.o" \
"CMakeFiles/../lineExt.dir/src/main.cpp.o" \
"CMakeFiles/../lineExt.dir/src/pch.cpp.o" \
"CMakeFiles/../lineExt.dir/src/tool.cpp.o"

# External object files for target ../lineExt
__/lineExt_EXTERNAL_OBJECTS =

../lineExt: CMakeFiles/../lineExt.dir/src/Algorithm.cpp.o
../lineExt: CMakeFiles/../lineExt.dir/src/Cache.cpp.o
../lineExt: CMakeFiles/../lineExt.dir/src/main.cpp.o
../lineExt: CMakeFiles/../lineExt.dir/src/pch.cpp.o
../lineExt: CMakeFiles/../lineExt.dir/src/tool.cpp.o
../lineExt: CMakeFiles/../lineExt.dir/build.make
../lineExt: CMakeFiles/../lineExt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ywen/code/lineExtDemo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable ../lineExt"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/../lineExt.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/../lineExt.dir/build: ../lineExt
.PHONY : CMakeFiles/../lineExt.dir/build

CMakeFiles/../lineExt.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/../lineExt.dir/cmake_clean.cmake
.PHONY : CMakeFiles/../lineExt.dir/clean

CMakeFiles/../lineExt.dir/depend:
	cd /home/ywen/code/lineExtDemo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ywen/code/lineExtDemo /home/ywen/code/lineExtDemo /home/ywen/code/lineExtDemo/build /home/ywen/code/lineExtDemo/build /home/ywen/code/lineExtDemo/build/lineExt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/../lineExt.dir/depend
