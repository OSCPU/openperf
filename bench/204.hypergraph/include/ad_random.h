#ifndef AD_RANDOM_INCLUDED
#define AD_RANDOM_INCLUDED

/* COPYRIGHT C 1991- Ali Dasdan */

/* initializes random number generator with seed or */
/* with any value if seed = -1 */
long randomize(long seed);

/* generates a int random number in [min, max] */
/* if int output is needed, prms are true min & max */
int irandom(int min, int max);

#endif
