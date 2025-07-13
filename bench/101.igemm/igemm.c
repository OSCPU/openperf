#include <bench.h>

static const struct {
  int size;
  uint32_t checksum;
  uint64_t ref_time;
} *ps, settings[BENCH_NR_SETTING] = {
         {2, 0xbc4f9265, 0},
         {40, 0x9321fb62, 22},
         {1000, 0xfcf9d4ab, 466056},
         {2500, 0x3e52d901, 7285748},
};

#define A_row(i, j) a[(i) * lda + (j)]
#define B_row(i, j) b[(i) * ldb + (j)]
#define C_row(i, j) c[(i) * ldc + (j)]

#define A_col(i, j) a[(j) * lda + (i)]
#define B_col(i, j) b[(j) * ldb + (i)]
#define C_col(i, j) c[(j) * ldc + (i)]

void random_init(int m, int n, unsigned *a, int lda, int type) {
  for (int j = 0; j < n; j++) {
    for (int i = 0; i < m; i++) {
      if (type == 0)
        A_row(i, j) = 2 * bench_rand() - 1;
      else
        A_col(i, j) = 2 * bench_rand() - 1;
    }
  }
}

void matmul_row(int m, int n, int k, unsigned *a, int lda, unsigned *b, int ldb, unsigned *c, int ldc) {
  /*
     Computes the matrix multiplication of A and B and stores in C.

     Arguments
     ---------
     m,n,k : Specifies matrix dimensions
     a : pointer to first matrix
     b : pointer to second matrix
     c : pointer to the resultant matrix
     lda : leading dimension of matrix a
     ldb : leading dimension of matrix b
     ldc : leading dimension of matrix c

     Return
     ------
     None

     Matrix Multiply Condition
     -------------------------
     Number of Columns in first matrix must be equal to the number of rows in the second matrix
  */

  if (a == NULL || b == NULL || c == NULL) {
    printf("Argument Error : One of the input arguments to matmul() was NULL\n");
    return;
  }

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      for (int p = 0; p < k; p++) {
        C_row(i, j) += A_row(i, p) * B_row(p, j);
      }
    }
  }
  return;
}

static unsigned *A, *B, *C;
static unsigned long long duration_row;
static int N = 1;

void bench_init(int setting) {
  ps = &settings[setting];
  N = ps->size;
  A = (unsigned *)malloc(N * N * sizeof(unsigned));
  B = (unsigned *)malloc(N * N * sizeof(unsigned));
  C = (unsigned *)calloc(1, N * N * sizeof(unsigned));

  if (A == NULL || B == NULL || C == NULL) {
    printf("Out of Memory!\n");
    bench_exit(1);
  }

  bench_srand(1);
  random_init(N, N, A, N, 0);
  random_init(N, N, B, N, 0);
}

uint64_t bench_run() {
  uint64_t t0 = bench_uptime();
  matmul_row(N, N, N, A, N, B, N, C, N);
  uint64_t t1 = bench_uptime();
  duration_row = (t1 - t0);
  if (duration_row == 0)
    duration_row = 1;
  return ps->ref_time;
}

int bench_validate() {
  uint64_t op = 2ull * N * N * N;
  printf("Dot product with row major order took %lld us, KOPS: %lld\n", duration_row, op * 1000 / duration_row);

  uint32_t cs = bench_checksum(C, C + N * N);

  free(A);
  free(B);
  free(C);

  int fail = (cs != ps->checksum);
  return fail;
}
