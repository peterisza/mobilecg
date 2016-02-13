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
    //abort ();
  }

  heap_end += incr;
  return (caddr_t) prev_heap_end;
}
