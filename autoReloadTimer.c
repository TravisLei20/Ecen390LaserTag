
#include "autoReloadTimer.h"
#include "drivers/buttons.h"
#include "include/utils.h"
#include "sound.h"
#include "trigger.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define RUNNING true
#define RESET_COUNTER 0

volatile uint64_t reloadCounter = RESET_COUNTER;

// volatile static bool reloadTimerEnable;
volatile static bool reloadTimerRunning;

// The state names in the state-machine
volatile static enum reloadTimer_st_t {
  autoReloadTimer_init_st,
  autoReloadTimer_wait_st,
  autoReloadTimer_run_st
} autoReloadTimer_currentState;

// The auto-reload timer is always looking at the remaining shot-count from the
// trigger state-machine. When it goes to 0, it starts a configurable delay and
// after the delay expires, it sets the remaining shots to a specific value.

// Need to init things.
void autoReloadTimer_init() {
  autoReloadTimer_currentState = autoReloadTimer_init_st;
  reloadTimerRunning = !RUNNING;
  // reloadTimerEnable = ENABLE;
}

// Calling this starts the timer.
void autoReloadTimer_start() {
  reloadTimerRunning = RUNNING;
  // printf("Reload started\n");
}

// Returns true if the timer is currently running.
bool autoReloadTimer_running() { return reloadTimerRunning; }

// Disables the autoReloadTimer and re-initializes it.
void autoReloadTimer_cancel() {
  reloadTimerRunning = !RUNNING;
  autoReloadTimer_currentState = autoReloadTimer_init_st;
  // printf("Reload cancelled\n");
}

// Standard tick function.
void autoReloadTimer_tick() {
  // switch to handle state machine
  switch (autoReloadTimer_currentState) {
  case autoReloadTimer_init_st:
    autoReloadTimer_currentState = autoReloadTimer_wait_st;
    break;

  case autoReloadTimer_wait_st:
    // if timer is enabled and running it will start
    if (reloadTimerRunning) { //  reloadTimerEnable &&
      autoReloadTimer_currentState = autoReloadTimer_run_st;
      reloadCounter = RESET_COUNTER;
    }
    break;

  case autoReloadTimer_run_st:
    reloadCounter++;

    // when the count reaches AUTO_RELOAD_EXPIRE_VALUE it will turn off
    if (reloadCounter >= AUTO_RELOAD_EXPIRE_VALUE) {
      autoReloadTimer_currentState = autoReloadTimer_wait_st;
      reloadTimerRunning = !RUNNING;
      trigger_setRemainingShotCount(AUTO_RELOAD_SHOT_VALUE);
      sound_playSound(sound_gunReload_e);
    }
    break;
  }
}
