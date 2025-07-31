#include <bench.h>
#include <stdio.h>
#include <stdlib.h>

static const struct {
  char *data;
  uint32_t cs;
  uint64_t ref_time;
} *ps, settings[BENCH_NR_SETTING] = {
         {"input/test.trace", 0x35000200, 0},
         {"input/train.trace", 0x1f07f9f2, 647},
         {"input/ref.trace", 0x0f80dc53, 311050},
         {"input/huge.trace", 0x8df3116f, 45297530},
};

enum {
  FUNC_malloc,
  FUNC_calloc,
  FUNC_realloc,
  FUNC_free
};

typedef struct __attribute__((packed)) {
  uint32_t func : 2;
  int idx : 30;
  uint32_t size;
  int arg3;
} OP;

void my_free(void *addr);
void *my_malloc(size_t nbytes);
void *my_calloc(size_t nmemb, size_t size);
void *my_realloc(void *ptr, size_t size);

static int nr_op;
static uint8_t **addr;
static OP *ops;
static uint32_t cs;

void bench_init(int setting) {
  ps = &settings[setting];
  cs = 0;
  FILE *fp = fopen(ps->data, "rb");
  assert(fp != NULL);

  int nr_addr = 0;
  fread(&nr_addr, 4, 1, fp);
  fread(&nr_op, 4, 1, fp);

  addr = my_malloc(sizeof(uintptr_t) * nr_addr);
  printf("allocated %d addresses\n", nr_addr);

  size_t ops_size = sizeof(OP) * nr_op;
  ops = my_malloc(ops_size);
  printf("%d operations in total\n", nr_op);
  int ret = fread(ops, ops_size, 1, fp);
  assert(ret == 1);
  fclose(fp);
}

uint64_t bench_run() {
  int i = 0;
  while (i < nr_op) {
    OP *op = &ops[i];
    switch (op->func) {
      case FUNC_malloc:
        addr[op->idx] = my_malloc(op->size);
        *addr[op->idx] = 1;
        cs ^= (i & 0xff) << 0;
        break;
      case FUNC_calloc:
        addr[op->idx] = my_calloc(op->arg3, op->size);
        *addr[op->idx] = 1;
        cs ^= (i & 0xff) << 8;
        break;
      case FUNC_realloc:
        if (op->idx == -1)
          my_free(addr[op->arg3]);
        else {
          void *ptr = op->arg3 == -1 ? NULL : addr[op->arg3];
          addr[op->idx] = my_realloc(ptr, op->size);
          *addr[op->idx] = 1;
        }
        cs ^= (i & 0xff) << 16;
        break;
      case FUNC_free:
        my_free(op->idx == -1 ? NULL : addr[op->idx]);
        cs ^= (i & 0xff) << 24;
        break;
      default: assert(0);
    }

    i++;
    if ((i & 0xffff) == 0) {
      printf("already handle %d/%d operations\n", i, nr_op);
    }
  }
  return ps->ref_time;
}

int bench_validate() {
  my_free(addr);
  my_free(ops);
  printf("Test end\n");
  int fail = (cs != ps->cs);
  return fail;
}
