#ifndef __mu_malloc_h__
#define __mu_malloc_h__

#include <stddef.h>
#include <stdint.h>

void  *my_malloc    (size_t size);
void  *my_calloc    (size_t number, size_t size);
void  *my_realloc   (void *p, size_t size);
void   my_free      (void *ptr);
void   my_all_free  (void);

#endif

