/*
 *
 * MINCTEST - Minimal C Test Library - 0.1
 *
 * Copyright (c) 2014, 2015, 2016 Lewis Van Winkle
 *
 * http://CodePlea.com
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgement in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 */

/*
 * MINCTEST - Minimal testing library for C
 *
 *
 * Example:
 *
 *      void test1() {
 *           lok('a' == 'a');
 *      }
 *
 *      void test2() {
 *           lequal(5, 6);
 *           lfequal(5.5, 5.6);
 *      }
 *
 *      int main() {
 *           lrun("test1", test1);
 *           lrun("test2", test2);
 *           lresults();
 *           return lfails != 0;
 *      }
 *
 *
 *
 * Hints:
 *      All functions/variables start with the letter 'l'.
 *
 */

#ifndef __MINCTEST_H__
#define __MINCTEST_H__

#include <math.h>
#include <stdio.h>
#include <time.h>

/* How far apart can floats be before we consider them unequal. */
#define LTEST_FLOAT_TOLERANCE 0.001
#define LTEST_SCALE_TOLERANCE (SCALE / 1000)

/* Track the number of passes, fails. */
/* NB this is made for all tests to be in one file. */
static int ltests = 0;
static int lfails = 0;

/* Display the test results. */
#define lresults()                                                    \
  do {                                                                \
    if (lfails == 0) {                                                \
      printf("ALL TESTS PASSED (%d/%d)\n", ltests, ltests);           \
    } else {                                                          \
      printf("SOME TESTS FAILED (%d/%d)\n", ltests - lfails, ltests); \
    }                                                                 \
  } while (0)

/* Run a test. Name can be any string to print out, test is the function name to call. */
#define lrun(name, test)                                                                                          \
  do {                                                                                                            \
    const int ts = ltests;                                                                                        \
    const int fs = lfails;                                                                                        \
    const unsigned long long start = bench_uptime();                                                              \
    printf("\t%-14s", name);                                                                                      \
    test();                                                                                                       \
    printf("pass:%2d   fail:%2d   %lldus\n", (ltests - ts) - (lfails - fs), lfails - fs, bench_uptime() - start); \
  } while (0)

/* Assert a true statement. */
#define lok(test)                                   \
  do {                                              \
    ++ltests;                                       \
    if (!(test)) {                                  \
      ++lfails;                                     \
      printf("%s:%d error \n", __FILE__, __LINE__); \
    }                                               \
  } while (0)

/* Assert two integers are equal. */
#define lequal(a, b)                                              \
  do {                                                            \
    ++ltests;                                                     \
    if ((a) != (b)) {                                             \
      ++lfails;                                                   \
      printf("%s:%d (%d != %d)\n", __FILE__, __LINE__, (a), (b)); \
    }                                                             \
  } while (0)

/* Assert two floats are equal (Within LTEST_FLOAT_TOLERANCE). */
#define lfequal(a, b)                                                          \
  do {                                                                         \
    ++ltests;                                                                  \
    int _a = a, _b = b;                                                        \
    if (abs((_a) - (_b)) > LTEST_SCALE_TOLERANCE) {                            \
      ++lfails;                                                                \
      printf("%s:%d (%d(scaled != %d(scaled))\n", __FILE__, __LINE__, _a, _b); \
    }                                                                          \
  } while (0)

#endif /*__MINCTEST_H__*/
