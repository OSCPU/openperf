#include <bench.h>
#include <stdio.h>

static const struct {
  int size;
  uint32_t ans;
} settings[BENCH_NR_SETTING] = {
  {8, 92},
  {11, 2680},
  {15, 2279184},
  {17, 95815104},
};

static unsigned int FULL;

static unsigned int dfs(unsigned int row, unsigned int ld, unsigned int rd) {
  if (row == FULL) {
    return 1;
  } else {
    unsigned int pos = FULL & (~(row | ld | rd)), ans = 0;
    while (pos) {
      unsigned int p = (pos & (~pos + 1));
      pos -= p;
      ans += dfs(row | p, (ld | p) << 1, (rd | p) >> 1);
    }
    return ans;
  }
}

static unsigned int ans;

static void bench_queen_prepare(int size) {
  ans = 0;
  FULL = (1 << size) - 1;
}

static void bench_queen_run() {
  ans = dfs(0, 0, 0);
}

static int bench_queen_validate(uint32_t ref) {
  return (ans == ref);
}

int bench_main(int setting) {
  bench_queen_prepare(settings[setting].size);
  bench_queen_run();
  printf("There are %d solutions for %d queen problem\n", ans, settings[setting].size);
  int ret = bench_queen_validate(settings[setting].ans);
  return !ret;
}
