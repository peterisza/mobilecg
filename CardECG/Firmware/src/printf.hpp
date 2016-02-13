#ifndef _PRINTF_HPP_
#define _PRINTF_HPP_

#include <stdarg.h>

int vsnprintf(char *dest, int maxlen, const char *format, va_list vl);
void printf(const char *format, ...);

#endif
