# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.26

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\sasha\Desktop\laba\lab3\int

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\sasha\Desktop\laba\lab3\int\build

# Include any dependencies generated for this target.
include CMakeFiles/int.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/int.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/int.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/int.dir/flags.make

CMakeFiles/int.dir/main.cpp.obj: CMakeFiles/int.dir/flags.make
CMakeFiles/int.dir/main.cpp.obj: C:/Users/sasha/Desktop/laba/lab3/int/main.cpp
CMakeFiles/int.dir/main.cpp.obj: CMakeFiles/int.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\sasha\Desktop\laba\lab3\int\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/int.dir/main.cpp.obj"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/int.dir/main.cpp.obj -MF CMakeFiles\int.dir\main.cpp.obj.d -o CMakeFiles\int.dir\main.cpp.obj -c C:\Users\sasha\Desktop\laba\lab3\int\main.cpp

CMakeFiles/int.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/int.dir/main.cpp.i"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\sasha\Desktop\laba\lab3\int\main.cpp > CMakeFiles\int.dir\main.cpp.i

CMakeFiles/int.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/int.dir/main.cpp.s"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\sasha\Desktop\laba\lab3\int\main.cpp -o CMakeFiles\int.dir\main.cpp.s

# Object files for target int
int_OBJECTS = \
"CMakeFiles/int.dir/main.cpp.obj"

# External object files for target int
int_EXTERNAL_OBJECTS =

int.exe: CMakeFiles/int.dir/main.cpp.obj
int.exe: CMakeFiles/int.dir/build.make
int.exe: CMakeFiles/int.dir/linkLibs.rsp
int.exe: CMakeFiles/int.dir/objects1.rsp
int.exe: CMakeFiles/int.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\sasha\Desktop\laba\lab3\int\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable int.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\int.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/int.dir/build: int.exe
.PHONY : CMakeFiles/int.dir/build

CMakeFiles/int.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\int.dir\cmake_clean.cmake
.PHONY : CMakeFiles/int.dir/clean

CMakeFiles/int.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\sasha\Desktop\laba\lab3\int C:\Users\sasha\Desktop\laba\lab3\int C:\Users\sasha\Desktop\laba\lab3\int\build C:\Users\sasha\Desktop\laba\lab3\int\build C:\Users\sasha\Desktop\laba\lab3\int\build\CMakeFiles\int.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/int.dir/depend

