# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/ubuntu/Documents/repository/MagicBoxWM

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/Documents/repository/MagicBoxWM/build

# Include any dependencies generated for this target.
include CMakeFiles/MagicBoxWM.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MagicBoxWM.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MagicBoxWM.dir/flags.make

CMakeFiles/MagicBoxWM.dir/src/main.cpp.o: CMakeFiles/MagicBoxWM.dir/flags.make
CMakeFiles/MagicBoxWM.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/Documents/repository/MagicBoxWM/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MagicBoxWM.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MagicBoxWM.dir/src/main.cpp.o -c /home/ubuntu/Documents/repository/MagicBoxWM/src/main.cpp

CMakeFiles/MagicBoxWM.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MagicBoxWM.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/Documents/repository/MagicBoxWM/src/main.cpp > CMakeFiles/MagicBoxWM.dir/src/main.cpp.i

CMakeFiles/MagicBoxWM.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MagicBoxWM.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/Documents/repository/MagicBoxWM/src/main.cpp -o CMakeFiles/MagicBoxWM.dir/src/main.cpp.s

CMakeFiles/MagicBoxWM.dir/src/MBWindow.cpp.o: CMakeFiles/MagicBoxWM.dir/flags.make
CMakeFiles/MagicBoxWM.dir/src/MBWindow.cpp.o: ../src/MBWindow.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/Documents/repository/MagicBoxWM/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/MagicBoxWM.dir/src/MBWindow.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MagicBoxWM.dir/src/MBWindow.cpp.o -c /home/ubuntu/Documents/repository/MagicBoxWM/src/MBWindow.cpp

CMakeFiles/MagicBoxWM.dir/src/MBWindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MagicBoxWM.dir/src/MBWindow.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/Documents/repository/MagicBoxWM/src/MBWindow.cpp > CMakeFiles/MagicBoxWM.dir/src/MBWindow.cpp.i

CMakeFiles/MagicBoxWM.dir/src/MBWindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MagicBoxWM.dir/src/MBWindow.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/Documents/repository/MagicBoxWM/src/MBWindow.cpp -o CMakeFiles/MagicBoxWM.dir/src/MBWindow.cpp.s

CMakeFiles/MagicBoxWM.dir/src/MBApp.cpp.o: CMakeFiles/MagicBoxWM.dir/flags.make
CMakeFiles/MagicBoxWM.dir/src/MBApp.cpp.o: ../src/MBApp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/Documents/repository/MagicBoxWM/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/MagicBoxWM.dir/src/MBApp.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MagicBoxWM.dir/src/MBApp.cpp.o -c /home/ubuntu/Documents/repository/MagicBoxWM/src/MBApp.cpp

CMakeFiles/MagicBoxWM.dir/src/MBApp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MagicBoxWM.dir/src/MBApp.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/Documents/repository/MagicBoxWM/src/MBApp.cpp > CMakeFiles/MagicBoxWM.dir/src/MBApp.cpp.i

CMakeFiles/MagicBoxWM.dir/src/MBApp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MagicBoxWM.dir/src/MBApp.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/Documents/repository/MagicBoxWM/src/MBApp.cpp -o CMakeFiles/MagicBoxWM.dir/src/MBApp.cpp.s

# Object files for target MagicBoxWM
MagicBoxWM_OBJECTS = \
"CMakeFiles/MagicBoxWM.dir/src/main.cpp.o" \
"CMakeFiles/MagicBoxWM.dir/src/MBWindow.cpp.o" \
"CMakeFiles/MagicBoxWM.dir/src/MBApp.cpp.o"

# External object files for target MagicBoxWM
MagicBoxWM_EXTERNAL_OBJECTS =

MagicBoxWM: CMakeFiles/MagicBoxWM.dir/src/main.cpp.o
MagicBoxWM: CMakeFiles/MagicBoxWM.dir/src/MBWindow.cpp.o
MagicBoxWM: CMakeFiles/MagicBoxWM.dir/src/MBApp.cpp.o
MagicBoxWM: CMakeFiles/MagicBoxWM.dir/build.make
MagicBoxWM: /usr/lib/x86_64-linux-gnu/libxcb.so
MagicBoxWM: CMakeFiles/MagicBoxWM.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/Documents/repository/MagicBoxWM/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable MagicBoxWM"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MagicBoxWM.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MagicBoxWM.dir/build: MagicBoxWM

.PHONY : CMakeFiles/MagicBoxWM.dir/build

CMakeFiles/MagicBoxWM.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MagicBoxWM.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MagicBoxWM.dir/clean

CMakeFiles/MagicBoxWM.dir/depend:
	cd /home/ubuntu/Documents/repository/MagicBoxWM/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/Documents/repository/MagicBoxWM /home/ubuntu/Documents/repository/MagicBoxWM /home/ubuntu/Documents/repository/MagicBoxWM/build /home/ubuntu/Documents/repository/MagicBoxWM/build /home/ubuntu/Documents/repository/MagicBoxWM/build/CMakeFiles/MagicBoxWM.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MagicBoxWM.dir/depend

