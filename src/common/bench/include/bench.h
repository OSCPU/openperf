#ifndef __BENCH_COMMON
#define __BENCH_COMMON

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

uint64_t uptime();
char *format_time(uint64_t us);
uint32_t checksum(void *start, void *end);
void bench_srand(uint32_t _seed);
uint32_t bench_rand();

typedef struct {
  void *sub_config;
  size_t mlim;
  uint64_t ref_time;
  uint32_t checksum;
  size_t repeat_time;
} Setting;

#ifdef  __cplusplus
}
#endif

#endif
