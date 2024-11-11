#ifndef __BENCH_DEBUG_H
#define __BENCH_DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>

#define ANSI_ERROR "\33[1;31m"
#define ANSI_WARN "\33[1;93m"
#define ANSI_INFO "\33[1;34m"
#define ANSI_DEBUG "\33[1;32m"
#define ANSI_TRACE "\33[1;90m"
#define ANSI_NONE "\33[0m"

#ifndef LOG_LEVEL
#define LOG_LEVEL 2
#endif

#define LOG_LEVEL_ERROR 0
#define LOG_LEVEL_WARN 1
#define LOG_LEVEL_INFO 2
#define LOG_LEVEL_DEBUG 3
#define LOG_LEVEL_TRACE 4

#define ANSI_FMT(str, fmt) fmt str ANSI_NONE "\n"

#define BENCH_LOG(level, str, ...)                                             \
  do {                                                                         \
    if (LOG_LEVEL >= LOG_LEVEL_##level) {                                      \
      bench_printf(ANSI_FMT(str, ANSI_##level), ##__VA_ARGS__);                \
    }                                                                          \
  } while (0)

int bench_vsprintf(char *buf, const char *fmt, va_list args);
int bench_sprintf(char *s, const char *fmt, ...);
int bench_printf(const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif
