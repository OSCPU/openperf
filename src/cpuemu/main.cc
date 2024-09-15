#include <etl/profiles/cpp17_no_stl.h>
#include <cpuemu.h>
#include <am.h>
#include <klib.h>
#include <klib-macros.h>

uint64_t rng64() {
  return 0;
}

static uint64_t uptime() { return io_read(AM_TIMER_UPTIME).us; }

static char *format_time(uint64_t us) {
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

int main(const char *args) {
  const char *setting_name = args;
  if (args == NULL || strcmp(args, "") == 0) {
    printf("Empty mainargs. Use \"ref\" by default\n");
    setting_name = "ref";
  }
  int setting_id = -1;

  if      (strcmp(setting_name, "test" ) == 0) setting_id = 0;
  else if (strcmp(setting_name, "train") == 0) setting_id = 1;
  else if (strcmp(setting_name, "ref"  ) == 0) setting_id = 2;
  else if (strcmp(setting_name, "huge" ) == 0) setting_id = 3;
  else {
    printf("Invalid mainargs: \"%s\"; "
           "must be in {test, train, ref, huge}\n", setting_name);
    halt(1);
  }

  ioe_init();

  int pass = 1;
  uint64_t t0 = uptime();
  uint64_t score_time = 0;

  uint64_t total_time = uptime() - t0;

  switch (setting_id) {
    case 0: rvmini(); break;
    case 1: nutshell(); break;
    default: nutshell(); break;
  }

  printf("Scored time: %s ms\n", format_time(score_time));
  printf("Total  time: %s ms\n", format_time(total_time));
  return (pass ? 0 : 1);
}

