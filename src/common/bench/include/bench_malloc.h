#ifndef __mu_malloc_h__
#define __mu_malloc_h__

#include <stddef.h>
#include <stdint.h>

void  *bench_malloc    (size_t size);
void  *bench_calloc    (size_t number, size_t size);
void  *bench_realloc   (void *p, size_t size);
void   bench_free      (void *ptr);
void   bench_all_free  (void);

#endif

