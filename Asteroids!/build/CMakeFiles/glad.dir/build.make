# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.24

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
CMAKE_SOURCE_DIR = C:\Users\wjhea\Desktop\Tulane\CMPS_Masters\Comp_Graphics\Project\final-game-project-moon-patrol\Asteroids!

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\wjhea\Desktop\Tulane\CMPS_Masters\Comp_Graphics\Project\final-game-project-moon-patrol\Asteroids!\build

# Include any dependencies generated for this target.
include CMakeFiles/glad.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/glad.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/glad.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/glad.dir/flags.make

CMakeFiles/glad.dir/glfw-3.3.7/deps/glad_gl.c.obj: CMakeFiles/glad.dir/flags.make
CMakeFiles/glad.dir/glfw-3.3.7/deps/glad_gl.c.obj: CMakeFiles/glad.dir/includes_C.rsp
CMakeFiles/glad.dir/glfw-3.3.7/deps/glad_gl.c.obj: C:/Users/wjhea/Desktop/Tulane/CMPS_Masters/Comp_Graphics/Project/final-game-project-moon-patrol/Asteroids!/glfw-3.3.7/deps/glad_gl.c
CMakeFiles/glad.dir/glfw-3.3.7/deps/glad_gl.c.obj: CMakeFiles/glad.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\wjhea\Desktop\Tulane\CMPS_Masters\Comp_Graphics\Project\final-game-project-moon-patrol\Asteroids!\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/glad.dir/glfw-3.3.7/deps/glad_gl.c.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/glad.dir/glfw-3.3.7/deps/glad_gl.c.obj -MF CMakeFiles\glad.dir\glfw-3.3.7\deps\glad_gl.c.obj.d -o CMakeFiles\glad.dir\glfw-3.3.7\deps\glad_gl.c.obj -c C:\Users\wjhea\Desktop\Tulane\CMPS_Masters\Comp_Graphics\Project\final-game-project-moon-patrol\Asteroids!\glfw-3.3.7\deps\glad_gl.c

CMakeFiles/glad.dir/glfw-3.3.7/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glad.dir/glfw-3.3.7/deps/glad_gl.c.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\wjhea\Desktop\Tulane\CMPS_Masters\Comp_Graphics\Project\final-game-project-moon-patrol\Asteroids!\glfw-3.3.7\deps\glad_gl.c > CMakeFiles\glad.dir\glfw-3.3.7\deps\glad_gl.c.i

CMakeFiles/glad.dir/glfw-3.3.7/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glad.dir/glfw-3.3.7/deps/glad_gl.c.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\wjhea\Desktop\Tulane\CMPS_Masters\Comp_Graphics\Project\final-game-project-moon-patrol\Asteroids!\glfw-3.3.7\deps\glad_gl.c -o CMakeFiles\glad.dir\glfw-3.3.7\deps\glad_gl.c.s

CMakeFiles/glad.dir/glfw-3.3.7/deps/glad_vulkan.c.obj: CMakeFiles/glad.dir/flags.make
CMakeFiles/glad.dir/glfw-3.3.7/deps/glad_vulkan.c.obj: CMakeFiles/glad.dir/includes_C.rsp
CMakeFiles/glad.dir/glfw-3.3.7/deps/glad_vulkan.c.obj: C:/Users/wjhea/Desktop/Tulane/CMPS_Masters/Comp_Graphics/Project/final-game-project-moon-patrol/Asteroids!/glfw-3.3.7/deps/glad_vulkan.c
CMakeFiles/glad.dir/glfw-3.3.7/deps/glad_vulkan.c.obj: CMakeFiles/glad.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\wjhea\Desktop\Tulane\CMPS_Masters\Comp_Graphics\Project\final-game-project-moon-patrol\Asteroids!\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/glad.dir/glfw-3.3.7/deps/glad_vulkan.c.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/glad.dir/glfw-3.3.7/deps/glad_vulkan.c.obj -MF CMakeFiles\glad.dir\glfw-3.3.7\deps\glad_vulkan.c.obj.d -o CMakeFiles\glad.dir\glfw-3.3.7\deps\glad_vulkan.c.obj -c C:\Users\wjhea\Desktop\Tulane\CMPS_Masters\Comp_Graphics\Project\final-game-project-moon-patrol\Asteroids!\glfw-3.3.7\deps\glad_vulkan.c

CMakeFiles/glad.dir/glfw-3.3.7/deps/glad_vulkan.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glad.dir/glfw-3.3.7/deps/glad_vulkan.c.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\wjhea\Desktop\Tulane\CMPS_Masters\Comp_Graphics\Project\final-game-project-moon-patrol\Asteroids!\glfw-3.3.7\deps\glad_vulkan.c > CMakeFiles\glad.dir\glfw-3.3.7\deps\glad_vulkan.c.i

CMakeFiles/glad.dir/glfw-3.3.7/deps/glad_vulkan.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glad.dir/glfw-3.3.7/deps/glad_vulkan.c.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\wjhea\Desktop\Tulane\CMPS_Masters\Comp_Graphics\Project\final-game-project-moon-patrol\Asteroids!\glfw-3.3.7\deps\glad_vulkan.c -o CMakeFiles\glad.dir\glfw-3.3.7\deps\glad_vulkan.c.s

CMakeFiles/glad.dir/glfw-3.3.7/deps/tinycthread.c.obj: CMakeFiles/glad.dir/flags.make
CMakeFiles/glad.dir/glfw-3.3.7/deps/tinycthread.c.obj: CMakeFiles/glad.dir/includes_C.rsp
CMakeFiles/glad.dir/glfw-3.3.7/deps/tinycthread.c.obj: C:/Users/wjhea/Desktop/Tulane/CMPS_Masters/Comp_Graphics/Project/final-game-project-moon-patrol/Asteroids!/glfw-3.3.7/deps/tinycthread.c
CMakeFiles/glad.dir/glfw-3.3.7/deps/tinycthread.c.obj: CMakeFiles/glad.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\wjhea\Desktop\Tulane\CMPS_Masters\Comp_Graphics\Project\final-game-project-moon-patrol\Asteroids!\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/glad.dir/glfw-3.3.7/deps/tinycthread.c.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/glad.dir/glfw-3.3.7/deps/tinycthread.c.obj -MF CMakeFiles\glad.dir\glfw-3.3.7\deps\tinycthread.c.obj.d -o CMakeFiles\glad.dir\glfw-3.3.7\deps\tinycthread.c.obj -c C:\Users\wjhea\Desktop\Tulane\CMPS_Masters\Comp_Graphics\Project\final-game-project-moon-patrol\Asteroids!\glfw-3.3.7\deps\tinycthread.c

CMakeFiles/glad.dir/glfw-3.3.7/deps/tinycthread.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glad.dir/glfw-3.3.7/deps/tinycthread.c.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\wjhea\Desktop\Tulane\CMPS_Masters\Comp_Graphics\Project\final-game-project-moon-patrol\Asteroids!\glfw-3.3.7\deps\tinycthread.c > CMakeFiles\glad.dir\glfw-3.3.7\deps\tinycthread.c.i

CMakeFiles/glad.dir/glfw-3.3.7/deps/tinycthread.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glad.dir/glfw-3.3.7/deps/tinycthread.c.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\wjhea\Desktop\Tulane\CMPS_Masters\Comp_Graphics\Project\final-game-project-moon-patrol\Asteroids!\glfw-3.3.7\deps\tinycthread.c -o CMakeFiles\glad.dir\glfw-3.3.7\deps\tinycthread.c.s

# Object files for target glad
glad_OBJECTS = \
"CMakeFiles/glad.dir/glfw-3.3.7/deps/glad_gl.c.obj" \
"CMakeFiles/glad.dir/glfw-3.3.7/deps/glad_vulkan.c.obj" \
"CMakeFiles/glad.dir/glfw-3.3.7/deps/tinycthread.c.obj"

# External object files for target glad
glad_EXTERNAL_OBJECTS =

libglad.a: CMakeFiles/glad.dir/glfw-3.3.7/deps/glad_gl.c.obj
libglad.a: CMakeFiles/glad.dir/glfw-3.3.7/deps/glad_vulkan.c.obj
libglad.a: CMakeFiles/glad.dir/glfw-3.3.7/deps/tinycthread.c.obj
libglad.a: CMakeFiles/glad.dir/build.make
libglad.a: CMakeFiles/glad.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\wjhea\Desktop\Tulane\CMPS_Masters\Comp_Graphics\Project\final-game-project-moon-patrol\Asteroids!\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C static library libglad.a"
	$(CMAKE_COMMAND) -P CMakeFiles\glad.dir\cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\glad.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/glad.dir/build: libglad.a
.PHONY : CMakeFiles/glad.dir/build

CMakeFiles/glad.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\glad.dir\cmake_clean.cmake
.PHONY : CMakeFiles/glad.dir/clean

CMakeFiles/glad.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\wjhea\Desktop\Tulane\CMPS_Masters\Comp_Graphics\Project\final-game-project-moon-patrol\Asteroids! C:\Users\wjhea\Desktop\Tulane\CMPS_Masters\Comp_Graphics\Project\final-game-project-moon-patrol\Asteroids! C:\Users\wjhea\Desktop\Tulane\CMPS_Masters\Comp_Graphics\Project\final-game-project-moon-patrol\Asteroids!\build C:\Users\wjhea\Desktop\Tulane\CMPS_Masters\Comp_Graphics\Project\final-game-project-moon-patrol\Asteroids!\build C:\Users\wjhea\Desktop\Tulane\CMPS_Masters\Comp_Graphics\Project\final-game-project-moon-patrol\Asteroids!\build\CMakeFiles\glad.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/glad.dir/depend

