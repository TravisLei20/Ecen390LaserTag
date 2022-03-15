#include "hitLedTimer.h"

#include "drivers/buttons.h"
#include "include/leds.h"
#include "utils.h"

#include <stdint.h>
#include <stdio.h>

#include "mio.h"

#define LED_ON_COUNT 50000
#define LED_OFF 0x0
#define HIT_LED_ON 0x2
#define ON 1
#define OFF 0
#define RESET_COUNTER 0
#define ENABLE true
#define RUNNING true
#define DELAY_400_MS 400
#define DELAY_300_MS 300

volatile uint16_t LedCounter = 0;

volatile static bool hitTimerEnable;
volatile static bool hitTimerRunning;

// The state names in the state-machine
volatile static enum hitLedTimer_st_t {
  hitLed_init_st,
  hitLed_wait_st,
  hitLed_run_st
} hitTimer_currentState;

// Calling this starts the timer.
void hitLedTimer_start() { hitTimerRunning = RUNNING; }

// Returns true if the timer is currently running.
bool hitLedTimer_running() { return hitTimerRunning; }

// Standard tick function.
void hitLedTimer_tick() {
  // switch to handle state machine
  switch (hitTimer_currentState) {
  case hitLed_init_st:
    hitTimer_currentState = hitLed_wait_st;
    break;

  case hitLed_wait_st:
    // if hit timer is enabled and running it will start
    if (hitTimerEnable && hitTimerRunning) {
      hitTimer_currentState = hitLed_run_st;
      LedCounter = RESET_COUNTER;
      hitLedTimer_turnLedOn();
    }
    break;

  case hitLed_run_st:
    LedCounter++;
    // when the count reaches LED_ON_COUNT it will turn off
    if (LedCounter == LED_ON_COUNT) {
      hitTimer_currentState = hitLed_wait_st;
      hitTimerRunning = !RUNNING;
      hitLedTimer_turnLedOff();
    }
    break;
  }
}

// Need to init things.
void hitLedTimer_init() {
  mio_init(false);
  mio_setPinAsOutput(HIT_LED_TIMER_OUTPUT_PIN);
  hitTimer_currentState = hitLed_init_st;
  hitTimerEnable = ENABLE;
}

// Turns the gun's hit-LED on.
void hitLedTimer_turnLedOn() {
  leds_write(ON);
  mio_writePin(HIT_LED_TIMER_OUTPUT_PIN, ON);
}

// Turns the gun's hit-LED off.
void hitLedTimer_turnLedOff() {
  leds_write(LED_OFF);
  mio_writePin(HIT_LED_TIMER_OUTPUT_PIN, LED_OFF);
}

// Disables the hitLedTimer.
void hitLedTimer_disable() { hitTimerEnable = !ENABLE; }

// Enables the hitLedTimer.
void hitLedTimer_enable() { hitTimerEnable = ENABLE; }

// Runs a visual test of the hit LED.
// The test continuously blinks the hit-led on and off.
void hitLedTimer_runTest() {
  leds_init(OFF);
  // runs until btn1 is pressed
  while (buttons_read() != BUTTONS_BTN1_MASK) {
    hitLedTimer_start();
    // runs until hitLedTimer is done
    while (hitLedTimer_running()) {
      ;
    }
    utils_msDelay(DELAY_300_MS);
  }
  hitLedTimer_disable();
  printf("hitLedTimer test Done\n\n");

  // debounces
  do {
    utils_msDelay(DELAY_400_MS);
  } while (buttons_read());
}