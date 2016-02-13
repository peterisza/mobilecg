/*
 * This file is part of MobilECG, an open source clinical grade Holter
 * ECG. For more information visit http://mobilecg.hu
 *
 * Copyright (C) 2016  Robert Csordas, Peter Isza
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
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
