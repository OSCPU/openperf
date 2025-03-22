#include <bench.h>
#include <sys/time.h>

#define NR_REPEAT 1
#define REF_SCORE 1000000
#define REF_CPU   "AMD Ryzen(TM) 9 7950X3D"

uint64_t bench_uptime() { // unit: us
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec * 1000000ull + tv.tv_usec;
}

static int str2setting(const char *args) {
  if (args == NULL || strcmp(args, "") == 0) {
    printf("Empty mainargs. Use \"test\" by default\n");
    args = "test";
  }
  int setting_id = -1;

  if (strcmp(args, "test") == 0)
    setting_id = BENCH_SETTING_TEST;
  else if (strcmp(args, "train") == 0)
    setting_id = BENCH_SETTING_TRAIN;
  else if (strcmp(args, "ref") == 0)
    setting_id = BENCH_SETTING_REF;
  else if (strcmp(args, "huge") == 0)
    setting_id = BENCH_SETTING_HUGE;
  else {
    printf("Invalid setting: \"%s\"; must be in {test, train, ref, huge}\n", args);
    bench_exit(1);
  }
  return setting_id;
}

static void print_reverse(char *p, uint32_t n) {
  while (n > 0) {
    *(p--) = '0' + n % 10;
    n /= 10;
  }
}

static char *format_time(unsigned long long _us) {
  static char buf[128];
  uint32_t s = _us / 1000000;
  uint32_t m = s / 60;
  uint32_t h = m / 60;
  uint32_t us = _us % 1000000;
  m %= 60;
  s %= 60;
  //            0123456789012345
  sprintf(buf, "  0:00:00.000000 (%llu us)", _us);
  print_reverse(buf + 2, h);
  print_reverse(buf + 5, m);
  print_reverse(buf + 8, s);
  print_reverse(buf + 15, us);
  return buf;
}

#define ANSI_FG_RED        "\33[1;31m"
#define ANSI_FG_GREEN      "\33[1;32m"
#define ANSI_NONE          "\33[0m"
#define ANSI_FMT(str, fmt) fmt str ANSI_NONE

int main(int argc, char *argv[]) {
  extern void bench_init(int setting);
  extern uint64_t bench_run();
  extern int bench_validate();

  uint64_t t0 = bench_uptime();
  int setting = str2setting(argv[1]);

  uint64_t ref_time = 0;
  uint64_t scored_time = 0;
  uint64_t dut_time = -1ull;
  int pass = 1;
  for (int i = 0; i < NR_REPEAT; i++) {
    bench_init(setting);
    uint64_t t1 = bench_uptime();
    ref_time = bench_run();
    uint64_t t2 = bench_uptime();

    int ret = bench_validate(); // 0 for OK
    if (ret != 0)
      pass = 0;

    uint64_t diff = t2 - t1;
    if (diff == 0)
      diff = 1;
    if (diff < dut_time)
      dut_time = diff;
    scored_time += diff;
  }

  uint64_t t3 = bench_uptime();
  uint64_t total_time = t3 - t0;

  const char *res = pass ? ANSI_FMT("PASS", ANSI_FG_GREEN) : ANSI_FMT("FAIL", ANSI_FG_RED);
  printf("==================================================\n");
  printf("[RESULT] %s with min time: %s\n", res, format_time(dut_time));

  if (setting != BENCH_SETTING_TEST) {
    uint32_t score = (uint64_t)(REF_SCORE)*ref_time / dut_time;
    if (score == 0)
      score = 1;
    printf("      %10u Marks\n", score);
    printf("  vs. %10u Marks @ %s\n", REF_SCORE, REF_CPU);
  } else {
    printf("\n");
  }
  printf("Scored time: %s\n", format_time(scored_time));
  printf("Total  time: %s\n", format_time(total_time));
  return (pass ? 0 : 1);
}

void bench_exit(int status) {
  exit(status);
}
