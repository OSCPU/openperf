#include <bench.h>

// Memory allocator by Kernighan and Ritchie,
// The C programming Language, 2nd ed.  Section 8.7.

typedef long Align;

union header {
  struct {
    union header *ptr;
    size_t size;
  } s;
  Align x;
};

typedef union header Header;

static Header base;
static Header *freep;

void my_free(void *ap) {
  Header *bp, *p;

  if (ap == NULL)
    return;

  bp = (Header *)ap - 1;
  for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
    if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
      break;
  if (bp + bp->s.size == p->s.ptr) {
    bp->s.size += p->s.ptr->s.size;
    bp->s.ptr = p->s.ptr->s.ptr;
  } else
    bp->s.ptr = p->s.ptr;
  if (p + p->s.size == bp) {
    p->s.size += bp->s.size;
    p->s.ptr = bp->s.ptr;
  } else
    p->s.ptr = bp;
  freep = p;
}

static Header *morecore(size_t nu) {
  char *p;
  Header *hp;

  if (nu < 4096)
    nu = 4096;
  size_t inc = nu * sizeof(Header);
#ifdef __ARCH__
  static void *brk = 0;
  if (brk == 0) {
    brk = heap.start;
  }
  void *new_brk = brk + inc;
  if (new_brk < heap.end) {
    p = brk;
    brk = new_brk;
  } else {
    p = (char *)-1;
  }
#else
  void *sbrk(intptr_t increment);
  p = sbrk(inc);
#endif
  if (p == (char *)-1)
    return 0;
  memset(p, 0xcc, inc);
  hp = (Header *)p;
  hp->s.size = nu;
  my_free((void *)(hp + 1));
  return freep;
}

void *my_malloc(uint32_t nbytes) {
  Header *p, *prevp;
  size_t nunits;

  nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
  if ((prevp = freep) == 0) {
    base.s.ptr = freep = prevp = &base;
    base.s.size = 0;
  }
  for (p = prevp->s.ptr;; prevp = p, p = p->s.ptr) {
    if (p->s.size >= nunits) {
      if (p->s.size == nunits)
        prevp->s.ptr = p->s.ptr;
      else {
        p->s.size -= nunits;
        p += p->s.size;
        p->s.size = nunits;
      }
      freep = prevp;
      return (void *)(p + 1);
    }
    if (p == freep)
      if ((p = morecore(nunits)) == 0)
        return 0;
  }
}

void *my_calloc(size_t nmemb, size_t size) {
  size *= nmemb;
  void *ret = my_malloc(size);
  memset(ret, 0, size);
  return ret;
}

void *my_realloc(void *ptr, size_t size) {
  if (ptr == NULL)
    return my_malloc(size);
  if (size == 0) {
    my_free(ptr);
    return NULL;
  }
  void *ret = my_malloc(size);
  if (ret) {
    Header *hp = (Header *)ptr - 1;
    size_t old_size = (hp->s.size - 1) * sizeof(Header);
    size_t copy_size = size < old_size ? size : old_size;
    memcpy(ret, ptr, copy_size);
    my_free(ptr);
  }
  return ret;
}
