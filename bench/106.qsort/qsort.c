#include <bench.h>

static int N = 100, *data;

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
  bench_srand(1);
  data = malloc(N * sizeof(int));
  for (int i = 0; i < N; i++) {
    data[i] = bench_rand();
  }
}

uint64_t bench_run() {
  myqsort(data, 0, N);
  return 0;
}

int bench_validate() {
  uint32_t cs = bench_checksum(data, data + N);
  printf("cs = 0x%08x\n", cs);
  free(data);
  return 0;
}
