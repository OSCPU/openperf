#include "my_malloc.h"

#define BLOCK_SIZE 24       /* 由于存在虚拟的data字段，sizeof不能正确计算meta长度，这里手工设置 */
static void *first_block = NULL;
extern char _end;

static intptr_t program_break = (intptr_t)&_end;  // program break一开始的位置位于_end

typedef struct s_block * t_block ;
struct s_block {
  size_t  size;       /* 数据区大小 */
  t_block prev;       /* 指向上个块的指针 */
  t_block next;       /* 指向下个块的指针 */
  int     free;       /* 是否是空闲块 */
  int     padding;    /* 填充4字节，保证meta块长度为8的倍数 */
  void*   ptr;        /* Magic pointer，指向data */
  char    data[1];    /* 这是一个虚拟字段，表示数据块的第一个字节，长度不应计入meta */
};


static void *sbrk(intptr_t increment) {
  intptr_t ret_addr = -1;
  intptr_t new_program_break = program_break + increment; // 被调用时, 根据记录的program break位置和参数increment, 计算出新program break
  ret_addr = program_break;
  program_break = new_program_break;
  return (void *)ret_addr;
}

static int brk(void *addr)
{
  program_break = (intptr_t)addr;
  return 1;
}

/* First fit */
static t_block find_block (t_block *last, size_t size) {
  t_block b = first_block;
  while ( b && !(b->free && b->size >= size)) {
    *last = b;
    b = b->next;
  }
  return b ;
}

static t_block extend_heap ( t_block last, size_t s ) {
  t_block b;
  b = sbrk(0);
  if (sbrk(BLOCK_SIZE + s) == (void *)(-1) )
      return NULL;
  b->size = s ;
  b->next = NULL;
  if(last)
    last->next = b;
  b->free = 0;
  return b;
}

static void split_block(t_block b, size_t s) {
  t_block new;
  new = (t_block)(b->data + s);
  new->size = b->size - s - BLOCK_SIZE ;
  new->next = b->next ;
  new->free = 1 ;
  b->size = s ;
  b->next = new ;
}

static size_t align8 (size_t s) {
  if ((s & 0x7) == 0)
    return s ;
  return ( ( s >> 3 ) + 1 ) << 3 ;
}

void *my_malloc(size_t size) {
  // On native, malloc() will be called during initializaion of C runtime.
  // Therefore do not call panic() here, else it will yield a dead recursion:
  //   panic() -> putchar() -> (glibc) -> malloc() -> panic()
#if !(defined(__ISA_NATIVE__) && defined(__NATIVE_USE_KLIB__))
  t_block b, last;
  size_t s;
  /* 对齐地址 */
  s = align8(size);
  if (first_block) {
    /* 查找合适的block */
    last = first_block ;
    b = find_block (&last, s) ;
    if (b) {
      /* 如果可以，则分裂 */
      if ((b->size - s) >= (BLOCK_SIZE + 8))
        split_block (b, s) ;
      b->free = 0 ;
    } else {
      /* 没有合适的block，开辟一个新的 */
      b = extend_heap( last, s) ;
      if (!b)
        return NULL ;
    }
  } else {
    b = extend_heap(NULL, s) ;
    if (!b)
      return NULL ;
    first_block = b ;
  }
  return b->data ;
#endif
  return NULL;
}


void *my_calloc(size_t number, size_t size) {
  size_t *new;
  size_t s8, i;
  new = my_malloc(number * size);
  if (new) {
    s8 = (align8(number * size) >> 2);
    for (i = 0; i < s8; i ++)
      new[i] = 0;
  }
  return new;
}

static t_block get_block (void* p) {
  char* tmp;
  tmp = p;
  // return (p = tmp -= BLOCK_SIZE) ;
  tmp -= BLOCK_SIZE;
  p = tmp;
  return p;
}

//为了实现realloc，我们首先要实现一个内存复制方法。
//如同calloc一样，为了效率，我们以4字节为单位进行复制
static void copy_block(t_block src, t_block dst) {
    size_t *sdata, *ddata;
    size_t i;
    sdata = src->ptr;
    ddata = dst->ptr;
    for(i = 0; (i * 4) < src->size && (i * 4) < dst->size; i++)
      ddata[i] = sdata[i];
}

static int valid_addr ( void * p ) {
  if(first_block) {
    if( p > first_block && p < sbrk(0) ) {
      return (p == (get_block(p))->ptr);
    }
  }
  return 0;
}

static t_block fusion ( t_block b ) {
  if (b->next && b->next->free ) {
    b->size += BLOCK_SIZE + b->next->size;
    b->next = b->next->next;
    if (b->next)
      b->next->prev=b;
  }
  return b ;
}

void *my_realloc(void *p, size_t size)
{
  size_t s;
  t_block b, newb;
  void *newp;
  if (!p)/* 根据标准库文档，当p传入NULL时，相当于调用malloc */
    return my_malloc(size);
  if(valid_addr(p))
  {
    s = align8(size);
    b = get_block(p);
    if(b->size >= s)
    {
      if(b->size - s >= (BLOCK_SIZE + 8))
        split_block(b,s);
    }
    else
    {
      /* 看是否可进行合并 */
      if(b->next && b->next->free && (b->size + BLOCK_SIZE + b->next->size) >= s)
      {
        fusion(b);
        if(b->size - s >= (BLOCK_SIZE + 8))
        split_block(b, s);
      }
      else
      {
      /* 新malloc */
        newp = my_malloc (s);
        if (!newp)
            return NULL;
        newb = get_block(newp);
        copy_block(b, newb);
        my_free(p);
        return(newp);
      }
    }
    return (p);
  }
  return NULL;
}


void my_free(void *ptr) {
  t_block b;
  if ( valid_addr ( ptr ) ) {
    b = get_block(ptr);
    b->free = 1;
    if (b->prev && b->prev->free )
        b = fusion(b->prev);
    if (b->next)
        fusion (b);
    else {
      if(b->prev)
        b->prev->prev = NULL;
      else
        first_block = NULL;
      brk(b) ;
    }
  }
}

// 这个堆管理写的应该是有问题，所以最好是在理应释放全部堆区的时候，直接将堆指针归零，简单粗暴
void my_all_free() {
  program_break = (intptr_t)&_end;
}


