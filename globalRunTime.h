#ifndef GLOBALRUNTIME_H_
#define GLOBALRUNTIME_H_

#include <stdbool.h>
#include <stdint.h>

// Calling this starts the timer.
void globalRunTime_start(uint16_t minutes);

// Perform any necessary inits for the invincibility timer.
void globalRunTime_init();

// Returns true if the timer is running.
bool globalRunTime_running();

// Standard tick function.
void globalRunTime_tick();

#endif /* GLOBALRUNTIME_H_ */
