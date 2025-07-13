#include "Top.h"
#include "utils.h"
#include <bench.h>

#define MAX_IDLE_CYCLE 100
#define PMEM_BASE      0x80000000

typedef uint32_t word_t;
typedef int32_t sword_t;

static const struct {
  const char *bin;
  uint32_t pmem_size;
  uint64_t cycles;
  uint32_t cs;
  uint64_t ref_time;
} *ps, settings[BENCH_NR_SETTING] = {
         {"input/test-putch-asm.bin", 64, 23, 0x917fb81e, 0},
         {"input/train-hello-riscv32e-npc.bin", 36 * 1024, 702, 0x3baab934, 96},
         {"input/ref-microbench-test-riscv32e-npc.bin", 100 * 1024, 1526121, 0x17a76ab4, 194814},
         {"input/huge-microbench-train-riscv32e-npc.bin", 370 * 1024, 504772696, 0x1d858e6e, 68625476},
};

static uint8_t *pmem = NULL;
static uint32_t pmem_size = 0;

static void reset(int n) {
  set_reset(1);
  while (n--) {
    step();
  }
  set_reset(0);
}

static size_t load_prog(const char *bin) {
  FILE *fp = fopen(bin, "r");
  assert(fp);
  int s = fread(pmem, 1, pmem_size, fp);
  fclose(fp);
  printf("image size = %d\n", s);
  return s;
}

static uint32_t addr2idx(uint32_t addr, uint32_t base) {
  uint32_t idx = (addr - base) & ~0x3ul;
  if (idx >= pmem_size) {
    printf("Error: memory access out of bound!\n");
    bench_exit(1);
  }
  return idx;
}

sword_t pmem_read(int32_t raddr) {
  uint32_t idx = addr2idx(raddr, PMEM_BASE);
  return *(sword_t *)(pmem + idx);
}

void pmem_write(int32_t waddr, sword_t wdata, uint8_t wmask) {
  if (waddr == 0x10000000) {
    printf("%c", wdata);
  } else {
    uint32_t idx = addr2idx(waddr, PMEM_BASE);
    for (int i = 0; i < sizeof(word_t); i++) {
      if (wmask & 0x1) {
        pmem[idx + i] = wdata & 0xff;
      }
      wmask >>= 1;
      wdata >>= 8;
    }
  }
}

static struct {
  bool valid, isEbreak, isMMIO, skip;
  word_t code;
  uint32_t memAddr, pc, dnpc;
} commit;

void set_commit(uint8_t valid, int32_t pc, int32_t dnpc, uint8_t isEbreak, word_t code, uint8_t isMMIO, int32_t memAddr,
                uint8_t skip) {
  commit.valid = valid;
  if (valid) {
    commit.pc = pc;
    commit.dnpc = dnpc;
    commit.isEbreak = isEbreak;
    commit.code = code;
    commit.isMMIO = isMMIO;
    commit.memAddr = memAddr;
    commit.skip = skip;
  }
}

void NPCTrap(uint8_t valid, uint32_t pc, uint32_t dnpc, uint8_t isEbreak, word_t code, uint8_t isMMIO, uint32_t memAddr,
             uint8_t skip) {
  set_commit(valid, pc, dnpc, isEbreak, code, isMMIO, memAddr, skip);
}

void SimDMEM(uint8_t ren, uint32_t raddr, uint32_t *rdata, uint8_t wen, uint32_t waddr, uint32_t wdata, uint8_t wmask) {
  *rdata = ren ? pmem_read(raddr) : 0;
  if (wen)
    pmem_write(waddr, wdata, wmask);
}

static unsigned long long t;
static unsigned long long cycles, insts;
static int exit_code;

void bench_init(int setting) {
  ps = &settings[setting];
  pmem_size = ps->pmem_size;
  pmem = (uint8_t *)calloc(1, pmem_size);
  assert(pmem != NULL);
  load_prog(ps->bin);
  exit_code = 0;
  cycles = 0;
  insts = 0;
  STop_init();
}

uint64_t bench_run() {
  t = bench_uptime();
  uint64_t last_commit_cycle = 0;
  reset(10);
  while (true) {
    step();
    cycles++;
    if (cycles - last_commit_cycle > MAX_IDLE_CYCLE) {
      printf("No instructions commit in %d cycles, maybe get stuck!\n", MAX_IDLE_CYCLE);
      exit_code = 2;
      break;
    }
    if (commit.valid) {
      insts++;
      last_commit_cycle = cycles;
      if (commit.isEbreak) {
        exit_code = commit.code;
        printf("npc: %s\n",
               (exit_code == 0 ? ANSI_FMT("HIT GOOD TRAP", ANSI_FG_GREEN) : ANSI_FMT("HIT BAD TRAP", ANSI_FG_RED)));
        break;
      }
      if (commit.dnpc == 0) {
        printf("Jump to 0. Maybe there is an exception.\n");
        exit_code = 3;
        break;
      }
    }
  }
  t = bench_uptime() - t;
  return ps->ref_time;
}

int bench_validate() {
  printf("finish after %lld cycles, %lld us, simulation freq = %lld Hz\n", cycles, t, cycles * 1000000 / t);
  printf("#inst = %lld, IPC = %lld * 10^{-3}\n", insts, insts * 1000 / cycles);

  uint32_t cs = bench_checksum(pmem, pmem + pmem_size);
  free(pmem);

  int fail = (exit_code != 0) || (ps->cycles != cycles) || (ps->cs != cs);
  return fail;
}
