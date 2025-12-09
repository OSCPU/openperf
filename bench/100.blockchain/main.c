#include "Blockchain.h"
#include <bench.h>

static const struct {
  int nDifficulty;
  uint32_t cs[3];
  uint64_t ref_time;
} *ps, settings[BENCH_NR_SETTING] = {
         {0, {0x3baf5009, 0xadf4479e, 0x3250357b}, 0},
         {1, {0xc45b555f, 0x4216efa2, 0xe93969da}, 43},
         {5, {0x32797865, 0xca23f2b5, 0x2f57cb76}, 1621671},
         {6, {0x62d1f745, 0x590e5ba7, 0x462f7ef6}, 14987945},
};

static Blockchain bChain;
static const char *hash[3];

void bench_init(int setting) {
  bench_srand(0);
  ps = &settings[setting];
  initBlockchain(&bChain, ps->nDifficulty);
}

uint64_t bench_run() {
  printf("Mining block 1...\n");
  hash[0] = AddBlock(&bChain, 1, "Block 1 Data");
  printf("Mining block 2...\n");
  hash[1] = AddBlock(&bChain, 2, "Block 2 Data");
  printf("Mining block 3...\n");
  hash[2] = AddBlock(&bChain, 3, "Block 3 Data");
  return ps->ref_time;
}

int bench_validate() {
  for (int i = 0; i < 3; i++) {
    uint32_t cs = bench_checksum(hash[i], hash[i] + strlen(hash[i]));
    if (cs != ps->cs[i]) {
      return 1;
    }
  }
  return 0;
}
