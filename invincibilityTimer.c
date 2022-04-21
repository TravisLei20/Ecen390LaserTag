#include "invincibilityTimer.h"
#include "include/utils.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define RUNNING true
#define RESET_COUNTER 0
#define CLOCK_FREQUENCY 100000

volatile uint64_t invincibleTime = RESET_COUNTER;
volatile uint64_t invincibleCounter = RESET_COUNTER;

// volatile static bool reloadTimerEnable;
volatile static bool invincibilityTimerRunning;

// The state names in the state-machine
volatile static enum invincibilityTimer_st_t {
  invincibilityTimer_wait_st,
  invincibilityTimer_init_st,
  invincibilityTimer_run_st
} invincibilityTimer_currentState;

// Need to init things.
void invincibilityTimer_init() {
  invincibilityTimer_currentState = invincibilityTimer_init_st;
  invincibilityTimerRunning = !RUNNING;
}

// Calling this starts the timer.
void invincibilityTimer_start(uint16_t seconds) {
  invincibleTime = seconds * CLOCK_FREQUENCY;
  invincibilityTimerRunning = RUNNING;
  // printf("Invincibility started\n");
}

// Returns true if the timer is currently running.
bool invincibilityTimer_running() { return invincibilityTimerRunning; }

// Standard tick function.
void invincibilityTimer_tick() {
  // switch to handle state machine
  switch (invincibilityTimer_currentState) {
  case invincibilityTimer_init_st:
    invincibilityTimer_currentState = invincibilityTimer_wait_st;
    break;

  case invincibilityTimer_wait_st:
    // if timer is enabled and running it will start
    if (invincibilityTimerRunning) {
      invincibilityTimer_currentState = invincibilityTimer_run_st;
      invincibleCounter = RESET_COUNTER;
    }
    break;

  case invincibilityTimer_run_st:
    invincibleCounter++;

    // when the count reaches invincibleTime it will turn off
    if (invincibleCounter >= invincibleTime) {
      invincibilityTimer_currentState = invincibilityTimer_wait_st;
      invincibilityTimerRunning = !RUNNING;
      // printf("invincibility ended\n");
      // sound_playSound(sound_gunReload_e);
    }
    break;
  }
}
