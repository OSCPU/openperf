#ifndef __my_math_h__
#define __my_math_h__
#include <stdarg.h>

int my_vsprintf(char *buf, const char *fmt, va_list args);
int my_sprintf( char *s, const char *fmt, ... );
int my_printf(const char *fmt, ... );

#endif
