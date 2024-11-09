#include <stddef.h>

typedef int cmp_t(const void *, const void *);

static char *med3(char *, char *, char *, cmp_t *);
static void swapfunc(char *, char *, int, int);

#define min(a, b) (a) < (b) ? a : b

/*
 * Qsort routine from Bentley & McIlroy's "Engineering a Sort Function".
 */
#define swapcode(TYPE, parmi, parmj, n)                                        \
  {                                                                            \
    long i = (n) / sizeof(TYPE);                                               \
    TYPE *pi = (TYPE *)(parmi);                                                \
    TYPE *pj = (TYPE *)(parmj);                                                \
    do {                                                                       \
      TYPE t = *pi;                                                            \
      *pi++ = *pj;                                                             \
      *pj++ = t;                                                               \
    } while (--i > 0);                                                         \
  }

#define SWAPINIT(a, es)                                                        \
  swaptype = ((char *)a - (char *)0) % sizeof(long) || es % sizeof(long) ? 2   \
             : es == sizeof(long)                                        ? 0   \
                                                                         : 1;

static void swapfunc(char *a, char *b, int n, int swaptype) {
  if (swaptype <= 1)
    swapcode(long, a, b, n) else swapcode(char, a, b, n)
}

#define swap(a, b)                                                             \
  if (swaptype == 0) {                                                         \
    long t = *(long *)(a);                                                     \
    *(long *)(a) = *(long *)(b);                                               \
    *(long *)(b) = t;                                                          \
  } else                                                                       \
    swapfunc(a, b, es, swaptype)

#define vecswap(a, b, n)                                                       \
  if ((n) > 0)                                                                 \
  swapfunc(a, b, n, swaptype)

static char *med3(char *a, char *b, char *c, cmp_t *cmp) {
  return cmp(a, b) < 0 ? (cmp(b, c) < 0 ? b : (cmp(a, c) < 0 ? c : a))
                       : (cmp(b, c) > 0 ? b : (cmp(a, c) < 0 ? a : c));
}

/*
 * Classical function call recursion wastes a lot of stack space. Each
 * recursion level requires a full stack frame comprising all local variables
 * and additional space as dictated by the processor calling convention.
 *
 * This implementation instead stores the variables that are unique for each
 * recursion level in a parameter stack array, and uses iteration to emulate
 * recursion. Function call recursion is not used until the array is full.
 *
 * To ensure the stack consumption isn't worsened by this design, the size of
 * the parameter stack array is chosen to be similar to the stack frame
 * excluding the array. Each function call recursion level can handle this
 * number of iterative recursion levels.
 */
#define PARAMETER_STACK_LEVELS 8u

void my_qsort(void *a, size_t n, size_t es, cmp_t *cmp) {
  char *pa, *pb, *pc, *pd, *pl, *pm, *pn;
  size_t d, r;
  int cmp_result;
  int swaptype, swap_cnt;
  size_t recursion_level = 0;
  struct {
    void *a;
    size_t n;
  } parameter_stack[PARAMETER_STACK_LEVELS];

  SWAPINIT(a, es);
loop:
  swap_cnt = 0;
  if (n < 7) {
    /* Short arrays are insertion sorted. */
    for (pm = (char *)a + es; pm < (char *)a + n * es; pm += es)
      for (pl = pm; pl > (char *)a && cmp(pl - es, pl) > 0; pl -= es)
        swap(pl, pl - es);
    goto pop;
  }

  /* Select a pivot element, move it to the left. */
  pm = (char *)a + (n / 2) * es;
  if (n > 7) {
    pl = a;
    pn = (char *)a + (n - 1) * es;
    if (n > 40) {
      d = (n / 8) * es;
      pl = med3(pl, pl + d, pl + 2 * d, cmp);
      pm = med3(pm - d, pm, pm + d, cmp);
      pn = med3(pn - 2 * d, pn - d, pn, cmp);
    }
    pm = med3(pl, pm, pn, cmp);
  }
  swap(a, pm);

  /*
   * Sort the array relative the pivot in four ranges as follows:
   * { elems == pivot, elems < pivot, elems > pivot, elems == pivot }
   */
  pa = pb = (char *)a + es;
  pc = pd = (char *)a + (n - 1) * es;
  for (;;) {
    /* Scan left to right stopping at first element > pivot. */
    while (pb <= pc && (cmp_result = cmp(pb, a)) <= 0) {
      /* Move elements == pivot to the left (to pa) */
      if (cmp_result == 0) {
        swap_cnt = 1;
        swap(pa, pb);
        pa += es;
      }
      pb += es;
    }
    /* Scan right to left stopping at first element < pivot. */
    while (pb <= pc && (cmp_result = cmp(pc, a)) >= 0) {
      /* Move elements == pivot to the right (to pd) */
      if (cmp_result == 0) {
        swap_cnt = 1;
        swap(pc, pd);
        pd -= es;
      }
      pc -= es;
    }
    if (pb > pc)
      break;
    /* The scan has found two elements to swap with each other. */
    swap(pb, pc);
    swap_cnt = 1;
    pb += es;
    pc -= es;
  }
  if (swap_cnt == 0) { /* Switch to insertion sort */
    for (pm = (char *)a + es; pm < (char *)a + n * es; pm += es)
      for (pl = pm; pl > (char *)a && cmp(pl - es, pl) > 0; pl -= es)
        swap(pl, pl - es);
    goto pop;
  }

  /*
   * Rearrange the array in three parts sorted like this:
   * { elements < pivot, elements == pivot, elements > pivot }
   */
  pn = (char *)a + n * es;
  r = min(pa - (char *)a, pb - pa);
  vecswap(a, pb - r, r);
  r = min(pd - pc, pn - pd - es);
  vecswap(pb, pn - r, r);
  d = pb - pa; /* d = Size of left part. */
  r = pd - pc; /* r = Size of right part. */
  pn -= r;     /* pn = Base of right part. */

  /*
   * Check which of the left and right parts are larger.
   * Set (a, n)  to (base, size) of the larger part.
   * Set (pa, r) to (base, size) of the smaller part.
   */
  if (r > d) { /* Right part is the larger part */
    pa = a;
    a = pn;
    n = r;
    r = d;
  } else { /* Left part is the larger part, or both are equal. */
    pa = pn;
    n = d;
  }

  /*
   * The left and right parts each need further sorting if they
   * contain two elements or more. If both need sorting we use
   * recursion to sort the smaller part and save the larger part
   * to be sorted by iteration after the recursion.
   * Using recursion only for the smaller part guarantees a
   * recursion depth that is bounded to be less than (log2(n)).
   */
  if (r > es) { /* Smaller part > 1 element. Both parts need sorting. */
    if (recursion_level < PARAMETER_STACK_LEVELS) {
      /*
       * The smaller part needs to be recursively sorted
       * before the larger part is sorted. To avoid function
       * call recursion the parameters for the larger part
       * are pushed on the parameter_stack array. The smaller
       * part is sorted using iteration and the larger part
       * will be sorted when the parameter_stack is popped
       * after the smaller part has been sorted.
       */
      parameter_stack[recursion_level].a = a;
      parameter_stack[recursion_level].n = n / es;
      recursion_level++;
      a = pa;
      n = r / es;
      goto loop;
    } else {
      /*
       * The parameter_stack array is full. The smaller part
       * is sorted using function call recursion. The larger
       * part will be sorted after the function call returns.
       */
      my_qsort(pa, r / es, es, cmp);
    }
  }
  if (n > es) { /* The larger part needs sorting. Iterate to sort.  */
    n = n / es;
    goto loop;
  }
  /* Both left and right parts are one element or less - level done. */
pop:
  if (recursion_level != 0) {
    recursion_level--;
    a = parameter_stack[recursion_level].a;
    n = parameter_stack[recursion_level].n;
    goto loop;
  }
}
