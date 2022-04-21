#include "trigger.h"
#include "autoReloadTimer.h"
#include "drivers/buttons.h"
#include "include/mio.h"
#include "include/utils.h"
#include "invincibilityTimer.h"
#include "sound.h"
#include "transmitter.h"

#include <stdio.h>

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

#define DEFAULT_ERROR_MESSAGE "Wrong!!!"
#define FIVE_MS_COUNTER 500
#define RESET_COUNTER 0
#define TRIGGER_GUN_TRIGGER_MIO_PIN 10 // JF-2 is MIO pin 10
#define GUN_TRIGGER_PRESSED true
#define DELAY_400_MS 400
#define INITIAL_SHOTS 100
#define NO_SHOTS_REMAINING 0
#define ENABLE true
#define IGNORE false

volatile trigger_shotsRemaining_t remainingShots;

volatile static bool enableTrigger = !ENABLE;
volatile static bool ignoreGunInput = IGNORE;

volatile static uint16_t counter;

// Enable the trigger state machine. The trigger state-machine is inactive until
// this function is called. This allows you to ignore the trigger when helpful
// (mostly useful for testing).
void trigger_enable() { enableTrigger = ENABLE; }

// Disable the trigger state machine so that trigger presses are ignored.
void trigger_disable() { enableTrigger = !ENABLE; }

// The state names in the state-machine
volatile static enum trigger_st_t {
  init_st,
  trigger_wait_for_action_st,
  trigger_debounce_pull_st,
  trigger_pulled_st,
  trigger_debounce_release_st,
  trigger_release_st
} trigger_currentState,
    trigger_previousState;

// Trigger can be activated by either btn0 or the external gun that is attached
// to TRIGGER_GUN_TRIGGER_MIO_PIN Gun input is ignored if the gun-input is high
// when the init() function is invoked.
bool triggerPressed() {
  return ((!ignoreGunInput) &
          ((mio_readPin(TRIGGER_GUN_TRIGGER_MIO_PIN) == GUN_TRIGGER_PRESSED) ||
           (buttons_read() & BUTTONS_BTN0_MASK)));
}

// Init trigger data-structures.
// Determines whether the trigger switch of the gun is connected (see discussion
// in lab web pages). Initializes the mio subsystem.
void trigger_init() {
  trigger_currentState = init_st;
  trigger_previousState = init_st;
  mio_init(IGNORE);

  mio_setPinAsInput(TRIGGER_GUN_TRIGGER_MIO_PIN);
  // If the trigger is pressed when trigger_init() is called, assume that the
  // gun is not connected and ignore it.
  if (triggerPressed()) {
    ignoreGunInput = !IGNORE;
  }

  counter = RESET_COUNTER;
}

// Enable the trigger state machine. The trigger state-machine is inactive until
// this function is called. This allows you to ignore the trigger when helpful
// (mostly useful for testing).
// void trigger_enable() { enableTrigger = true; }

// Disable the trigger state machine so that trigger presses are ignored.
// void trigger_disable() { enableTrigger = false; }

// Returns the number of remaining shots.
trigger_shotsRemaining_t trigger_getRemainingShotCount() {
  return remainingShots;
}

// Sets the number of remaining shots.
void trigger_setRemainingShotCount(trigger_shotsRemaining_t count) {
  remainingShots = count;
}

// this is the debugStatePrint function
void triggerDebugStatePrint() {
  static bool firstPass = !IGNORE;

  // if states have changed then print the occurence
  if ((trigger_previousState != trigger_currentState) || firstPass) {
    // printf("Prev state: %d, curr state: %d\n", trigger_previousState,
    //      trigger_currentState);
    firstPass = IGNORE;
    trigger_previousState = trigger_currentState;
    // switch statement to print change
    switch (trigger_currentState) {
    case init_st:
      printf("init_st\n");
      break;

    case trigger_wait_for_action_st:
      printf("trigger_wait_for_action_st\n");
      break;

    case trigger_debounce_pull_st:
      printf("trigger_debounce_pull_st\n");
      break;

    case trigger_pulled_st:
      printf("trigger_pulled_st\n");
      break;

    case trigger_debounce_release_st:
      printf("trigger_debounce_release_st\n");
      break;

    case trigger_release_st:
      printf("trigger_release_st\n");
      break;

    // Prints a default error message
    default:
      printf(DEFAULT_ERROR_MESSAGE);
      break;
    }
  }
}

// Standard tick function.
void trigger_tick() {
  // triggerDebugStatePrint();

  // Perform state update first.
  // Perform the Moore action based on trigger_currentState
  if (enableTrigger) { //&& (remainingShots > NO_SHOTS_REMAINING)) {
    // switch to handle state machine
    switch (trigger_currentState) {
    case init_st:
      trigger_currentState = trigger_wait_for_action_st;
      break;

    case trigger_wait_for_action_st:
      // if btn0 is pressed the start
      if (triggerPressed() && (remainingShots > NO_SHOTS_REMAINING) &&
          !invincibilityTimer_running()) {
        trigger_currentState = trigger_debounce_pull_st;
        counter = RESET_COUNTER;
      } else if (triggerPressed() && !invincibilityTimer_running()) {
        sound_playSound(sound_gunClick_e);
      }
      break;

    case trigger_debounce_pull_st:
      // debounces for 5ms
      if (counter == FIVE_MS_COUNTER) {
        trigger_currentState = trigger_pulled_st;
        remainingShots--;
        sound_playSound(sound_gunFire_e);
        printf("Remaining shots %d\n", remainingShots);
        autoReloadTimer_start();
        counter = RESET_COUNTER;
        transmitter_run();
        DPCHAR('D');
        DPCHAR('\n');
      } else if (!triggerPressed()) {
        trigger_currentState = trigger_wait_for_action_st;
        counter = RESET_COUNTER;
      }
      break;

    case trigger_pulled_st:
      // wait until btn is released
      if (!triggerPressed()) {
        autoReloadTimer_cancel();
        trigger_currentState = trigger_debounce_release_st;
        counter = RESET_COUNTER;
      }
      break;

    case trigger_debounce_release_st:
      // debounces released 5ms
      if (counter == FIVE_MS_COUNTER) {
        trigger_currentState = trigger_release_st;
        counter = RESET_COUNTER;
        DPCHAR('U');
        DPCHAR('\n');
      } else if (triggerPressed()) {
        trigger_currentState = trigger_pulled_st;
        counter = RESET_COUNTER;
      }
      break;

    case trigger_release_st:
      trigger_currentState = trigger_wait_for_action_st;
      break;

    // Prints a default error message
    default:
      printf(DEFAULT_ERROR_MESSAGE);
      break;
    }

    // Perform state action next.
    // Perform the Mealy actions base on trigger_currentState
    switch (trigger_currentState) {
    case init_st:
      break;

    case trigger_wait_for_action_st:
      break;

    case trigger_debounce_pull_st:
      counter++;
      break;

    case trigger_pulled_st:
      break;

    case trigger_debounce_release_st:
      counter++;
      break;

    case trigger_release_st:
      break;

    // Prints a default error message
    default:
      printf(DEFAULT_ERROR_MESSAGE);
      break;
    }
  }
}

// Runs the test continuously until BTN1 is pressed.
// The test just prints out a 'D' when the trigger or BTN0
// is pressed, and a 'U' when the trigger or BTN0 is released.
void trigger_runTest() {
  trigger_enable();
  remainingShots = INITIAL_SHOTS;

  // runs until btn 1 is pressed
  while (buttons_read() != BUTTONS_BTN1_MASK) {
    utils_sleep();
  }
  trigger_disable();

  // debounces
  do {
    utils_msDelay(DELAY_400_MS);
  } while (!buttons_read());
}
