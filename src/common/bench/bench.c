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
