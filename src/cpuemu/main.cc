#include <am.h>
#include <cpuemu.h>
#include <bench.h>
#include <bench_debug.h>
#include <bench_malloc.h>
#include <etl/profiles/cpp17_no_stl.h>
#include <klib-macros.h>
#include <klib.h>

uint64_t rng64() { return 0; }

extern bench_cpuemu_config config;

int main(const char *args) {

  bench_malloc_init();
  ioe_init();

  int pass = 1;

  uint64_t start_time, end_time;
  start_time = uptime();
  switch (config.setting_id) {
  case 0:
    rvmini();
    break;
  case 1:
    nutshell();
    break;
  default:
    nutshell();
    break;
  }
  end_time = uptime();

  BENCH_LOG(INFO, "OpenPerf time: %s", format_time(end_time - start_time));
  return (pass ? 0 : 1);
}
