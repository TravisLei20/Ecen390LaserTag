/*
This software is provided for student assignment use in the Department of
Electrical and Computer Engineering, Brigham Young University, Utah, USA.
Users agree to not re-host, or redistribute the software, in source or binary
form, to other persons or other institutions. Users may modify and use the
source code for personal or educational use.
For questions, contact Brad Hutchings or Jeff Goeders, https://ece.byu.edu/
*/

#include "interrupts.h"
//#include "runningModes.h"

#include "autoReloadTimer.h"

#include "detector.h"
#include "display.h"
#include "drivers/buttons.h"
#include "drivers/intervalTimer.h"
#include "drivers/switches.h"
#include "filter.h"
#include "globalRunTime.h"
#include "histogram.h"
#include "hitLedTimer.h"
#include "interrupts.h"
#include "invincibilityTimer.h"
#include "isr.h"
#include "ledTimer.h"
#include "leds.h"
#include "lockoutTimer.h"
#include "mio.h"
#include "queue.h"
#include "sound.h"
#include "transmitter.h"
#include "trigger.h"
#include "utils.h"
#include "xparameters.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
This file (runningModes2.c) is separated from runningModes.c so that
check_and_zip.py does not include provided code for grading. Code for
submission can be added to this file and will be graded. The code in
runningModes.c can give you some ideas about how to implement other
modes here.
*/

// Uncomment this code so that the code in the various modes will
// ignore your own frequency. You still must properly implement
// the ability to ignore frequencies in detector.c
#define IGNORE_OWN_FREQUENCY 1

#define MAX_HIT_COUNT 3

#define MAX_BUFFER_SIZE 100 // Used for a generic message buffer.

#define DETECTOR_HIT_ARRAY_SIZE                                                \
  FILTER_FREQUENCY_COUNT // The array contains one location per user frequency.

#define HISTOGRAM_BAR_COUNT                                                    \
  FILTER_FREQUENCY_COUNT // As many histogram bars as user filter frequencies.

#define ISR_CUMULATIVE_TIMER INTERVAL_TIMER_TIMER_0 // Used by the ISR.
#define TOTAL_RUNTIME_TIMER                                                    \
  INTERVAL_TIMER_TIMER_1 // Used to compute total run-time.
#define MAIN_CUMULATIVE_TIMER                                                  \
  INTERVAL_TIMER_TIMER_2 // Used to compute cumulative run-time in main.

#define SYSTEM_TICKS_PER_HISTOGRAM_UPDATE                                      \
  30000 // Update the histogram about 3 times per second.

#define RUNNING_MODE_WARNING_TEXT_SIZE 2 // Upsize the text for visibility.
#define RUNNING_MODE_WARNING_TEXT_COLOR DISPLAY_RED // Red for more visibility.
#define RUNNING_MODE_NORMAL_TEXT_SIZE 1 // Normal size for reporting.
#define RUNNING_MODE_NORMAL_TEXT_COLOR DISPLAY_WHITE // White for reporting.
#define RUNNING_MODE_SCREEN_X_ORIGIN 0 // Origin for reporting text.
#define RUNNING_MODE_SCREEN_Y_ORIGIN 0 // Origin for reporting text.

// Detector should be invoked this often for good performance.
#define SUGGESTED_DETECTOR_INVOCATIONS_PER_SECOND 30000
// ADC queue should have no more than this number of unprocessed elements for
// good performance.
#define SUGGESTED_REMAINING_ELEMENT_COUNT 500

// Defined to make things more readable.
#define INTERRUPTS_CURRENTLY_ENABLED true
#define INTERRUPTS_CURRENTLY_DISABLE false

#define TEAM_A_FREQUENCY 6
#define TEAM_B_FREQUENCY 9
#define ZOMBIE_LIVES 3
#define HUMAN_LIVES 1
#define STARTING_SHOTS 10
#define DEAD 0
#define RESET_COUNTER 0
#define NO_SHOTS_REMAINING 0
#define STARTED true
#define IGNORE true

#define FIVE_SECONDS 5
#define GAME_TIME 3 // run for three minutes

static sound_sounds_t sound;
static sound_volume_t volume;

// Keep track of detector invocations.
volatile static uint32_t detectorInvocationCount = 0;

volatile static uint8_t playerLives = HUMAN_LIVES;

volatile static bool automaticReloadStarted = !STARTED;

// This array is indexed by frequency number. If array-element[freq_no] == true,
// the frequency is ignored, e.g., no hit will ever occur at that frequency.
static bool ignoredFrequenciesArray[FILTER_FREQUENCY_COUNT] = {
    IGNORE, IGNORE,  IGNORE, IGNORE, IGNORE,
    IGNORE, !IGNORE, IGNORE, IGNORE, !IGNORE}; // player 6 and 9 possible

// Group all of the inits together to reduce visual clutter.
void runningModes_initAll() {
  intervalTimer_initAll();
  histogram_init(HISTOGRAM_BAR_COUNT);
  filter_init();
  sound_init();
  isr_init();
  globalRunTime_start(GAME_TIME);
}

// Returns the current switch-setting
uint16_t runningModes_getFrequencySetting() {
  uint16_t switchSetting =
      switches_read() & SWITCHES_SW0_MASK; // Bit-mask the results.

  // Ignores the correct frequency
  // TEAM A is humans
  // TEAM B is zombies
  if (!switchSetting) {
    ignoredFrequenciesArray[TEAM_A_FREQUENCY] = IGNORE_OWN_FREQUENCY;
    playerLives = HUMAN_LIVES;
    return TEAM_A_FREQUENCY;
  } else {
    ignoredFrequenciesArray[TEAM_B_FREQUENCY] = IGNORE_OWN_FREQUENCY;
    playerLives = ZOMBIE_LIVES;
    return TEAM_B_FREQUENCY;
  }
}

uint16_t toZombieTeam() {
  ignoredFrequenciesArray[TEAM_A_FREQUENCY] = !IGNORE_OWN_FREQUENCY;
  ignoredFrequenciesArray[TEAM_B_FREQUENCY] = IGNORE_OWN_FREQUENCY;
  return TEAM_B_FREQUENCY;
}

void shooterModeInits() {
  interrupts_initAll(true);
  interrupts_enableTimerGlobalInts();
  interrupts_startArmPrivateTimer();
  intervalTimer_reset(ISR_CUMULATIVE_TIMER);
  intervalTimer_reset(TOTAL_RUNTIME_TIMER);
  intervalTimer_reset(MAIN_CUMULATIVE_TIMER);
  intervalTimer_start(TOTAL_RUNTIME_TIMER);
  interrupts_enableArmInts();
}

// This is the function that does most of the work
// It has most of the logic for this two team mode
void runningModes_shooter() {
  uint16_t hitCount = RESET_COUNTER;
  uint16_t histogramSystemTicks = RESET_COUNTER;
  detectorInvocationCount = RESET_COUNTER;

  trigger_enable();
  lockoutTimer_start();

  // As long as button 3 isn't pressed and the player hasn't lost all of his/her
  // lives then continue

  while (((buttons_read() != BUTTONS_BTN3_MASK)) && (playerLives > DEAD) &&
         (globalRunTime_running())) {           // main suspicion globalRunTime
    intervalTimer_start(MAIN_CUMULATIVE_TIMER); // Measure run-time
    histogramSystemTicks++;    // Keep track of ticks to update the histogram.
    detectorInvocationCount++; // Used for run-time statistics.
    detector(INTERRUPTS_CURRENTLY_ENABLED); // Interrupts are currently enabled.

    if (transmitter_getFrequencyNumber() == TEAM_B_FREQUENCY &&
        !sound_isBusy()) {
      sound_playSound(sound_zombie_e);
    }

    // If a hit is detected or button 1 is pressed
    if ((detector_hitDetected() || (buttons_read() == BUTTONS_BTN2_MASK)) &&
        !invincibilityTimer_running()) { // Hit detected
      // printf("HEY! A HIT WAS DETECTED IN RUNNING MODES 2\n");
      hitCount++;          // increment the hit count.
      detector_clearHit(); // Clear the hit.
      detector_hitCount_t hitCounts[DETECTOR_HIT_ARRAY_SIZE];

      detector_getHitCounts(hitCounts);  // Get the current hit counts.
      histogram_plotUserHits(hitCounts); // Plot the hit counts on the TFT.

      printf("Hit Count is %d\n", hitCount);

      // If hitCount has reached its limit then the player looses a life
      // Respective sounds will play
      if (hitCount >= MAX_HIT_COUNT) {
        playerLives--;
        printf("Lives left %d\n", playerLives);
        sound_playSound(sound_loseLife_e);
        hitCount = RESET_COUNTER;
      } else {
        sound_playSound(sound_hit_e);
      }

      // invincible for 5 seconds
      invincibilityTimer_start(FIVE_SECONDS);
    }

    // If player runs out of shoots then the autoReloadTimer will start
    if ((trigger_getRemainingShotCount() <= NO_SHOTS_REMAINING)) {
      autoReloadTimer_start();
    }

    intervalTimer_stop(MAIN_CUMULATIVE_TIMER);
  }

  printf("Shooter mode terminated after detecting %d shots.\n", hitCount);
  trigger_disable();
}

// This is the function that initializes the things that need to be initialized
// It also is the one that is called from main
void runningModes_zombie() {
  /////////              Completed tasks              //////////
  // set up zombie team - team b is zombie
  // human -> zombie transition
  // global run timer - globalRunTime.h mimics invincibility timer

  ////////                  TODO                /////////
  // zombie sounds

  uint16_t hitCount = RESET_COUNTER;

  printf("Starting runningModes_twoTeams\n");

  transmitter_setFrequencyNumber(runningModes_getFrequencySetting());
  // printf("initial frequency number: %d\n", transmitter_getFrequencyNumber());
  detector_init(ignoredFrequenciesArray);
  runningModes_initAll();
  // More initialization...

  sound_setVolume(sound_mediumHighVolume_e);
  printf("play starting sound\n");
  sound_playSound(sound_gameStart_e);

  trigger_setRemainingShotCount(STARTING_SHOTS);
  printf("Total shots available %d\n", trigger_getRemainingShotCount());

  // Implement game loop...
  shooterModeInits();
  runningModes_shooter();

  bool soundAlternate = true;

  while (!globalRunTime_running() &&
         transmitter_getFrequencyNumber() != TEAM_B_FREQUENCY) {
    // if the sound in complete then start another sound
    if (sound_isSoundComplete()) {
      // If soundAlternate is true then sound the return to base
      // Else start the one second of silence
      if (soundAlternate) {

        sound_setSound(sound_victory_e);
        sound_startSound();

        soundAlternate = false;
      } else if (!soundAlternate) {

        sound_setSound(sound_oneSecondSilence_e);
        sound_startSound();

        soundAlternate = true;
      }
    }
  }

  sound_playSound(sound_gameOver_e);

  // if not already zombie, move to zombie team
  if (transmitter_getFrequencyNumber() != TEAM_B_FREQUENCY) {
    transmitter_setFrequencyNumber(toZombieTeam());
    detector_init(ignoredFrequenciesArray);
    // printf("new frequency number: %d\n", transmitter_getFrequencyNumber());
    playerLives = ZOMBIE_LIVES;

    runningModes_shooter();
  }

  printf("Two-team mode terminated\n");

  while (!globalRunTime_running()) {
    // if the sound in complete then start another sound
    if (sound_isSoundComplete()) {
      // If soundAlternate is true then sound the return to base
      // Else start the one second of silence
      if (soundAlternate) {

        sound_setSound(sound_failure_e);
        sound_startSound();

        soundAlternate = false;
      } else if (!soundAlternate) {

        sound_setSound(sound_oneSecondSilence_e);
        sound_startSound();

        soundAlternate = true;
      }
    }
  }

  // Always runs and instructs the player
  while (1) {
    // if the sound in complete then start another sound
    if (sound_isSoundComplete()) {
      // If soundAlternate is true then sound the return to base
      // Else start the one second of silence
      if (soundAlternate) {

        sound_setSound(sound_returnToBase_e);
        sound_startSound();

        soundAlternate = false;
      } else if (!soundAlternate) {

        sound_setSound(sound_oneSecondSilence_e);
        sound_startSound();

        soundAlternate = true;
      }
    }
  }

  interrupts_disableArmInts(); // disable the interrupts.
  hitLedTimer_turnLedOff();    // Save power :-)
}
