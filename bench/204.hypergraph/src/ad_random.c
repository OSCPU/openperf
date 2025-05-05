
/* COPYRIGHT C 1991- Ali Dasdan */

#include "ad_random.h"
#include <bench.h>
#include <stdlib.h>

/* initializes random number generator with seed or */
/* with any value if seed = -1 */
long randomize(long seed) {
  long in_seed = seed;
  bench_srand(in_seed);
  return in_seed;
} /* randomize */

/* generates a int random number in [min, max] */
/* if int output is needed, prms are true min & max */
int irandom(int min, int max) {
  if (min >= max) {
    return min;
  } else {
    int retval = bench_rand() % (max - min + 1) + min;
    if (retval > max) {
      retval = max;
    }
    return retval;
  } /* else */
} /* irandom */

/* EOF */
