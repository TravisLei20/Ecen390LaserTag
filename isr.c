#include <stdint.h>
#include <stdio.h>

#include "hitLedTimer.h"
#include "include/interrupts.h"
#include "isr.h"
#include "lockoutTimer.h"
#include "sound.h"
#include "transmitter.h"
#include "trigger.h"

#define ADC_BUFFER_SIZE 100000
#define INITIAL_INDEX 0
#define RESET_COUNTER 0

// This implements a dedicated circular buffer for storing values
// from the ADC until they are read and processed by detector().
// adcBuffer_t is similar to a queue.
typedef struct {
  uint32_t indexIn;               // New values go here.
  uint32_t indexOut;              // Pull old values from here.
  uint32_t elementCount;          // Number of elements in the buffer.
  uint32_t data[ADC_BUFFER_SIZE]; // Values are stored here.
} adcBuffer_t;

// This is the instantiation of adcBuffer.
volatile static adcBuffer_t adcBuffer;

// Init adcBuffer.
void adcBufferInit() {
  adcBuffer.indexIn = INITIAL_INDEX;
  adcBuffer.indexOut = INITIAL_INDEX;
  adcBuffer.elementCount = RESET_COUNTER;

  // initialize the data buffer
  for (uint32_t i = 0; i < ADC_BUFFER_SIZE; i++) {
    adcBuffer.data[i] = 0;
  }
}

// This adds data to the ADC queue. Data are removed from this queue and used by
// the detector.
// Implemented as a fixed-size circular buffer.
// indexIn always points to an empty location (by definition).
// indexOut always points to the oldest element.
// Buffer is empty if indexIn == indexOut.
// Buffer is full if incremented indexIn == indexOut.
void isr_addDataToAdcBuffer(uint32_t adcData) {
  // if indexIn is at the top of the queue, wrap around to bottom
  if (adcBuffer.indexIn + 1 >= ADC_BUFFER_SIZE) {
    adcBuffer.indexIn = INITIAL_INDEX;
  }

  // increments the correct signal according to their status
  if (adcBuffer.indexIn == adcBuffer.indexOut) {
    // empty, count the new element
    adcBuffer.elementCount += 1;
    adcBuffer.indexIn += 1;
  } else if ((adcBuffer.indexIn + 1) == adcBuffer.indexOut) {
    // full, don't count the new element, overwrite oldest
    adcBuffer.indexOut += 1;
    adcBuffer.indexIn += 1;
  } else if (adcBuffer.elementCount == ADC_BUFFER_SIZE) {
    adcBuffer.indexIn += 1;
  } else {
    adcBuffer.elementCount += 1;
    adcBuffer.indexIn += 1;
  }

  adcBuffer.data[adcBuffer.indexIn] = adcData;
}

// Removes a single item from the ADC buffer.
// Does not signal an error if the ADC buffer is currently empty
// Simply returns a default value of 0 if the buffer is currently empty.
uint32_t isr_removeDataFromAdcBuffer() {
  uint32_t tempIndex = 0;

  // return zero if empty buffer
  if (adcBuffer.elementCount == 0) {
    return 0;
  }

  tempIndex = adcBuffer.indexOut;
  adcBuffer.indexOut += 1;

  // rolls over indexOut if necessary
  if (adcBuffer.indexOut >= ADC_BUFFER_SIZE) {
    adcBuffer.indexOut = INITIAL_INDEX;
  }

  adcBuffer.elementCount -= 1;
  return adcBuffer.data[tempIndex];
}

// This returns the number of values in the ADC buffer.
uint32_t isr_adcBufferElementCount() { return adcBuffer.elementCount; }

// Performs inits for anything in isr.c
void isr_init() {
  adcBufferInit();
  transmitter_init();
  trigger_init();
  hitLedTimer_init();
  lockoutTimer_init();
  sound_init();
}

// This function is invoked by the timer interrupt at 100 kHz.
void isr_function() {
  transmitter_tick();
  trigger_tick();
  hitLedTimer_tick();
  lockoutTimer_tick();
  isr_addDataToAdcBuffer(interrupts_getAdcData());
}