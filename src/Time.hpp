#ifndef _TIME_HPP_
#define _TIME_HPP_

#include <stdint.h>

#define MS_PER_TICK 10

typedef uint32_t time_t;

#define now() (currTime)
#define startTimer() (now())

#define msPassed(timer, ms) (currTime > (timer + ((MS_PER_TICK-1+ms)/MS_PER_TICK)))

#define msSince(time) ((currTime - (time))*MS_PER_TICK)

#define clockInit() currTime=0

extern time_t currTime;

#endif
