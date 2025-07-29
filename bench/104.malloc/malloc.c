#include <stddef.h>
#include <stdint.h>
#include <string.h>

void *_sbrk(intptr_t increment);

// Memory allocator by Kernighan and Ritchie,
// The C programming Language, 2nd ed.  Section 8.7.

typedef long Align;

union header {
  struct {
    union header *ptr;
    uint32_t size;
  } s;
  Align x;
};

typedef union header Header;

static Header base;
static Header *freep;

void free(void *ap) {
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

static Header *morecore(uint32_t nu) {
  char *p;
  Header *hp;

  if (nu < 4096)
    nu = 4096;
  p = _sbrk(nu * sizeof(Header));
  if (p == (char *)-1)
    return 0;
  hp = (Header *)p;
  hp->s.size = nu;
  free((void *)(hp + 1));
  return freep;
}

void *malloc(uint32_t nbytes) {
  Header *p, *prevp;
  uint32_t nunits;

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

void *calloc(size_t nmemb, size_t size) {
  size *= nmemb;
  void *ret = malloc(size);
  memset(ret, 0, size);
  return ret;
}

void *realloc(void *ptr, size_t size) {
  if (ptr == NULL)
    return malloc(size);
  if (size == 0) {
    free(ptr);
    return NULL;
  }
  void *ret = malloc(size);
  memcpy(ret, ptr, size);
  free(ptr);
  return ret;
}
