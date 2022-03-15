#include "detector.h"
#include "filter.h"
#include "hitLedTimer.h"
#include "include/interrupts.h"
#include "lockoutTimer.h"
#include "runningModes.h"

#include <stdio.h>

bool interruptsEnabled;

#define TEST_DATA1                                                             \
  { 541.654, .001, 960, 1, 1000, 0, 0, 0.5, 1, 1 } // hit by player 4
#define TEST_DATA2                                                             \
  { 10000, 9005, 960, 1, 2000, 5000, 7845, 9845, 1, 951 } // no hit

#define RESET_COUNTER 0
#define ADC_MAX_VAL 4095
#define ADC_HALF_VAL 2047
#define FILTER_FREQUENCY_COUNT 10
#define HIGHEST_INDEX 9
#define MEDIAN_INDEX 4

#define FORCE_COMPUTE true
#define DEBUG_PRINT true
#define DETECTED true

#define ARRAY_SIZE 10
#define DECIMATION_FACTOR 10

static uint8_t addInputCount = 0;
static bool hitDetected = !DETECTED;
static detector_hitCount_t hitCountArray[FILTER_FREQUENCY_COUNT];
static bool ignoredFrequenciesArray[FILTER_FREQUENCY_COUNT];
static bool ignoreAll;
static uint16_t lastHitFrequency;
static uint32_t fudgeFactor = 750;

//////////////////////////////
//      Cursor Parking      //
//                          //
//////////////////////////////

/*
Test circular queue and if we can detect hits only changing the fudge factor
with data given on wiki
*/

// Encapsulate ADC scaling for easier testing.
double detector_getScaledAdcValue(isr_AdcValue_t adcValue) {
  double scaledValue = (((double)adcValue - ADC_HALF_VAL) / ADC_HALF_VAL);
  return scaledValue;
}

// Always have to init things.
// bool array is indexed by frequency number, array location set for true to
// ignore, false otherwise. This way you can ignore multiple frequencies.
void detector_init(bool ignoredFrequencies[]) {
  interruptsEnabled = false;
  for (uint8_t i = 0; i < FILTER_FREQUENCY_COUNT; i++) {
    ignoredFrequenciesArray[i] = ignoredFrequencies[i];
    hitCountArray[i] = RESET_COUNTER;
  }
  filter_init();
}

// get power arrays and sort to check for hit
void detector_detectHit() {
  double sortedArray[FILTER_FREQUENCY_COUNT] = TEST_DATA2;   // TEST_DATA1;
  double originalArray[FILTER_FREQUENCY_COUNT] = TEST_DATA2; // TEST_DATA1;
  double medianPower;
  uint8_t highestIndex = 0;

  filter_getCurrentPowerValues(sortedArray);
  filter_getCurrentPowerValues(originalArray);

  // do power sorting and multiply by fudge factor
  for (uint8_t i = 0; i < FILTER_FREQUENCY_COUNT; i++) {
    uint8_t jMin = i;
    for (uint8_t j = i + 1; j < FILTER_FREQUENCY_COUNT; j++) {
      if (sortedArray[j] < sortedArray[jMin]) {
        jMin = j;
      }
      if (originalArray[j] > originalArray[highestIndex]) {
        highestIndex = j;
      }
    }
    if (jMin != i) {
      double temp = sortedArray[i];
      sortedArray[i] = sortedArray[jMin];
      sortedArray[jMin] = temp;
    }
  }

  medianPower = sortedArray[MEDIAN_INDEX] * fudgeFactor;

  if (!ignoredFrequenciesArray[highestIndex] &&
      (sortedArray[HIGHEST_INDEX] > medianPower) && !ignoreAll) {
    hitCountArray[highestIndex] += 1;
    hitDetected = DETECTED;
    lastHitFrequency = highestIndex;
  }
}

// Runs the entire detector: decimating fir-filter, iir-filters,
// power-computation, hit-detection. if interruptsNotEnabled = true, interrupts
// are not running. If interruptsNotEnabled = true you can pop values from the
// ADC queue without disabling interrupts. If interruptsNotEnabled = false, do
// the following:
// 1. disable interrupts.
// 2. pop the value from the ADC queue.
// 3. re-enable interrupts if interruptsNotEnabled was true.
// if ignoreSelf == true, ignore hits that are detected on your frequency.
// Your frequency is simply the frequency indicated by the slide switches
void detector(bool interruptsCurrentlyEnabled) {
  uint32_t elementCount = isr_adcBufferElementCount();
  double rawAdcValue;
  double scaledAdcValue;

  for (uint32_t i = 0; i < elementCount; i++) {
    if (interruptsCurrentlyEnabled == true) {
      interrupts_disableArmInts();
    }

    rawAdcValue = isr_removeDataFromAdcBuffer();

    if (interruptsCurrentlyEnabled == true) {
      interrupts_enableArmInts();
    }

    scaledAdcValue = detector_getScaledAdcValue(rawAdcValue);
    filter_addNewInput(scaledAdcValue);
    addInputCount += 1;

    if (addInputCount >= DECIMATION_FACTOR) {
      addInputCount = RESET_COUNTER;
      filter_firFilter();
      for (uint8_t i = 0; i < FILTER_FREQUENCY_COUNT; i++) {
        filter_iirFilter(i);
        filter_computePower(i, !FORCE_COMPUTE, !DEBUG_PRINT);
      }
      if (!lockoutTimer_running()) {
        // run hit detection
        detector_detectHit();

        if (hitDetected) {
          lockoutTimer_start();
          hitLedTimer_start();
        }
      }
    }
  }
}

// Returns true if a hit was detected.
bool detector_hitDetected() { return hitDetected; }

// Returns the frequency number that caused the hit.
uint16_t detector_getFrequencyNumberOfLastHit() { return lastHitFrequency; }

// Clear the detected hit once you have accounted for it.
void detector_clearHit() { hitDetected = !DETECTED; }

// Ignore all hits. Used to provide some limited invincibility in some game
// modes. The detector will ignore all hits if the flag is true, otherwise will
// respond to hits normally.
void detector_ignoreAllHits(bool flagValue) { ignoreAll = flagValue; }

// Get the current hit counts.
// Copy the current hit counts into the user-provided hitArray
// using a for-loop.
void detector_getHitCounts(detector_hitCount_t hitArray[]) {
  for (uint8_t i = 0; i < FILTER_FREQUENCY_COUNT; i++) {
    hitArray[i] = hitCountArray[i];
  }
}

// Allows the fudge-factor index to be set externally from the detector.
// The actual values for fudge-factors is stored in an array found in detector.c
void detector_setFudgeFactorIndex(uint32_t factor) { fudgeFactor = factor; }

/*******************************************************
 ****************** Test Routines **********************
 ******************************************************/

// Students implement this as part of Milestone 3, Task 3.
void detector_runTest() {
  // Isolated
  printf("running detect hit with 750\n");
  detector_setFudgeFactorIndex(750);
  detector_detectHit();

  if (hitDetected) {
    printf("HIT DETECTED BY PLAYER %d\n", lastHitFrequency);
  } else {
    printf("No hit detected.\n");
  }

  printf("running detect hit with 400\n");
  detector_setFudgeFactorIndex(400);
  detector_detectHit();

  if (hitDetected) {
    printf("HIT DETECTED BY PLAYER %d\n", lastHitFrequency);
  } else {
    printf("No hit detected.\n");
  }

  printf("running detect hit with \n");
  detector_setFudgeFactorIndex(200);
  detector_detectHit();

  if (hitDetected) {
    printf("HIT DETECTED BY PLAYER %d\n", lastHitFrequency);
  } else {
    printf("No hit detected.\n");
  }

  detector_clearHit();
}
