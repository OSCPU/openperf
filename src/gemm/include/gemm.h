#include <am.h>
#include <bench.h>
#include <bench_malloc.h>
#include <klib-macros.h>
#include <klib.h>
#include <stdint.h>

#define TEST
typedef struct {
  uint32_t m;
  uint32_t n;
  uint32_t k;
  uint64_t checksum;
} bench_gemm_config;

void AddDot4x4(int, double *, int, double *, int, double *, int);
void PackMatrixA(int, double *, int, double *);
void PackMatrixB(int, double *, int, double *);
void InnerKernel(int, int, int, double *, int, double *, int, double *, int,
                 int);
void matmul(int m, int n, int k, double *a, int lda, double *b, int ldb,
            double *c, int ldc);
