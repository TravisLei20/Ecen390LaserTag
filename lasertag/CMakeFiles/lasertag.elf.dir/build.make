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
CMAKE_COMMAND = /usr/local/lib/python3.6/dist-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /usr/local/lib/python3.6/dist-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /fsd/leicr/ecen330

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /fsd/leicr/ecen330/lasertag

# Include any dependencies generated for this target.
include lasertag/CMakeFiles/lasertag.elf.dir/depend.make

# Include the progress variables for this target.
include lasertag/CMakeFiles/lasertag.elf.dir/progress.make

# Include the compile flags for this target's objects.
include lasertag/CMakeFiles/lasertag.elf.dir/flags.make

lasertag/CMakeFiles/lasertag.elf.dir/main.c.o: lasertag/CMakeFiles/lasertag.elf.dir/flags.make
lasertag/CMakeFiles/lasertag.elf.dir/main.c.o: main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/fsd/leicr/ecen330/lasertag/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object lasertag/CMakeFiles/lasertag.elf.dir/main.c.o"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/lasertag.elf.dir/main.c.o -c /fsd/leicr/ecen330/lasertag/main.c

lasertag/CMakeFiles/lasertag.elf.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lasertag.elf.dir/main.c.i"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /fsd/leicr/ecen330/lasertag/main.c > CMakeFiles/lasertag.elf.dir/main.c.i

lasertag/CMakeFiles/lasertag.elf.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lasertag.elf.dir/main.c.s"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /fsd/leicr/ecen330/lasertag/main.c -o CMakeFiles/lasertag.elf.dir/main.c.s

lasertag/CMakeFiles/lasertag.elf.dir/queue_test.c.o: lasertag/CMakeFiles/lasertag.elf.dir/flags.make
lasertag/CMakeFiles/lasertag.elf.dir/queue_test.c.o: queue_test.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/fsd/leicr/ecen330/lasertag/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object lasertag/CMakeFiles/lasertag.elf.dir/queue_test.c.o"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/lasertag.elf.dir/queue_test.c.o -c /fsd/leicr/ecen330/lasertag/queue_test.c

lasertag/CMakeFiles/lasertag.elf.dir/queue_test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lasertag.elf.dir/queue_test.c.i"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /fsd/leicr/ecen330/lasertag/queue_test.c > CMakeFiles/lasertag.elf.dir/queue_test.c.i

lasertag/CMakeFiles/lasertag.elf.dir/queue_test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lasertag.elf.dir/queue_test.c.s"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /fsd/leicr/ecen330/lasertag/queue_test.c -o CMakeFiles/lasertag.elf.dir/queue_test.c.s

lasertag/CMakeFiles/lasertag.elf.dir/filter.c.o: lasertag/CMakeFiles/lasertag.elf.dir/flags.make
lasertag/CMakeFiles/lasertag.elf.dir/filter.c.o: filter.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/fsd/leicr/ecen330/lasertag/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object lasertag/CMakeFiles/lasertag.elf.dir/filter.c.o"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/lasertag.elf.dir/filter.c.o -c /fsd/leicr/ecen330/lasertag/filter.c

lasertag/CMakeFiles/lasertag.elf.dir/filter.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lasertag.elf.dir/filter.c.i"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /fsd/leicr/ecen330/lasertag/filter.c > CMakeFiles/lasertag.elf.dir/filter.c.i

lasertag/CMakeFiles/lasertag.elf.dir/filter.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lasertag.elf.dir/filter.c.s"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /fsd/leicr/ecen330/lasertag/filter.c -o CMakeFiles/lasertag.elf.dir/filter.c.s

lasertag/CMakeFiles/lasertag.elf.dir/filterTest.c.o: lasertag/CMakeFiles/lasertag.elf.dir/flags.make
lasertag/CMakeFiles/lasertag.elf.dir/filterTest.c.o: filterTest.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/fsd/leicr/ecen330/lasertag/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object lasertag/CMakeFiles/lasertag.elf.dir/filterTest.c.o"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/lasertag.elf.dir/filterTest.c.o -c /fsd/leicr/ecen330/lasertag/filterTest.c

lasertag/CMakeFiles/lasertag.elf.dir/filterTest.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lasertag.elf.dir/filterTest.c.i"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /fsd/leicr/ecen330/lasertag/filterTest.c > CMakeFiles/lasertag.elf.dir/filterTest.c.i

lasertag/CMakeFiles/lasertag.elf.dir/filterTest.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lasertag.elf.dir/filterTest.c.s"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /fsd/leicr/ecen330/lasertag/filterTest.c -o CMakeFiles/lasertag.elf.dir/filterTest.c.s

lasertag/CMakeFiles/lasertag.elf.dir/histogram.c.o: lasertag/CMakeFiles/lasertag.elf.dir/flags.make
lasertag/CMakeFiles/lasertag.elf.dir/histogram.c.o: histogram.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/fsd/leicr/ecen330/lasertag/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object lasertag/CMakeFiles/lasertag.elf.dir/histogram.c.o"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/lasertag.elf.dir/histogram.c.o -c /fsd/leicr/ecen330/lasertag/histogram.c

lasertag/CMakeFiles/lasertag.elf.dir/histogram.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lasertag.elf.dir/histogram.c.i"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /fsd/leicr/ecen330/lasertag/histogram.c > CMakeFiles/lasertag.elf.dir/histogram.c.i

lasertag/CMakeFiles/lasertag.elf.dir/histogram.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lasertag.elf.dir/histogram.c.s"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /fsd/leicr/ecen330/lasertag/histogram.c -o CMakeFiles/lasertag.elf.dir/histogram.c.s

lasertag/CMakeFiles/lasertag.elf.dir/isr.c.o: lasertag/CMakeFiles/lasertag.elf.dir/flags.make
lasertag/CMakeFiles/lasertag.elf.dir/isr.c.o: isr.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/fsd/leicr/ecen330/lasertag/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object lasertag/CMakeFiles/lasertag.elf.dir/isr.c.o"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/lasertag.elf.dir/isr.c.o -c /fsd/leicr/ecen330/lasertag/isr.c

lasertag/CMakeFiles/lasertag.elf.dir/isr.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lasertag.elf.dir/isr.c.i"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /fsd/leicr/ecen330/lasertag/isr.c > CMakeFiles/lasertag.elf.dir/isr.c.i

lasertag/CMakeFiles/lasertag.elf.dir/isr.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lasertag.elf.dir/isr.c.s"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /fsd/leicr/ecen330/lasertag/isr.c -o CMakeFiles/lasertag.elf.dir/isr.c.s

lasertag/CMakeFiles/lasertag.elf.dir/trigger.c.o: lasertag/CMakeFiles/lasertag.elf.dir/flags.make
lasertag/CMakeFiles/lasertag.elf.dir/trigger.c.o: trigger.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/fsd/leicr/ecen330/lasertag/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object lasertag/CMakeFiles/lasertag.elf.dir/trigger.c.o"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/lasertag.elf.dir/trigger.c.o -c /fsd/leicr/ecen330/lasertag/trigger.c

lasertag/CMakeFiles/lasertag.elf.dir/trigger.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lasertag.elf.dir/trigger.c.i"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /fsd/leicr/ecen330/lasertag/trigger.c > CMakeFiles/lasertag.elf.dir/trigger.c.i

lasertag/CMakeFiles/lasertag.elf.dir/trigger.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lasertag.elf.dir/trigger.c.s"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /fsd/leicr/ecen330/lasertag/trigger.c -o CMakeFiles/lasertag.elf.dir/trigger.c.s

lasertag/CMakeFiles/lasertag.elf.dir/transmitter.c.o: lasertag/CMakeFiles/lasertag.elf.dir/flags.make
lasertag/CMakeFiles/lasertag.elf.dir/transmitter.c.o: transmitter.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/fsd/leicr/ecen330/lasertag/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object lasertag/CMakeFiles/lasertag.elf.dir/transmitter.c.o"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/lasertag.elf.dir/transmitter.c.o -c /fsd/leicr/ecen330/lasertag/transmitter.c

lasertag/CMakeFiles/lasertag.elf.dir/transmitter.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lasertag.elf.dir/transmitter.c.i"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /fsd/leicr/ecen330/lasertag/transmitter.c > CMakeFiles/lasertag.elf.dir/transmitter.c.i

lasertag/CMakeFiles/lasertag.elf.dir/transmitter.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lasertag.elf.dir/transmitter.c.s"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /fsd/leicr/ecen330/lasertag/transmitter.c -o CMakeFiles/lasertag.elf.dir/transmitter.c.s

lasertag/CMakeFiles/lasertag.elf.dir/hitLedTimer.c.o: lasertag/CMakeFiles/lasertag.elf.dir/flags.make
lasertag/CMakeFiles/lasertag.elf.dir/hitLedTimer.c.o: hitLedTimer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/fsd/leicr/ecen330/lasertag/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object lasertag/CMakeFiles/lasertag.elf.dir/hitLedTimer.c.o"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/lasertag.elf.dir/hitLedTimer.c.o -c /fsd/leicr/ecen330/lasertag/hitLedTimer.c

lasertag/CMakeFiles/lasertag.elf.dir/hitLedTimer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lasertag.elf.dir/hitLedTimer.c.i"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /fsd/leicr/ecen330/lasertag/hitLedTimer.c > CMakeFiles/lasertag.elf.dir/hitLedTimer.c.i

lasertag/CMakeFiles/lasertag.elf.dir/hitLedTimer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lasertag.elf.dir/hitLedTimer.c.s"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /fsd/leicr/ecen330/lasertag/hitLedTimer.c -o CMakeFiles/lasertag.elf.dir/hitLedTimer.c.s

lasertag/CMakeFiles/lasertag.elf.dir/lockoutTimer.c.o: lasertag/CMakeFiles/lasertag.elf.dir/flags.make
lasertag/CMakeFiles/lasertag.elf.dir/lockoutTimer.c.o: lockoutTimer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/fsd/leicr/ecen330/lasertag/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object lasertag/CMakeFiles/lasertag.elf.dir/lockoutTimer.c.o"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/lasertag.elf.dir/lockoutTimer.c.o -c /fsd/leicr/ecen330/lasertag/lockoutTimer.c

lasertag/CMakeFiles/lasertag.elf.dir/lockoutTimer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lasertag.elf.dir/lockoutTimer.c.i"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /fsd/leicr/ecen330/lasertag/lockoutTimer.c > CMakeFiles/lasertag.elf.dir/lockoutTimer.c.i

lasertag/CMakeFiles/lasertag.elf.dir/lockoutTimer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lasertag.elf.dir/lockoutTimer.c.s"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /fsd/leicr/ecen330/lasertag/lockoutTimer.c -o CMakeFiles/lasertag.elf.dir/lockoutTimer.c.s

lasertag/CMakeFiles/lasertag.elf.dir/detector.c.o: lasertag/CMakeFiles/lasertag.elf.dir/flags.make
lasertag/CMakeFiles/lasertag.elf.dir/detector.c.o: detector.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/fsd/leicr/ecen330/lasertag/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object lasertag/CMakeFiles/lasertag.elf.dir/detector.c.o"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/lasertag.elf.dir/detector.c.o -c /fsd/leicr/ecen330/lasertag/detector.c

lasertag/CMakeFiles/lasertag.elf.dir/detector.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lasertag.elf.dir/detector.c.i"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /fsd/leicr/ecen330/lasertag/detector.c > CMakeFiles/lasertag.elf.dir/detector.c.i

lasertag/CMakeFiles/lasertag.elf.dir/detector.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lasertag.elf.dir/detector.c.s"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /fsd/leicr/ecen330/lasertag/detector.c -o CMakeFiles/lasertag.elf.dir/detector.c.s

lasertag/CMakeFiles/lasertag.elf.dir/sound.c.o: lasertag/CMakeFiles/lasertag.elf.dir/flags.make
lasertag/CMakeFiles/lasertag.elf.dir/sound.c.o: sound.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/fsd/leicr/ecen330/lasertag/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object lasertag/CMakeFiles/lasertag.elf.dir/sound.c.o"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/lasertag.elf.dir/sound.c.o -c /fsd/leicr/ecen330/lasertag/sound.c

lasertag/CMakeFiles/lasertag.elf.dir/sound.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lasertag.elf.dir/sound.c.i"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /fsd/leicr/ecen330/lasertag/sound.c > CMakeFiles/lasertag.elf.dir/sound.c.i

lasertag/CMakeFiles/lasertag.elf.dir/sound.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lasertag.elf.dir/sound.c.s"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /fsd/leicr/ecen330/lasertag/sound.c -o CMakeFiles/lasertag.elf.dir/sound.c.s

lasertag/CMakeFiles/lasertag.elf.dir/timer_ps.c.o: lasertag/CMakeFiles/lasertag.elf.dir/flags.make
lasertag/CMakeFiles/lasertag.elf.dir/timer_ps.c.o: timer_ps.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/fsd/leicr/ecen330/lasertag/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object lasertag/CMakeFiles/lasertag.elf.dir/timer_ps.c.o"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/lasertag.elf.dir/timer_ps.c.o -c /fsd/leicr/ecen330/lasertag/timer_ps.c

lasertag/CMakeFiles/lasertag.elf.dir/timer_ps.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lasertag.elf.dir/timer_ps.c.i"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /fsd/leicr/ecen330/lasertag/timer_ps.c > CMakeFiles/lasertag.elf.dir/timer_ps.c.i

lasertag/CMakeFiles/lasertag.elf.dir/timer_ps.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lasertag.elf.dir/timer_ps.c.s"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /fsd/leicr/ecen330/lasertag/timer_ps.c -o CMakeFiles/lasertag.elf.dir/timer_ps.c.s

lasertag/CMakeFiles/lasertag.elf.dir/runningModes.c.o: lasertag/CMakeFiles/lasertag.elf.dir/flags.make
lasertag/CMakeFiles/lasertag.elf.dir/runningModes.c.o: runningModes.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/fsd/leicr/ecen330/lasertag/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building C object lasertag/CMakeFiles/lasertag.elf.dir/runningModes.c.o"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/lasertag.elf.dir/runningModes.c.o -c /fsd/leicr/ecen330/lasertag/runningModes.c

lasertag/CMakeFiles/lasertag.elf.dir/runningModes.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lasertag.elf.dir/runningModes.c.i"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /fsd/leicr/ecen330/lasertag/runningModes.c > CMakeFiles/lasertag.elf.dir/runningModes.c.i

lasertag/CMakeFiles/lasertag.elf.dir/runningModes.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lasertag.elf.dir/runningModes.c.s"
	cd /fsd/leicr/ecen330/lasertag/lasertag && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /fsd/leicr/ecen330/lasertag/runningModes.c -o CMakeFiles/lasertag.elf.dir/runningModes.c.s

# Object files for target lasertag.elf
lasertag_elf_OBJECTS = \
"CMakeFiles/lasertag.elf.dir/main.c.o" \
"CMakeFiles/lasertag.elf.dir/queue_test.c.o" \
"CMakeFiles/lasertag.elf.dir/filter.c.o" \
"CMakeFiles/lasertag.elf.dir/filterTest.c.o" \
"CMakeFiles/lasertag.elf.dir/histogram.c.o" \
"CMakeFiles/lasertag.elf.dir/isr.c.o" \
"CMakeFiles/lasertag.elf.dir/trigger.c.o" \
"CMakeFiles/lasertag.elf.dir/transmitter.c.o" \
"CMakeFiles/lasertag.elf.dir/hitLedTimer.c.o" \
"CMakeFiles/lasertag.elf.dir/lockoutTimer.c.o" \
"CMakeFiles/lasertag.elf.dir/detector.c.o" \
"CMakeFiles/lasertag.elf.dir/sound.c.o" \
"CMakeFiles/lasertag.elf.dir/timer_ps.c.o" \
"CMakeFiles/lasertag.elf.dir/runningModes.c.o"

# External object files for target lasertag.elf
lasertag_elf_EXTERNAL_OBJECTS =

lasertag/lasertag.elf: lasertag/CMakeFiles/lasertag.elf.dir/main.c.o
lasertag/lasertag.elf: lasertag/CMakeFiles/lasertag.elf.dir/queue_test.c.o
lasertag/lasertag.elf: lasertag/CMakeFiles/lasertag.elf.dir/filter.c.o
lasertag/lasertag.elf: lasertag/CMakeFiles/lasertag.elf.dir/filterTest.c.o
lasertag/lasertag.elf: lasertag/CMakeFiles/lasertag.elf.dir/histogram.c.o
lasertag/lasertag.elf: lasertag/CMakeFiles/lasertag.elf.dir/isr.c.o
lasertag/lasertag.elf: lasertag/CMakeFiles/lasertag.elf.dir/trigger.c.o
lasertag/lasertag.elf: lasertag/CMakeFiles/lasertag.elf.dir/transmitter.c.o
lasertag/lasertag.elf: lasertag/CMakeFiles/lasertag.elf.dir/hitLedTimer.c.o
lasertag/lasertag.elf: lasertag/CMakeFiles/lasertag.elf.dir/lockoutTimer.c.o
lasertag/lasertag.elf: lasertag/CMakeFiles/lasertag.elf.dir/detector.c.o
lasertag/lasertag.elf: lasertag/CMakeFiles/lasertag.elf.dir/sound.c.o
lasertag/lasertag.elf: lasertag/CMakeFiles/lasertag.elf.dir/timer_ps.c.o
lasertag/lasertag.elf: lasertag/CMakeFiles/lasertag.elf.dir/runningModes.c.o
lasertag/lasertag.elf: lasertag/CMakeFiles/lasertag.elf.dir/build.make
lasertag/lasertag.elf: lasertag/sounds/libsounds.a
lasertag/lasertag.elf: lasertag/CMakeFiles/lasertag.elf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/fsd/leicr/ecen330/lasertag/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Linking CXX executable lasertag.elf"
	cd /fsd/leicr/ecen330/lasertag/lasertag && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lasertag.elf.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lasertag/CMakeFiles/lasertag.elf.dir/build: lasertag/lasertag.elf

.PHONY : lasertag/CMakeFiles/lasertag.elf.dir/build

lasertag/CMakeFiles/lasertag.elf.dir/clean:
	cd /fsd/leicr/ecen330/lasertag/lasertag && $(CMAKE_COMMAND) -P CMakeFiles/lasertag.elf.dir/cmake_clean.cmake
.PHONY : lasertag/CMakeFiles/lasertag.elf.dir/clean

lasertag/CMakeFiles/lasertag.elf.dir/depend:
	cd /fsd/leicr/ecen330/lasertag && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /fsd/leicr/ecen330 /fsd/leicr/ecen330/lasertag /fsd/leicr/ecen330/lasertag /fsd/leicr/ecen330/lasertag/lasertag /fsd/leicr/ecen330/lasertag/lasertag/CMakeFiles/lasertag.elf.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lasertag/CMakeFiles/lasertag.elf.dir/depend

