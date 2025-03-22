#include <bench.h>

void bench_init(int setting) {}

uint64_t bench_run() {
  printf("Hello, World!\n");
  return 1;
}

int bench_validate() {
  return 0;
}
