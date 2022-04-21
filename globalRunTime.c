#include "include/utils.h"
#include "invincibilityTimer.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define RUNNING true
#define RESET_COUNTER 0
#define CLOCK_FREQUENCY 100000
#define SECONDS_PER_MINUTE 60

volatile uint64_t globalRunTime = RESET_COUNTER;
volatile uint64_t globalRunTimeCounter = RESET_COUNTER;

// volatile static bool reloadTimerEnable;
volatile static bool globalRunTimerRunning;

// The state names in the state-machine
volatile static enum globalRunTime_st_t {
  globalRunTime_wait_st,
  globalRunTime_init_st,
  globalRunTime_run_st
} globalRunTime_currentState;

// Need to init things.
void globalRunTime_init() {
  globalRunTime_currentState = globalRunTime_init_st;
  globalRunTimerRunning = !RUNNING;
}

// Calling this starts the timer.
void globalRunTime_start(uint16_t minutes) {
  globalRunTime = minutes * SECONDS_PER_MINUTE * CLOCK_FREQUENCY;
  globalRunTimerRunning = RUNNING;
  // printf("global timer started: %d\n", globalRunTime);
}

// Returns true if the timer is currently running.
bool globalRunTime_running() { return globalRunTimerRunning; }

// Standard tick function.
void globalRunTime_tick() {
  // switch to handle state machine
  switch (globalRunTime_currentState) {
  case globalRunTime_init_st:
    globalRunTime_currentState = globalRunTime_wait_st;
    break;

  case globalRunTime_wait_st:
    // if timer is enabled and running it will start
    if (globalRunTimerRunning) {
      globalRunTime_currentState = globalRunTime_run_st;
      globalRunTimeCounter = RESET_COUNTER;
    }
    break;

  case globalRunTime_run_st:
    globalRunTimeCounter++;

    // when the count reaches invincibleTime it will turn off
    if (globalRunTimeCounter >= globalRunTime) {
      globalRunTime_currentState = globalRunTime_wait_st;
      globalRunTimerRunning = !RUNNING;
    }
    break;
  }
}
