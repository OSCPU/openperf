#ifndef UTIL_H
#define UTIL_H

#define Assert(cond, ...) \
  do { \
    if (!(cond)) { \
      printf("\33[1;31mAssert Failed"); \
      printf(__VA_ARGS__); \
      printf("\33[0m\n"); \
      while (1) ; \
    } \
  } while (0)

#endif
