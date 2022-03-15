#include "utils.h"
#include <stdio.h>

#include "filter.h"
#include "transmitter.h"

#include "include/mio.h"

#include "drivers/buttons.h"
#include "drivers/switches.h"
#define TRANSMITTER_TEST_TICK_PERIOD_IN_MS 10
#define BOUNCE_DELAY 5
#define TRANSMITTER_OUTPUT_PIN 13
#define TRANSMITTER_HIGH_VALUE 1
#define TRANSMITTER_LOW_VALUE 0
#define DEFAULT_ERROR_MESSAGE "Wrong!!!"
#define BEGIN true
#define COMPLETE false
#define IGNORE false
#define RESET_COUNTER 0
#define DIVIDE_HALF 2
#define DELAY_400_MS 400
#define DELAY_300_MS 300
#define INITIAL_VOLTAGE 10
#define LOW_PIN_VOLTAGE 0
#define SIGNAL_200_MS 20000

volatile static uint16_t currFrequencyNumber;
volatile static uint8_t nextPeriod;
volatile static uint8_t nextHalfPeriod;
volatile static uint8_t currHalfPeriod;

volatile static bool running;

volatile static bool continuousRun;

volatile static uint16_t count;
volatile static uint16_t totalCount;

// This sets the jf1 pin high
void transmitter_set_jf1_to_one() {
  mio_writePin(TRANSMITTER_OUTPUT_PIN, TRANSMITTER_HIGH_VALUE);
}

// This sets the jf1 pin low
void transmitter_set_jf1_to_zero() {
  mio_writePin(TRANSMITTER_OUTPUT_PIN, TRANSMITTER_LOW_VALUE);
}

// The state names in the state-machine
volatile static enum transmitter_st_t {
  init_st,
  wait_for_startFlag_st,
  output_low_st,
  output_high_st,
  transmitter_result_st
} transmitter_currentState;

// Standard init function.
void transmitter_init() {
  mio_setPinAsOutput(TRANSMITTER_OUTPUT_PIN);
  transmitter_currentState = init_st;
  running = !BEGIN;
}

// Starts the transmitter.
void transmitter_run() { running = BEGIN; }

// Returns true if the transmitter is still running.
bool transmitter_running() { return running; }

// Sets the frequency number. If this function is called while the
// transmitter is running, the frequency will not be updated until the
// transmitter stops and transmitter_run() is called again.
void transmitter_setFrequencyNumber(uint16_t frequencyNumber) {
  currFrequencyNumber = frequencyNumber;
  nextPeriod =
      filter_frequencyTickTable[frequencyNumber]; // clock cycles per period
  nextHalfPeriod = nextPeriod / DIVIDE_HALF;
}

// Returns the current frequency setting.
uint16_t transmitter_getFrequencyNumber() { return currFrequencyNumber; }

// Standard tick function.
void transmitter_tick() {
  // Perform state update first.
  // Operates the state-machine
  switch (transmitter_currentState) {
  case init_st:
    transmitter_currentState = wait_for_startFlag_st;
    break;

  case wait_for_startFlag_st:
    // if the pin is not equal to zero then set the jf1 pin low
    if (mio_readPin(TRANSMITTER_OUTPUT_PIN) != LOW_PIN_VOLTAGE) {
      transmitter_set_jf1_to_zero();
    }

    // if it's still running then go to the low state and reset counters
    if (running || continuousRun) {
      transmitter_currentState = output_low_st;
      currHalfPeriod = nextHalfPeriod;
      count = RESET_COUNTER;
      totalCount = RESET_COUNTER;
    }

    break;

  case output_low_st:
    count++;
    totalCount++;

    // If totalCount is greater than or equal to SIGNAL_200_MS
    // then set jf1 to zero and set running to complete and reset counters
    if (totalCount >= SIGNAL_200_MS) {
      transmitter_set_jf1_to_zero();
      transmitter_currentState = transmitter_result_st;
      running = COMPLETE;
      count = RESET_COUNTER;
      totalCount = RESET_COUNTER;
    }

    // If count has reached half then set jf1 high and reset counter
    else if (count == currHalfPeriod) {
      transmitter_currentState = output_high_st;
      transmitter_set_jf1_to_one();
      count = RESET_COUNTER;
    }

    break;

  case output_high_st:
    count++;
    totalCount++;

    // If totalCount is greater than or equal to SIGNAL_200_MS
    // then set jf1 to zero and set running to complete and reset counters
    if ((totalCount >= SIGNAL_200_MS)) {
      transmitter_set_jf1_to_zero();
      transmitter_currentState = transmitter_result_st;
      running = COMPLETE;
      count = RESET_COUNTER;
      totalCount = RESET_COUNTER;
    }

    // if count is equal to half then jf1 is set to zero and count is reset
    else if (count == currHalfPeriod) {
      transmitter_currentState = output_low_st;
      transmitter_set_jf1_to_zero();
      count = RESET_COUNTER;
    }

    break;

  case transmitter_result_st:
    transmitter_currentState = wait_for_startFlag_st;
    break;

  // Prints a default error message
  default:
    printf(DEFAULT_ERROR_MESSAGE);
    break;
  }
}

static uint16_t previousVoltage = INITIAL_VOLTAGE;

// Tests the transmitter.
void transmitter_runTest() {
  printf("starting transmitter_runTest()\n");
  mio_init(false);
  buttons_init();     // Using buttons
  switches_init();    // and switches.
  transmitter_init(); // init the transmitter.
  transmitter_setContinuousMode(false);
  transmitter_run();

  // runs until btn 1 is pressed
  while (buttons_read() != BUTTONS_BTN1_MASK) {
    uint16_t switchValue = switches_read() % FILTER_FREQUENCY_COUNT;
    transmitter_setFrequencyNumber(switchValue);
    transmitter_run();

    // runs until state machine is finished
    while (transmitter_running()) {

      utils_msDelay(TRANSMITTER_TEST_TICK_PERIOD_IN_MS);
      printf("%d ", mio_readPin(TRANSMITTER_OUTPUT_PIN));

      // prints when switches of values occur
      if (mio_readPin(TRANSMITTER_OUTPUT_PIN) != previousVoltage) {
        previousVoltage = mio_readPin(TRANSMITTER_OUTPUT_PIN);
        printf("\n");
        printf("total count %d\n", totalCount);
      }
    }
    printf(" \ncompleted one test period.\n");
  }

  // btn debounces
  do {
    utils_msDelay(DELAY_400_MS);
  } while (buttons_read());
  printf("exiting transmitter_runTest()\n");
}

// Runs the transmitter continuously.
// if continuousModeFlag == true, transmitter runs continuously, otherwise,
// transmits one pulse-width and stops. To set continuous mode, you must
// invoke
// this function prior to calling transmitter_run(). If the transmitter is
// in currently in continuous mode, it will stop running if this function is
// invoked with continuousModeFlag == false. It can stop immediately or wait
// until the last 200 ms pulse is complete. NOTE: while running
// continuously, the transmitter will change frequencies at the end of each
// 200 ms pulse.
void transmitter_setContinuousMode(bool continuousModeFlag) {
  continuousRun = continuousModeFlag;
}

// Tests the transmicontinuousModeFlag;uous mode.
// The test runs until BTN1 is pressed.
// To perform the test, connect the oscilloscope probe
// to the transmitter and ground probes on the development board
// prior to running this test. You should see about a 300 ms dead
// spot between 200 ms pulses.
// Should change frequency in response to the slide switches.
void transmitter_runNoncontinuousTest() {
  printf("starting transmitter_runNoncontinuousTest()\n");
  mio_init(false);
  transmitter_setContinuousMode(false);

  // runs until btn 1 is pressed
  while (buttons_read() != BUTTONS_BTN1_MASK) {

    uint16_t switchValue = switches_read() % FILTER_FREQUENCY_COUNT;
    transmitter_setFrequencyNumber(switchValue);
    transmitter_run();

    // runs till state machine is finished
    while (transmitter_running()) {
      utils_sleep();
    }
    utils_msDelay(DELAY_300_MS);
  }
  // debounces
  do {
    utils_msDelay(DELAY_400_MS);
  } while (!buttons_read());
}

// Tests the transmitter in continuous mode.
// To perform the test, connect the oscilloscope probe
// to the transmitter and ground probes on the development board
// prior to running this test.
// Transmitter should continuously generate the proper waveform
// at the transmitter-probe pin and change frequencies
// in response to changes to the changes in the slide switches.
// Test runs until BTN1 is pressed.
void transmitter_runContinuousTest() {
  printf("starting transmitter_runContinuousTest()\n");
  mio_init(IGNORE);
  buttons_init();     // Using buttons
  switches_init();    // and switches.
  transmitter_init(); // init the transmitter.
  transmitter_setContinuousMode(true);
  transmitter_run();

  // runs until btn 1 is pressed
  while (buttons_read() != BUTTONS_BTN1_MASK) {
    uint16_t switchValue = switches_read() % FILTER_FREQUENCY_COUNT;
    transmitter_setFrequencyNumber(switchValue);

    utils_msDelay(TRANSMITTER_TEST_TICK_PERIOD_IN_MS);
  }

  transmitter_setContinuousMode(false);

  // debounces
  do {
    utils_msDelay(DELAY_400_MS);
  } while (buttons_read());
}