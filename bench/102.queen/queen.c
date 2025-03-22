#include <bench.h>

static uint32_t FULL;
static uint32_t ans;

static uint32_t dfs(uint32_t row, uint32_t ld, uint32_t rd) {
  if (row == FULL) {
    return 1;
  } else {
    uint32_t pos = FULL & (~(row | ld | rd)), ans = 0;
    while (pos) {
      uint32_t p = (pos & (~pos + 1));
      pos -= p;
      ans += dfs(row | p, (ld | p) << 1, (rd | p) >> 1);
    }
    return ans;
  }
}

void bench_init(int setting) {
  ans = 0;
  FULL = (1 << 8) - 1;
}

uint64_t bench_run() {
  ans = dfs(0, 0, 0);
  return 0;
}

int bench_validate() {
  printf("ans = %d\n", ans);
  return 0;
}
