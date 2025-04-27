#ifndef __BENCH_H__
#define __BENCH_H__

#include <stdint.h>
#ifdef __ARCH__ // defined in AM
#include <klib.h>
#else
#include <assert.h>
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

uint64_t bench_uptime(); // unit: us
void bench_exit(int status);

#endif
