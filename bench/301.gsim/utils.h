#ifndef __UTILS_H__
#define __UTILS_H__

#define ANSI_FG_BLACK      "\33[1;30m"
#define ANSI_FG_RED        "\33[1;31m"
#define ANSI_FG_GREEN      "\33[1;32m"
#define ANSI_FG_YELLOW     "\33[1;33m"
#define ANSI_FG_BLUE       "\33[1;34m"
#define ANSI_FG_MAGENTA    "\33[1;35m"
#define ANSI_FG_CYAN       "\33[1;36m"
#define ANSI_FG_WHITE      "\33[1;37m"
#define ANSI_NONE          "\33[0m"
#define ANSI_FMT(str, fmt) fmt str ANSI_NONE

#define Log(format, ...) \
  printf(ANSI_FMT("[%s:%d %s] " format, ANSI_FG_MAGENTA) "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__)

#define Assert(cond, format, ...)                                         \
  do {                                                                    \
    if (!(cond)) {                                                        \
      fflush(stdout);                                                     \
      fprintf(stderr, ANSI_FMT(format, ANSI_FG_RED) "\n", ##__VA_ARGS__); \
      assert(cond);                                                       \
    }                                                                     \
  } while (0)

#endif
