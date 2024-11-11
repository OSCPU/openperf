#ifndef __BENCH_MALLOC
#define __BENCH_MALLOC

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

void bench_malloc_init();
void *bench_malloc(size_t size);
void *bench_calloc(size_t number, size_t size);
void *bench_realloc(void *p, size_t size);
void bench_free(void *ptr);
void bench_all_free(void);

#ifdef  __cplusplus
}
#endif

#endif
