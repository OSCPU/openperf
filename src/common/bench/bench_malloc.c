#include <bench_malloc.h>
#include <klib.h>

#if !defined (__ISA_NATIVE__)
extern char _end;
static intptr_t program_break = (intptr_t)&_end;  // program break一开始的位置位于_end

static void *sbrk(intptr_t increment) {
  intptr_t ret_addr = -1;
  intptr_t new_program_break = program_break + increment; // 被调用时, 根据记录的program break位置和参数increment, 计算出新program break
  ret_addr = program_break;
  program_break = new_program_break;
  return (void *)ret_addr;
}

// static int brk(void *addr)
// {
//   program_break = (intptr_t)addr;
//   return 1;
// }

static inline size_t word_align(size_t size) {
    return ( size + (sizeof(size_t) - 1)) & ~(sizeof(size_t) - 1);
}

struct chunk {
    struct chunk *next, *prev;
    size_t        size;
    size_t        free;
    void         *data;
};

typedef struct chunk *Chunk;

static void *malloc_base() {
    static Chunk b = NULL;
    if (!b) {
        b = sbrk(word_align(sizeof(struct chunk)));
        if (b == (void*) -1) {
            // _exit(127);
            assert(0);
        }
        b->next = NULL;
        b->prev = NULL;
        b->size = 0;
        b->free = 0;
        b->data = NULL;
    }
    return b;
}

Chunk malloc_chunk_find(size_t s, Chunk *heap) {
    Chunk c = malloc_base();
    for (; c && (!c->free || c->size < s); *heap = c, c = c->next);
    return c;
}

void malloc_merge_next(Chunk c) {
    c->size = c->size + c->next->size + sizeof(struct chunk);
    c->next = c->next->next;
    if (c->next) {
        c->next->prev = c;
    }
}

void malloc_split_next(Chunk c, size_t size) {
    Chunk newc = (Chunk)((char*) c + size);
    newc->prev = c;
    newc->next = c->next;
    newc->size = c->size - size;
    newc->free = 1;
    newc->data = newc + 1;
    if (c->next) {
        c->next->prev = newc;
    }
    c->next = newc;
    c->size = size - sizeof(struct chunk);
}

void *bench_malloc(size_t size) {
    if (!size) return NULL;
    size_t length = word_align(size + sizeof(struct chunk));
    Chunk prev = NULL;
    Chunk c = malloc_chunk_find(size, &prev);
    if (!c) {
        Chunk newc = sbrk(length);
        if (newc == (void*) -1) {
            return NULL;
        }
        newc->next = NULL;
        newc->prev = prev;
        newc->size = length - sizeof(struct chunk);
        newc->data = newc + 1;
        prev->next = newc;
        c = newc;
    } else if (length + sizeof(size_t) < c->size) {
        malloc_split_next(c, length);
    }
    c->free = 0;
    return c->data;
}

void bench_free(void *ptr) {
    if (!ptr || ptr < malloc_base() || ptr > sbrk(0)) return;
    Chunk c = (Chunk) ptr - 1;
    if (c->data != ptr) return;
    c->free = 1;

    if (c->next && c->next->free) {
        malloc_merge_next(c);
    }
    if (c->prev->free) {
        malloc_merge_next(c = c->prev);
    }
    if (!c->next) {
        c->prev->next = NULL;
        sbrk(- c->size - sizeof(struct chunk));
    }
}

void *bench_calloc(size_t nmemb, size_t size) {
    size_t length = nmemb * size;
    void *ptr = bench_malloc(length);
    if (ptr) {
        char *dst = ptr;
        for (size_t i = 0; i < length; *dst = 0, ++dst, ++i);
    }
    return ptr;
}

void *bench_realloc(void *ptr, size_t size) {
    void *newptr = bench_malloc(size);
    if (newptr && ptr && ptr >= malloc_base() && ptr <= sbrk(0)) {
        Chunk c = (Chunk) ptr - 1;
        if (c->data == ptr) {
            size_t length = c->size > size ? size : c->size;
            char *dst = newptr, *src = ptr;
            for (size_t i = 0; i < length; *dst = *src, ++src, ++dst, ++i);
            bench_free(ptr);
        }
    }
    return newptr;
}

// 在理应释放全部堆区的时候直接将堆指针归零，简单粗暴
void bench_all_free() {
  program_break = (intptr_t)&_end;
}
#else
#include <stdlib.h>
void *bench_malloc(size_t size) {
  return malloc(size);
}

void *bench_calloc(size_t number, size_t size) {
  return calloc(number, size);
}

void *bench_realloc(void *p, size_t size) {
  return realloc(p, size);
}

void bench_free(void *ptr) {
  free(ptr);
}

void bench_all_free() {

}



#endif //__ARCH_NATIVE__


