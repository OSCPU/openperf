#include "Top.h"
#include "utils.h"
#include <bench.h>

#define MAX_IDLE_CYCLE 100
#define PMEM_BASE      0x80000000
#define PMEM_SIZE      (128 * 1024)

typedef uint32_t word_t;
typedef int32_t sword_t;

static uint8_t *pmem = NULL;
static uint64_t cycles = 0, insts = 0;

static void reset(int n) {
  set_reset(1);
  while (n--) {
    step();
  }
  set_reset(0);
}

static size_t load_prog(char *bin) {
  bin = "input/microbench-riscv32e-npc.bin";
  FILE *fp = fopen(bin, "r");
  assert(fp);
  size_t s = fread(pmem, 1, PMEM_SIZE, fp);
  fclose(fp);
  printf("image size = %d\n", s);
  return s;
}

static uint32_t addr2idx(uint32_t addr, uint32_t base) {
  return (addr - base) & ~0x3ul;
}

sword_t pmem_read(int32_t raddr) {
  uint32_t idx = addr2idx(raddr, PMEM_BASE);
  return (idx < PMEM_SIZE ? *(sword_t *)(pmem + idx) : 0);
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

int main(int argc, char *argv[]) {
  pmem = (uint8_t *)malloc(PMEM_SIZE);
  assert(pmem != NULL);
  size_t img_size = load_prog(argv[1]);
  uint64_t last_commit_cycle = 0;
  int exit_code = 0;

  STop_init();

  uint64_t t0 = bench_uptime();

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

  uint64_t us = bench_uptime() - t0;
  printf("finish after %ld cycles, %lld us, simulation freq = %lld Hz\n", cycles, us, cycles * 1000000 / us);
  printf("#inst = %ld, IPC = %lld * 10^{-3}\n", insts, insts * 1000 / cycles);

  return exit_code;
}
