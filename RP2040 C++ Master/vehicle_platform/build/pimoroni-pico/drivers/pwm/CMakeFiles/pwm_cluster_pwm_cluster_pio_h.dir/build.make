# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.26.4/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.26.4/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/m1/Documents/C++/pico/vehicle_platform

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/m1/Documents/C++/pico/vehicle_platform/build

# Utility rule file for pwm_cluster_pwm_cluster_pio_h.

# Include any custom commands dependencies for this target.
include pimoroni-pico/drivers/pwm/CMakeFiles/pwm_cluster_pwm_cluster_pio_h.dir/compiler_depend.make

# Include the progress variables for this target.
include pimoroni-pico/drivers/pwm/CMakeFiles/pwm_cluster_pwm_cluster_pio_h.dir/progress.make

pimoroni-pico/drivers/pwm/CMakeFiles/pwm_cluster_pwm_cluster_pio_h: pimoroni-pico/drivers/pwm/pwm_cluster.pio.h

pimoroni-pico/drivers/pwm/pwm_cluster.pio.h: /Users/m1/Documents/C++/pico/vehicle_platform/pimoroni-pico/drivers/pwm/pwm_cluster.pio
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/m1/Documents/C++/pico/vehicle_platform/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating pwm_cluster.pio.h"
	cd /Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/pwm && ../../../pioasm/pioasm -o c-sdk /Users/m1/Documents/C++/pico/vehicle_platform/pimoroni-pico/drivers/pwm/pwm_cluster.pio /Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/pwm/pwm_cluster.pio.h

pwm_cluster_pwm_cluster_pio_h: pimoroni-pico/drivers/pwm/CMakeFiles/pwm_cluster_pwm_cluster_pio_h
pwm_cluster_pwm_cluster_pio_h: pimoroni-pico/drivers/pwm/pwm_cluster.pio.h
pwm_cluster_pwm_cluster_pio_h: pimoroni-pico/drivers/pwm/CMakeFiles/pwm_cluster_pwm_cluster_pio_h.dir/build.make
.PHONY : pwm_cluster_pwm_cluster_pio_h

# Rule to build all files generated by this target.
pimoroni-pico/drivers/pwm/CMakeFiles/pwm_cluster_pwm_cluster_pio_h.dir/build: pwm_cluster_pwm_cluster_pio_h
.PHONY : pimoroni-pico/drivers/pwm/CMakeFiles/pwm_cluster_pwm_cluster_pio_h.dir/build

pimoroni-pico/drivers/pwm/CMakeFiles/pwm_cluster_pwm_cluster_pio_h.dir/clean:
	cd /Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/pwm && $(CMAKE_COMMAND) -P CMakeFiles/pwm_cluster_pwm_cluster_pio_h.dir/cmake_clean.cmake
.PHONY : pimoroni-pico/drivers/pwm/CMakeFiles/pwm_cluster_pwm_cluster_pio_h.dir/clean

pimoroni-pico/drivers/pwm/CMakeFiles/pwm_cluster_pwm_cluster_pio_h.dir/depend:
	cd /Users/m1/Documents/C++/pico/vehicle_platform/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/m1/Documents/C++/pico/vehicle_platform /Users/m1/Documents/C++/pico/vehicle_platform/pimoroni-pico/drivers/pwm /Users/m1/Documents/C++/pico/vehicle_platform/build /Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/pwm /Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/drivers/pwm/CMakeFiles/pwm_cluster_pwm_cluster_pio_h.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : pimoroni-pico/drivers/pwm/CMakeFiles/pwm_cluster_pwm_cluster_pio_h.dir/depend

