/*
This software is provided for student assignment use in the Department of
Electrical and Computer Engineering, Brigham Young University, Utah, USA.
Users agree to not re-host, or redistribute the software, in source or binary
form, to other persons or other institutions. Users may modify and use the
source code for personal or educational use.
For questions, contact Brad Hutchings or Jeff Goeders, https://ece.byu.edu/
*/

// Uncomment to run tests, various Milestones
// #define RUNNING_MODE_TESTS

// Uncomment to run Milestone 3, Task 2
//#define RUNNING_MODE_M3_T2

// Uncomment to run continuous/shooter mode, Milestone 3, Task 3
//#define RUNNING_MODE_M3_T3

// Uncomment to run two-player mode, Milestone 5
#define RUNNING_MODE_M5

// The following line enables the main() contained in laserTagMain.c
// Leave this line uncommented unless you want to run some other special test
// main().
#define LASER_TAG_MAIN

#ifdef LASER_TAG_MAIN

#include <assert.h>
#include <stdio.h>

#include "buttons.h"
#include "detector.h"
#include "filter.h"
#include "filterTest.h"
#include "hitLedTimer.h"
#include "interrupts.h"
#include "isr.h"
#include "leds.h"
#include "lockoutTimer.h"
#include "mio.h"
#include "runningModes.h"
#include "sound.h"
#include "switches.h"
#include "transmitter.h"
#include "trigger.h"

int main() {
  buttons_init();
  switches_init();
  mio_init(false);
  leds_init(true);
  mio_init(false);

#ifdef RUNNING_MODE_TESTS
  // queue_runTest(); // M1
  // filterTest_runTest(); // M3 T1
  // transmitter_runTest(); // M3 T2
  // detector_runTest(); // M3 T3
  sound_runTest(); // M4
#endif

#ifdef RUNNING_MODE_M3_T2

  isr_init();

  interrupts_initAll(true);           // main interrupt init function.
  interrupts_enableTimerGlobalInts(); // enable global interrupts.
  interrupts_startArmPrivateTimer();  // start the main timer.
  interrupts_enableArmInts(); // now the ARM processor can see interrupts.

  transmitter_runNoncontinuousTest();
  transmitter_runContinuousTest();
  printf("lets run trigger test\n");
  trigger_runTest();

  printf("Run hitLED test\n");
  hitLedTimer_runTest();

  lockoutTimer_runTest();

  while (1) {
    ;
    isr_function(); // Forever-while loop. Modify as you see fit.
    // utils_msDelay(250);
  }
#endif

#ifdef RUNNING_MODE_M3_T3
  // The program comes up in continuous mode.
  // Hold BTN2 while the program starts to come up in shooter mode.

  if (buttons_read() &
      BUTTONS_BTN2_MASK) { // Read the buttons to see if BTN2 is depressed.
    // printf("Starting continuous mode\n");
    runningModes_continuous(); // Otherwise, go to continuous mode.
  } else {
    // printf("Starting shooter mode\n");
    runningModes_shooter(); // Run shooter mode if BTN2 is depressed.
  }
#endif

#ifdef RUNNING_MODE_M5
  printf("Starting two team mode\n");
  runningModes_zombie();
#endif

  return 0;
}

#endif // LASER_TAG_MAIN

// ../run_elf_on_board.py lasertag/lasertag.elf
