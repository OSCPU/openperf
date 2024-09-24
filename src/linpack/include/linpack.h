#ifndef __LINPACK_H__
#define __LINPACK_H__

#define FLT_DIG 6
#define DBL_DIG 15

#define SP

#ifndef SP
#ifndef DP
#define DP
#endif
#endif

#ifdef SP
#define ZERO 0.0
#define ONE 1.0
#define PREC "Single"
#define BASE10DIG FLT_DIG

typedef float REAL;
#endif

#ifdef DP
#define ZERO 0.0e0
#define ONE 1.0e0
#define PREC "Double"
#define BASE10DIG DBL_DIG

typedef double REAL;
#endif

/* 2022-07-26: Macro defined for memreq variable to resolve warnings
 *             during malloc check
 */
#define MEM_T long


typedef struct {
  int arsize;
} bench_linpack_config ;

#endif
