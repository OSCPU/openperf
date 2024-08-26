#ifndef __BENCH_DEBUG_H
#define __BENCH_DEBUG_H
#include <stdarg.h>

int bench_vsprintf(char *buf, const char *fmt, va_list args);
int bench_sprintf( char *s, const char *fmt, ... );
int bench_printf(const char *fmt, ... );

#endif
