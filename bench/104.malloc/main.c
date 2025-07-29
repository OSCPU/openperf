#include <bench.h>
#include <stdio.h>
#include <stdlib.h>

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

static int nr_op;
static char **addr;
static OP *ops;

void bench_init(int setting) {
  FILE *fp = fopen("input/test.trace", "rb");
  assert(fp != NULL);

  int nr_addr = 0;
  fread(&nr_addr, 4, 1, fp);
  fread(&nr_op, 4, 1, fp);

  addr = malloc(sizeof(uintptr_t) * nr_addr);
  printf("allocated %d addresses\n", nr_addr);

  size_t ops_size = sizeof(OP) * nr_op;
  ops = malloc(ops_size);
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
        addr[op->idx] = malloc(op->size);
        *addr[op->idx] = 1;
        break;
      case FUNC_calloc:
        addr[op->idx] = calloc(op->arg3, op->size);
        *addr[op->idx] = 1;
        break;
      case FUNC_realloc:
        if (op->idx == -1)
          free(addr[op->arg3]);
        else {
          void *ptr = op->arg3 == -1 ? NULL : addr[op->arg3];
          addr[op->idx] = realloc(ptr, op->size);
          *addr[op->idx] = 1;
        }
        break;
      case FUNC_free: free(op->idx == -1 ? NULL : addr[op->idx]); break;
      default: assert(0);
    }

    i++;
    if ((i & 0xffff) == 0) {
      printf("already handle %d/%d operations\n", i, nr_op);
    }
  }

  return 0;
}

int bench_validate() {
  free(addr);
  free(ops);
  printf("Test end\n");
  return 0;
}
