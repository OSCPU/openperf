#ifndef __BENCH_H__
#define __BENCH_H__

#include <stdint.h>
#ifdef __ARCH__ // defined in AM
#include <klib.h>
#else
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

enum {
  BENCH_SETTING_TEST,
  BENCH_SETTING_TRAIN,
  BENCH_SETTING_REF,
  BENCH_SETTING_HUGE,
  BENCH_NR_SETTING,
};

typedef struct {
  char *p;
  int len;
  int capicity;
} Obuf;

void bench_srand(uint32_t _seed);
uint32_t bench_rand();
uint64_t bench_uptime(); // unit: us
void bench_exit(int status);
uint32_t bench_checksum(const void *start, const void *end);
void bench_obuf_init(Obuf *o, int len);
void bench_obuf_append(Obuf *o, const void *p, int len);

#endif
