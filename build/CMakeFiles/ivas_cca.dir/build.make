# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /home/willychiang/petalinux/2021.1/xilinx-k26-starterkit-2021.1/images/linux/sdk/sysroots/x86_64-petalinux-linux/usr/bin/cmake

# The command to remove a file.
RM = /home/willychiang/petalinux/2021.1/xilinx-k26-starterkit-2021.1/images/linux/sdk/sysroots/x86_64-petalinux-linux/usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/willychiang/tony-workspace/defect-detect

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/willychiang/tony-workspace/defect-detect/build

# Include any dependencies generated for this target.
include CMakeFiles/ivas_cca.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ivas_cca.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ivas_cca.dir/flags.make

CMakeFiles/ivas_cca.dir/src/ivas_cca.c.o: CMakeFiles/ivas_cca.dir/flags.make
CMakeFiles/ivas_cca.dir/src/ivas_cca.c.o: ../src/ivas_cca.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/willychiang/tony-workspace/defect-detect/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ivas_cca.dir/src/ivas_cca.c.o"
	/home/willychiang/petalinux/2021.1/xilinx-k26-starterkit-2021.1/images/linux/sdk/sysroots/x86_64-petalinux-linux/usr/bin/aarch64-xilinx-linux/aarch64-xilinx-linux-gcc   -mcpu=cortex-a72.cortex-a53 -march=armv8-a+crc -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/home/willychiang/petalinux/2021.1/xilinx-k26-starterkit-2021.1/images/linux/sdk/sysroots/cortexa72-cortexa53-xilinx-linux --sysroot=/home/willychiang/petalinux/2021.1/xilinx-k26-starterkit-2021.1/images/linux/sdk/sysroots/cortexa72-cortexa53-xilinx-linux $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ivas_cca.dir/src/ivas_cca.c.o -c /home/willychiang/tony-workspace/defect-detect/src/ivas_cca.c

CMakeFiles/ivas_cca.dir/src/ivas_cca.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ivas_cca.dir/src/ivas_cca.c.i"
	/home/willychiang/petalinux/2021.1/xilinx-k26-starterkit-2021.1/images/linux/sdk/sysroots/x86_64-petalinux-linux/usr/bin/aarch64-xilinx-linux/aarch64-xilinx-linux-gcc   -mcpu=cortex-a72.cortex-a53 -march=armv8-a+crc -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/home/willychiang/petalinux/2021.1/xilinx-k26-starterkit-2021.1/images/linux/sdk/sysroots/cortexa72-cortexa53-xilinx-linux --sysroot=/home/willychiang/petalinux/2021.1/xilinx-k26-starterkit-2021.1/images/linux/sdk/sysroots/cortexa72-cortexa53-xilinx-linux $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/willychiang/tony-workspace/defect-detect/src/ivas_cca.c > CMakeFiles/ivas_cca.dir/src/ivas_cca.c.i

CMakeFiles/ivas_cca.dir/src/ivas_cca.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ivas_cca.dir/src/ivas_cca.c.s"
	/home/willychiang/petalinux/2021.1/xilinx-k26-starterkit-2021.1/images/linux/sdk/sysroots/x86_64-petalinux-linux/usr/bin/aarch64-xilinx-linux/aarch64-xilinx-linux-gcc   -mcpu=cortex-a72.cortex-a53 -march=armv8-a+crc -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=/home/willychiang/petalinux/2021.1/xilinx-k26-starterkit-2021.1/images/linux/sdk/sysroots/cortexa72-cortexa53-xilinx-linux --sysroot=/home/willychiang/petalinux/2021.1/xilinx-k26-starterkit-2021.1/images/linux/sdk/sysroots/cortexa72-cortexa53-xilinx-linux $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/willychiang/tony-workspace/defect-detect/src/ivas_cca.c -o CMakeFiles/ivas_cca.dir/src/ivas_cca.c.s

# Object files for target ivas_cca
ivas_cca_OBJECTS = \
"CMakeFiles/ivas_cca.dir/src/ivas_cca.c.o"

# External object files for target ivas_cca
ivas_cca_EXTERNAL_OBJECTS =

libivas_cca.so: CMakeFiles/ivas_cca.dir/src/ivas_cca.c.o
libivas_cca.so: CMakeFiles/ivas_cca.dir/build.make
libivas_cca.so: CMakeFiles/ivas_cca.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/willychiang/tony-workspace/defect-detect/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library libivas_cca.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ivas_cca.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ivas_cca.dir/build: libivas_cca.so

.PHONY : CMakeFiles/ivas_cca.dir/build

CMakeFiles/ivas_cca.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ivas_cca.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ivas_cca.dir/clean

CMakeFiles/ivas_cca.dir/depend:
	cd /home/willychiang/tony-workspace/defect-detect/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/willychiang/tony-workspace/defect-detect /home/willychiang/tony-workspace/defect-detect /home/willychiang/tony-workspace/defect-detect/build /home/willychiang/tony-workspace/defect-detect/build /home/willychiang/tony-workspace/defect-detect/build/CMakeFiles/ivas_cca.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ivas_cca.dir/depend

