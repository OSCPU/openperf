#include <am.h>
#include <bench_debug.h>
#include <klib-macros.h>
#include <klib.h>

uint64_t uptime() { return (io_read(AM_TIMER_UPTIME).us); }

char *format_time(uint64_t us) {

  static char buf[128];
  uint64_t ms = us / 1000;
  uint64_t s = ms / 1000;
  uint64_t min = s / 60;
  uint64_t h = min / 60;

  us %= 1000;
  ms %= 1000;
  s %= 60;
  min %= 60;

  int len = 0;
  if (h > 0) {
    len = bench_sprintf(buf, "%lld h %lld min %lld s %lld.000 ms", h, min, s, ms);
  } else if (min > 0) {
    len = bench_sprintf(buf, "%lld min %lld s, %lld.000 ms", min, s, ms);
  } else if (s > 0) {
    len = bench_sprintf(buf, "%lld s, %lld.000 ms", s, ms);
  } else {
    len = bench_sprintf(buf, "%lld.000 ms", ms);
  }
  char *p = &buf[len - 4];
  while (us > 0) {
    *(p--) = '0' + us % 10;
    us /= 10;
  }

  return buf;
}
/* char *format_time(uint64_t us) {
  static char buf[32];
  uint64_t ms = us / 1000;
  us -= ms * 1000;
  assert(us < 1000);
  int len = sprintf(buf, "%d.000", ms);
  char *p = &buf[len - 1];
  while (us > 0) {
    *(p --) = '0' + us % 10;
    us /= 10;
  }
  return buf;
} */

// FNV hash
uint32_t checksum(void *start, void *end) {
  const uint32_t x = 16777619;
  uint32_t h1 = 2166136261u;
  for (uint8_t *p = (uint8_t *)start; p + 4 < (uint8_t *)end; p += 4) {
    for (int i = 0; i < 4; i++) {
      h1 = (h1 ^ p[i]) * x;
    }
  }
  int32_t hash = (uint32_t)h1;
  hash += hash << 13;
  hash ^= hash >> 7;
  hash += hash << 3;
  hash ^= hash >> 17;
  hash += hash << 5;
  return hash;
}
