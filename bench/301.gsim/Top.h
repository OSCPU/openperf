#ifndef Top_H
#define Top_H

#include <bench.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// User configuration
//#define ENABLE_LOG
//#define RANDOMIZE_INIT

#define gAssert(cond, ...) \
  do {                     \
    if (!(cond)) {         \
      printf("\33[1;31m"); \
      printf(__VA_ARGS__); \
      printf("\33[0m\n");  \
      assert(cond);        \
    }                      \
  } while (0)
#define gdiv(a, b) ((b) == 0 ? 0 : (a) / (b))

#define likely(x)   __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
void gprintf(const char *fmt, ...);
void NPCTrap(uint8_t _0, uint32_t _1, uint32_t _2, uint8_t _3, uint32_t _4, uint8_t _5, uint32_t _6, uint8_t _7);
void SimDMEM(uint8_t _0, uint32_t _1, uint32_t *_2, uint8_t _3, uint32_t _4, uint32_t _5, uint8_t _6);

void STop_init();
void init();
void activateAll();
void set_clock(uint8_t val);
void set_reset(uint8_t val);
void resetAll();
void subReset0();
void subStep0();
void step();

#endif
