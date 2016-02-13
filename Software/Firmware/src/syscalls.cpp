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
 
#include <errno.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <sys/unistd.h>
#include "stm32f4xx_hal.h"
#include <Logger.h>

extern "C" char _heap;
extern "C" char _eheap;

extern "C" caddr_t _sbrk(int incr)
{
  static char *heap_end=0;
  char *prev_heap_end;

  if (heap_end == 0)
  {
    heap_end = &_heap;
  }
  prev_heap_end = heap_end;

  if (heap_end + incr > &_eheap)
  {
    errno = ENOMEM;
    Logger::panic("_sbrk(): Out of heap.");
    return (caddr_t) -1;
  }

  heap_end += incr;
  return (caddr_t) prev_heap_end;
}
