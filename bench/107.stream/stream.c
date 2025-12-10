/*-----------------------------------------------------------------------*/
/* Program: STREAM                                                       */
/* Revision: $Id: stream.c,v 5.10 2013/01/17 16:01:06 mccalpin Exp mccalpin $ */
/* Original code developed by John D. McCalpin                           */
/* Programmers: John D. McCalpin                                         */
/*              Joe R. Zagar                                             */
/*                                                                       */
/* This program measures memory transfer rates in MB/s for simple        */
/* computational kernels coded in C.                                     */
/*-----------------------------------------------------------------------*/
/* Copyright 1991-2013: John D. McCalpin                                 */
/*-----------------------------------------------------------------------*/
/* License:                                                              */
/*  1. You are free to use this program and/or to redistribute           */
/*     this program.                                                     */
/*  2. You are free to modify this program for your own use,             */
/*     including commercial use, subject to the publication              */
/*     restrictions in item 3.                                           */
/*  3. You are free to publish results obtained from running this        */
/*     program, or from works that you derive from this program,         */
/*     with the following limitations:                                   */
/*     3a. In order to be referred to as "STREAM benchmark results",     */
/*         published results must be in conformance to the STREAM        */
/*         Run Rules, (briefly reviewed below) published at              */
/*         http://www.cs.virginia.edu/stream/ref.html                    */
/*         and incorporated herein by reference.                         */
/*         As the copyright holder, John McCalpin retains the            */
/*         right to determine conformity with the Run Rules.             */
/*     3b. Results based on modified source code or on runs not in       */
/*         accordance with the STREAM Run Rules must be clearly          */
/*         labelled whenever they are published.  Examples of            */
/*         proper labelling include:                                     */
/*           "tuned STREAM benchmark results"                            */
/*           "based on a variant of the STREAM benchmark code"           */
/*         Other comparable, clear, and reasonable labelling is          */
/*         acceptable.                                                   */
/*     3c. Submission of results to the STREAM benchmark web site        */
/*         is encouraged, but not required.                              */
/*  4. Use of this program or creation of derived works based on this    */
/*     program constitutes acceptance of these licensing restrictions.   */
/*  5. Absolutely no warranty is expressed or implied.                   */
/*-----------------------------------------------------------------------*/
#include <bench.h>
#include <unistd.h>

/*-----------------------------------------------------------------------
 * INSTRUCTIONS:
 *
 *	1) STREAM requires different amounts of memory to run on different
 *           systems, depending on both the system cache size(s) and the
 *           granularity of the system timer.
 *     You should adjust the value of 'STREAM_ARRAY_SIZE' (below)
 *           to meet *both* of the following criteria:
 *       (a) Each array must be at least 4 times the size of the
 *           available cache memory. I don't worry about the difference
 *           between 10^6 and 2^20, so in practice the minimum array size
 *           is about 3.8 times the cache size.
 *           Example 1: One Xeon E3 with 8 MB L3 cache
 *               STREAM_ARRAY_SIZE should be >= 4 million, giving
 *               an array size of 30.5 MB and a total memory requirement
 *               of 91.5 MB.  
 *           Example 2: Two Xeon E5's with 20 MB L3 cache each (using OpenMP)
 *               STREAM_ARRAY_SIZE should be >= 20 million, giving
 *               an array size of 153 MB and a total memory requirement
 *               of 458 MB.  
 *       (b) The size should be large enough so that the 'timing calibration'
 *           output by the program is at least 20 clock-ticks.  
 *           Example: most versions of Windows have a 10 millisecond timer
 *               granularity.  20 "ticks" at 10 ms/tic is 200 milliseconds.
 *               If the chip is capable of 10 GB/s, it moves 2 GB in 200 msec.
 *               This means the each array must be at least 1 GB, or 128M elements.
 *
 *      Version 5.10 increases the default array size from 2 million
 *          elements to 10 million elements in response to the increasing
 *          size of L3 caches.  The new default size is large enough for caches
 *          up to 20 MB. 
 *      Version 5.10 changes the loop index variables from "register int"
 *          to "ssize_t", which allows array indices >2^32 (4 billion)
 *          on properly configured 64-bit systems.  Additional compiler options
 *          (such as "-mcmodel=medium") may be required for large memory runs.
 *
 *      Array size can be set at compile time without modifying the source
 *          code for the (many) compilers that support preprocessor definitions
 *          on the compile line.  E.g.,
 *                gcc -O -DSTREAM_ARRAY_SIZE=100000000 stream.c -o stream.100M
 *          will override the default size of 10M with a new size of 100M elements
 *          per array.
 */
//#ifndef STREAM_ARRAY_SIZE
//#define STREAM_ARRAY_SIZE 10000000
//#endif

/*  2) STREAM runs each kernel "NTIMES" times and reports the *best* result
 *         for any iteration after the first, therefore the minimum value
 *         for NTIMES is 2.
 *      There are no rules on maximum allowable values for NTIMES, but
 *         values larger than the default are unlikely to noticeably
 *         increase the reported performance.
 *      NTIMES can also be set on the compile line without changing the source
 *         code using, for example, "-DNTIMES=7".
 */
#ifdef NTIMES
#if NTIMES <= 1
#define NTIMES 100
#endif
#endif
#ifndef NTIMES
#define NTIMES 100
#endif

/*  Users are allowed to modify the "OFFSET" variable, which *may* change the
 *         relative alignment of the arrays (though compilers may change the 
 *         effective offset by making the arrays non-contiguous on some systems). 
 *      Use of non-zero values for OFFSET can be especially helpful if the
 *         STREAM_ARRAY_SIZE is set to a value close to a large power of 2.
 *      OFFSET can also be set on the compile line without changing the source
 *         code using, for example, "-DOFFSET=56".
 */
#ifndef OFFSET
#define OFFSET 0
#endif

/*
 *	3) Compile the code with optimization.  Many compilers generate
 *       unreasonably bad code before the optimizer tightens things up.  
 *     If the results are unreasonably good, on the other hand, the
 *       optimizer might be too smart for me!
 *
 *     For a simple single-core version, try compiling with:
 *            cc -O stream.c -o stream
 *     This is known to work on many, many systems....
 *
 *     To use multiple cores, you need to tell the compiler to obey the OpenMP
 *       directives in the code.  This varies by compiler, but a common example is
 *            gcc -O -fopenmp stream.c -o stream_omp
 *       The environment variable OMP_NUM_THREADS allows runtime control of the 
 *         number of threads/cores used when the resulting "stream_omp" program
 *         is executed.
 *
 *     To run with single-precision variables and arithmetic, simply add
 *         -DSTREAM_TYPE=float
 *     to the compile line.
 *     Note that this changes the minimum array sizes required --- see (1) above.
 *
 *     The preprocessor directive "TUNED" does not do much -- it simply causes the 
 *       code to call separate functions to execute each kernel.  Trivial versions
 *       of these functions are provided, but they are *not* tuned -- they just 
 *       provide predefined interfaces to be replaced with tuned code.
 *
 *
 *	4) Optional: Mail the results to mccalpin@cs.virginia.edu
 *	   Be sure to include info that will help me understand:
 *		a) the computer hardware configuration (e.g., processor model, memory type)
 *		b) the compiler name/version and compilation flags
 *      c) any run-time information (such as OMP_NUM_THREADS)
 *		d) all of the output from the test case.
 *
 * Thanks!
 *
 *-----------------------------------------------------------------------*/

#define HLINE "-------------------------------------------------------------\n"

#ifndef MIN
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#endif
#ifndef MAX
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#endif

#ifndef STREAM_TYPE
#define STREAM_TYPE unsigned
#endif

static const struct {
  int size;
  uint32_t cs_a, cs_b, cs_c;
  uint64_t ref_time;
} *ps, settings[BENCH_NR_SETTING] = {
         {4, 0x707a8b17, 0xf7e16681, 0xad1d27be, 0},
         {3000, 0xc21564df, 0x3e96caf9, 0x4c96496f, 270},
         {4000000, 0x2050cd0a, 0x3d6ba970, 0xbfdfc1de, 469729},
         {200000000, 0x7b8e1456, 0x4c83c711, 0x5408d901, 28553508},
};

static STREAM_TYPE *a, *b, *c;
static unsigned long long avgtime[4] = {0}, maxtime[4] = {0},
                          mintime[4] = {UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX};
static char *label[4] = {"Copy:      ", "Scale:     ", "Add:       ", "Triad:     "};
static int STREAM_ARRAY_SIZE;

extern void checkSTREAMresults();
#ifdef TUNED
extern void tuned_STREAM_Copy();
extern void tuned_STREAM_Scale(STREAM_TYPE scalar);
extern void tuned_STREAM_Add();
extern void tuned_STREAM_Triad(STREAM_TYPE scalar);
#endif
#ifdef _OPENMP
extern int omp_get_num_threads();
#endif

static uint64_t times[4][NTIMES];
static unsigned long long bytes[4];

void bench_init(int setting) {
  int quantum, checktick();
  int BytesPerWord;
  int j;
  uint64_t t;

  ps = &settings[setting];
  STREAM_ARRAY_SIZE = ps->size;

  a = malloc(sizeof(STREAM_TYPE) * (STREAM_ARRAY_SIZE + OFFSET));
  b = malloc(sizeof(STREAM_TYPE) * (STREAM_ARRAY_SIZE + OFFSET));
  c = malloc(sizeof(STREAM_TYPE) * (STREAM_ARRAY_SIZE + OFFSET));
  assert(a != NULL);
  assert(b != NULL);
  assert(c != NULL);

  bytes[0] = 2 * sizeof(STREAM_TYPE) * STREAM_ARRAY_SIZE;
  bytes[1] = 2 * sizeof(STREAM_TYPE) * STREAM_ARRAY_SIZE;
  bytes[2] = 3 * sizeof(STREAM_TYPE) * STREAM_ARRAY_SIZE;
  bytes[3] = 3 * sizeof(STREAM_TYPE) * STREAM_ARRAY_SIZE;

  /* --- SETUP --- determine precision and check timing --- */

  printf(HLINE);
  printf("STREAM version $Revision: 5.10 $\n");
  printf(HLINE);
  BytesPerWord = sizeof(STREAM_TYPE);
  printf("This system uses %d bytes per array element.\n", BytesPerWord);

  printf(HLINE);
#ifdef N
  printf("*****  WARNING: ******\n");
  printf("      It appears that you set the preprocessor variable N when compiling this code.\n");
  printf("      This version of the code uses the preprocessor variable STREAM_ARRAY_SIZE to control the array size\n");
  printf("      Reverting to default value of STREAM_ARRAY_SIZE=%llu\n", (unsigned long long)STREAM_ARRAY_SIZE);
  printf("*****  WARNING: ******\n");
#endif

  printf("Array size = %llu (elements), Offset = %d (elements)\n", (unsigned long long)STREAM_ARRAY_SIZE, OFFSET);
  printf("Memory per array = %lld MiB (%lld KiB).\n", 1ull * BytesPerWord * STREAM_ARRAY_SIZE / 1024 / 1024,
         1ull * BytesPerWord * STREAM_ARRAY_SIZE / 1024);
  printf("Total memory required = %lld MiB (%lld KiB).\n", 3ull * BytesPerWord * STREAM_ARRAY_SIZE / 1024 / 1024,
         3ull * BytesPerWord * STREAM_ARRAY_SIZE / 1024);
  printf("Each kernel will be executed %d times.\n", NTIMES);
  printf(" The *best* time for each kernel (excluding the first iteration)\n");
  printf(" will be used to compute the reported bandwidth.\n");

#ifdef _OPENMP
  printf(HLINE);
#pragma omp parallel
  {
#pragma omp master
    {
      k = omp_get_num_threads();
      printf("Number of Threads requested = %i\n", k);
    }
  }
#endif

#ifdef _OPENMP
  k = 0;
#pragma omp parallel
#pragma omp atomic
  k++;
  printf("Number of Threads counted = %i\n", k);
#endif

  /* Get initial value for system clock. */
  for (j = 0; j < STREAM_ARRAY_SIZE; j++) {
    a[j] = 1;
    b[j] = 2;
    c[j] = 0;
  }

  printf(HLINE);

  if ((quantum = checktick()) >= 1)
    printf(
        "Your clock granularity/precision appears to be "
        "%d microseconds.\n",
        quantum);
  else {
    printf(
        "Your clock granularity appears to be "
        "less than one microsecond.\n");
    quantum = 1;
  }

  t = bench_uptime();
  for (j = 0; j < STREAM_ARRAY_SIZE; j++)
    a[j] = 2 * a[j];
  t = bench_uptime() - t;

  printf(
      "Each test below will take on the order"
      " of %d microseconds.\n",
      (int)t);
  printf("   (= %d clock ticks)\n", (int)(t / quantum));
  printf("Increase the size of the arrays if this shows that\n");
  printf("you are not getting at least 20 clock ticks per test.\n");

  printf(HLINE);

  printf("WARNING -- The above is only a rough guideline.\n");
  printf("For best results, please be sure you know the\n");
  printf("precision of your system timer.\n");
  printf(HLINE);
}

uint64_t bench_run() {
  /*	--- MAIN LOOP --- repeat test cases NTIMES times --- */

  int j, k;
  STREAM_TYPE scalar = 3;
  for (k = 0; k < NTIMES; k++) {
    times[0][k] = bench_uptime();
#ifdef TUNED
    tuned_STREAM_Copy();
#else
    for (j = 0; j < STREAM_ARRAY_SIZE; j++)
      c[j] = a[j];
#endif
    times[0][k] = bench_uptime() - times[0][k];

    times[1][k] = bench_uptime();
#ifdef TUNED
    tuned_STREAM_Scale(scalar);
#else
    for (j = 0; j < STREAM_ARRAY_SIZE; j++)
      b[j] = scalar * c[j];
#endif
    times[1][k] = bench_uptime() - times[1][k];

    times[2][k] = bench_uptime();
#ifdef TUNED
    tuned_STREAM_Add();
#else
    for (j = 0; j < STREAM_ARRAY_SIZE; j++)
      c[j] = a[j] + b[j];
#endif
    times[2][k] = bench_uptime() - times[2][k];

    times[3][k] = bench_uptime();
#ifdef TUNED
    tuned_STREAM_Triad(scalar);
#else
    for (j = 0; j < STREAM_ARRAY_SIZE; j++)
      a[j] = b[j] + scalar * c[j];
#endif
    times[3][k] = bench_uptime() - times[3][k];
  }
  return ps->ref_time;
}

int bench_validate() {
  /*	--- SUMMARY --- */

  int j, k;
  for (k = 1; k < NTIMES; k++) /* note -- skip first iteration */
  {
    for (j = 0; j < 4; j++) {
      avgtime[j] = avgtime[j] + times[j][k];
      mintime[j] = MAX(MIN(mintime[j], times[j][k]), 1);
      maxtime[j] = MAX(maxtime[j], times[j][k]);
    }
  }

  printf("Function    Best Rate KB/s  Avg time(us) Min time(us) Max time(us)\n");
  for (j = 0; j < 4; j++) {
    avgtime[j] = avgtime[j] / (NTIMES - 1);

    printf("%s%12lld  %11lld  %11lld  %11lld\n", label[j], bytes[j] * 1024 / mintime[j], avgtime[j], mintime[j],
           maxtime[j]);
  }
  printf(HLINE);

  /* --- Check Results --- */
  checkSTREAMresults();
  printf(HLINE);

  uint32_t cs_a = bench_checksum(a, a + STREAM_ARRAY_SIZE);
  uint32_t cs_b = bench_checksum(b, b + STREAM_ARRAY_SIZE);
  uint32_t cs_c = bench_checksum(c, c + STREAM_ARRAY_SIZE);
  int fail = (cs_a != ps->cs_a) || (cs_b != ps->cs_b) || (cs_c != ps->cs_c);
  return fail;
}

#define M 20

int checktick() {
  int i, minDelta, Delta;
  uint64_t t1, t2, timesfound[M];

  /*  Collect a sequence of M unique time values from the system. */

  for (i = 0; i < M; i++) {
    t1 = bench_uptime();
    int j = 0;
    while (((t2 = bench_uptime()) - t1) < 1) {
      j++;
      if (j == 10) {
        t2 = t1 + 1;
        break;
      }
    }
    timesfound[i] = t1 = t2;
  }

  /*
 * Determine the minimum difference between these M values.
 * This result will be our estimate (in microseconds) for the
 * clock granularity.
 */

  minDelta = 1000000;
  for (i = 1; i < M; i++) {
    Delta = (int)(timesfound[i] - timesfound[i - 1]);
    minDelta = MIN(minDelta, MAX(Delta, 0));
  }

  return (minDelta);
}

#ifndef abs
#define abs(a) ((a) >= 0 ? (a) : -(a))
#endif
void checkSTREAMresults() {
  STREAM_TYPE aj, bj, cj, scalar;
  unsigned long long aSumErr, bSumErr, cSumErr;
  int j, k, ierr, err;

  /* reproduce initialization */
  aj = 1;
  bj = 2;
  cj = 0;
  /* a[] is modified during timing check */
  aj = 2 * aj;
  /* now execute timing loop */
  scalar = 3;
  for (k = 0; k < NTIMES; k++) {
    cj = aj;
    bj = scalar * cj;
    cj = aj + bj;
    aj = bj + scalar * cj;
  }

  /* accumulate deltas between observed and expected results */
  aSumErr = 0;
  bSumErr = 0;
  cSumErr = 0;
  for (j = 0; j < STREAM_ARRAY_SIZE; j++) {
    aSumErr += abs(a[j] - aj);
    bSumErr += abs(b[j] - bj);
    cSumErr += abs(c[j] - cj);
    // if (j == 417) printf("Index 417: c[j]: %f, cj: %f\n",c[j],cj);	// MCCALPIN
  }

  err = 0;
  if (aSumErr != 0) {
    err++;
    printf("Failed Validation on array a[]\n");
    printf("     Expected Value: %d\n", aj);
    ierr = 0;
    for (j = 0; j < STREAM_ARRAY_SIZE; j++) {
      if (a[j] != aj) {
        ierr++;
        if (ierr < 10) {
          printf("         array a: index: %d, expected: %d, observed: %d\n", j, aj, a[j]);
        }
      }
    }
    printf("     For array a[], %d errors were found.\n", ierr);
  }
  if (bSumErr != 0) {
    err++;
    printf("Failed Validation on array b[]\n");
    printf("     Expected Value: %d\n", bj);
    ierr = 0;
    for (j = 0; j < STREAM_ARRAY_SIZE; j++) {
      if (b[j] != bj) {
        ierr++;
        if (ierr < 10) {
          printf("         array b: index: %d, expected: %d, observed: %d\n", j, bj, b[j]);
        }
      }
    }
    printf("     For array b[], %d errors were found.\n", ierr);
  }
  if (cSumErr != 0) {
    err++;
    printf("Failed Validation on array c[]\n");
    printf("     Expected Value: %d\n", cj);
    ierr = 0;
    for (j = 0; j < STREAM_ARRAY_SIZE; j++) {
      if (c[j] != cj) {
        ierr++;
        if (ierr < 10) {
          printf("         array c: index: %d, expected: %d, observed: %d\n", j, cj, c[j]);
        }
      }
    }
    printf("     For array c[], %d errors were found.\n", ierr);
  }
  if (err == 0) {
    printf("Solution Validates: no error on all three arrays\n");
  } else {
    printf("Results Validation Verbose Results: \n");
    printf("    Expected a(1), b(1), c(1): %d %d %d \n", aj, bj, cj);
    printf("    Observed a(1), b(1), c(1): %d %d %d \n", a[1], b[1], c[1]);
    printf("    SumErr on a, b, c:         %lld %lld %lld \n", aSumErr, bSumErr, cSumErr);
  }
}

#ifdef TUNED
/* stubs for "tuned" versions of the kernels */
void tuned_STREAM_Copy() {
  ssize_t j;
#pragma omp parallel for
  for (j = 0; j < STREAM_ARRAY_SIZE; j++)
    c[j] = a[j];
}

void tuned_STREAM_Scale(STREAM_TYPE scalar) {
  ssize_t j;
#pragma omp parallel for
  for (j = 0; j < STREAM_ARRAY_SIZE; j++)
    b[j] = scalar * c[j];
}

void tuned_STREAM_Add() {
  ssize_t j;
#pragma omp parallel for
  for (j = 0; j < STREAM_ARRAY_SIZE; j++)
    c[j] = a[j] + b[j];
}

void tuned_STREAM_Triad(STREAM_TYPE scalar) {
  ssize_t j;
#pragma omp parallel for
  for (j = 0; j < STREAM_ARRAY_SIZE; j++)
    a[j] = b[j] + scalar * c[j];
}
/* end of stubs for the "tuned" versions of the kernels */
#endif
