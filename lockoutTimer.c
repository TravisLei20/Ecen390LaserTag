#include "lockoutTimer.h"
#include <stdint.h>
#include <stdio.h>

#include "drivers/intervalTimer.h"
#include "isr.h"

#include "include/utils.h"

// Uncomment for debug prints
//#define DEBUG

#if defined(DEBUG)
#include "xil_printf.h"
#include <stdio.h>

#define DPRINTF(...) printf(__VA_ARGS__)
#define DPCHAR(ch) outbyte(ch)
#else
#define DPRINTF(...)
#define DPCHAR(ch)
#endif

#define RUN true
#define DEFAULT_ERROR_MESSAGE "Wrong!!!"
#define RESET_COUNTER 0
#define LOCKOUT_COUNT 50000

volatile static bool lockoutTimerRunning = false;

volatile static uint16_t counter = RESET_COUNTER;

// The state names in the state-machine
volatile static enum lockoutTimer_st_t {
  lockoutTimer_init_st,
  lockoutTimer_wait_st,
  lockoutTimer_run_st
} lockout_currentState;

// Calling this starts the timer.
void lockoutTimer_start() { lockoutTimerRunning = RUN; }

// Perform any necessary inits for the lockout timer.
void lockoutTimer_init() { lockout_currentState = lockoutTimer_init_st; }

// Returns true if the timer is running.
bool lockoutTimer_running() { return lockoutTimerRunning; }

// Standard tick function.
void lockoutTimer_tick() {
  // this goes throughout the state machine
  switch (lockout_currentState) {
  case lockoutTimer_init_st:
    lockout_currentState = lockoutTimer_wait_st;
    break;

  case lockoutTimer_wait_st:
    // If the timer is running then go to the run state and reset counter
    if (lockoutTimerRunning) {
      lockout_currentState = lockoutTimer_run_st;
      counter = RESET_COUNTER;
      DPCHAR('R');
      DPCHAR('\n');
    }
    break;

  case lockoutTimer_run_st:
    counter++;
    // if counter is greater than or equal to
    if (counter >= LOCKOUT_COUNT) {
      lockout_currentState = lockoutTimer_wait_st;
      lockoutTimerRunning = !RUN;
      DPCHAR('S');
      DPCHAR('\n');
    }
    break;

  // Prints a default error message
  default:
    printf(DEFAULT_ERROR_MESSAGE);
    break;
  }
}

// Test function assumes interrupts have been completely enabled and
// lockoutTimer_tick() function is invoked by isr_function().
// Prints out pass/fail status and other info to console.
// Returns true if passes, false otherwise.
// This test uses the interval timer to determine correct delay for
// the interval timer.
bool lockoutTimer_runTest() {
  intervalTimer_init(INTERVAL_TIMER_TIMER_1);
  lockoutTimer_init();

  intervalTimer_reset(INTERVAL_TIMER_TIMER_1);

  intervalTimer_start(INTERVAL_TIMER_TIMER_1);

  lockoutTimer_start();

  // runs until lockouttimer is not running
  while (lockoutTimer_running()) {
    utils_sleep();
  }

  intervalTimer_stop(INTERVAL_TIMER_TIMER_1);

  printf("The interval timer is %f\n",
         intervalTimer_getTotalDurationInSeconds(INTERVAL_TIMER_TIMER_1));
  printf("The lockout timer is 0.5\n");
  return true;
}