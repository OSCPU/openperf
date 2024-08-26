#include <am.h>
#include <klib.h>
#include <klib-macros.h>

uint64_t uptime()
{
	return (io_read(AM_TIMER_UPTIME).us);
}

char *format_time(uint64_t us) {
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
}

// FNV hash
uint32_t checksum(void *start, void *end) {
  const uint32_t x = 16777619;
  uint32_t h1 = 2166136261u;
  for (uint8_t *p = (uint8_t*)start; p + 4 < (uint8_t*)end; p += 4) {
    for (int i = 0; i < 4; i ++) {
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
