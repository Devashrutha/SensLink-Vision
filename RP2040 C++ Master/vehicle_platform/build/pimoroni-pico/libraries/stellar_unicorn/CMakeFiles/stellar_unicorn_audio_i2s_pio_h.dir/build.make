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

# Utility rule file for stellar_unicorn_audio_i2s_pio_h.

# Include any custom commands dependencies for this target.
include pimoroni-pico/libraries/stellar_unicorn/CMakeFiles/stellar_unicorn_audio_i2s_pio_h.dir/compiler_depend.make

# Include the progress variables for this target.
include pimoroni-pico/libraries/stellar_unicorn/CMakeFiles/stellar_unicorn_audio_i2s_pio_h.dir/progress.make

pimoroni-pico/libraries/stellar_unicorn/CMakeFiles/stellar_unicorn_audio_i2s_pio_h: pimoroni-pico/libraries/stellar_unicorn/audio_i2s.pio.h

pimoroni-pico/libraries/stellar_unicorn/audio_i2s.pio.h: /Users/m1/Documents/C++/pico/vehicle_platform/pimoroni-pico/libraries/stellar_unicorn/audio_i2s.pio
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/m1/Documents/C++/pico/vehicle_platform/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating audio_i2s.pio.h"
	cd /Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/libraries/stellar_unicorn && ../../../pioasm/pioasm -o c-sdk /Users/m1/Documents/C++/pico/vehicle_platform/pimoroni-pico/libraries/stellar_unicorn/audio_i2s.pio /Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/libraries/stellar_unicorn/audio_i2s.pio.h

stellar_unicorn_audio_i2s_pio_h: pimoroni-pico/libraries/stellar_unicorn/CMakeFiles/stellar_unicorn_audio_i2s_pio_h
stellar_unicorn_audio_i2s_pio_h: pimoroni-pico/libraries/stellar_unicorn/audio_i2s.pio.h
stellar_unicorn_audio_i2s_pio_h: pimoroni-pico/libraries/stellar_unicorn/CMakeFiles/stellar_unicorn_audio_i2s_pio_h.dir/build.make
.PHONY : stellar_unicorn_audio_i2s_pio_h

# Rule to build all files generated by this target.
pimoroni-pico/libraries/stellar_unicorn/CMakeFiles/stellar_unicorn_audio_i2s_pio_h.dir/build: stellar_unicorn_audio_i2s_pio_h
.PHONY : pimoroni-pico/libraries/stellar_unicorn/CMakeFiles/stellar_unicorn_audio_i2s_pio_h.dir/build

pimoroni-pico/libraries/stellar_unicorn/CMakeFiles/stellar_unicorn_audio_i2s_pio_h.dir/clean:
	cd /Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/libraries/stellar_unicorn && $(CMAKE_COMMAND) -P CMakeFiles/stellar_unicorn_audio_i2s_pio_h.dir/cmake_clean.cmake
.PHONY : pimoroni-pico/libraries/stellar_unicorn/CMakeFiles/stellar_unicorn_audio_i2s_pio_h.dir/clean

pimoroni-pico/libraries/stellar_unicorn/CMakeFiles/stellar_unicorn_audio_i2s_pio_h.dir/depend:
	cd /Users/m1/Documents/C++/pico/vehicle_platform/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/m1/Documents/C++/pico/vehicle_platform /Users/m1/Documents/C++/pico/vehicle_platform/pimoroni-pico/libraries/stellar_unicorn /Users/m1/Documents/C++/pico/vehicle_platform/build /Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/libraries/stellar_unicorn /Users/m1/Documents/C++/pico/vehicle_platform/build/pimoroni-pico/libraries/stellar_unicorn/CMakeFiles/stellar_unicorn_audio_i2s_pio_h.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : pimoroni-pico/libraries/stellar_unicorn/CMakeFiles/stellar_unicorn_audio_i2s_pio_h.dir/depend

