#include <bench.h>

static const struct {
  int size;
  uint32_t ans;
  uint64_t ref_time;
} *ps, settings[BENCH_NR_SETTING] = {
         {8, 92, 0},
         {11, 2680, 551},
         {15, 2279184, 591703},
         {17, 95815104, 28147419},
};

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
  ps = &settings[setting];
  ans = 0;
  FULL = (1 << ps->size) - 1;
}

uint64_t bench_run() {
  ans = dfs(0, 0, 0);
  return ps->ref_time;
}

int bench_validate() {
  printf("There are %d solutions for %d queen problem\n", ans, ps->size);
  return ans == ps->ans ? 0 : 1;
}
