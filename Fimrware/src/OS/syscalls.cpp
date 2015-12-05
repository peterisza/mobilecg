#include <errno.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <sys/unistd.h>
#include "stm32f4xx_hal.h"

extern "C" caddr_t _sbrk(int incr)
{
  extern char _ebss; // Defined by the linker
  static char *heap_end;
  char *prev_heap_end;

  if (heap_end == 0)
  {
    heap_end = &_ebss;
  }
  prev_heap_end = heap_end;

  char * stack = (char*) __get_MSP();
  if (heap_end + incr > stack)
  {
    errno = ENOMEM;
    return (caddr_t) -1;
    //abort ();
  }

  heap_end += incr;
  return (caddr_t) prev_heap_end;
}
