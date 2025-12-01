#include <bench.h>

static const struct {
  int size;
  uint32_t checksum;
  uint64_t ref_time;
} *ps, settings[BENCH_NR_SETTING] = {
         {100, 0x6a368bc9, 0},
         {10000, 0x1f4fe60a, 242},
         {30000000, 0xce979d2d, 1516034},
         {500000000, 0x2e887502, 29476677},
};

static int N, *data;

static void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

static void myqsort(int *a, int l, int r) {
  if (l < r) {
    int p = a[l], pivot = l, j;
    for (j = l + 1; j < r; j++) {
      if (a[j] < p) {
        swap(&a[++pivot], &a[j]);
      }
    }
    swap(&a[pivot], &a[l]);
    myqsort(a, l, pivot);
    myqsort(a, pivot + 1, r);
  }
}

void bench_init(int setting) {
  ps = &settings[setting];
  N = ps->size;
  bench_srand(1);
  data = malloc(N * sizeof(int));
  for (int i = 0; i < N; i++) {
    data[i] = bench_rand();
  }
}

uint64_t bench_run() {
  myqsort(data, 0, N);
  return ps->ref_time;
}

int bench_validate() {
  uint32_t cs = bench_checksum(data, data + N);
  printf("cs = 0x%08x\n", cs);
  free(data);
  return cs == ps->checksum ? 0 : 1;
}
