
/* COPYRIGHT C 1991- Ali Dasdan */

#include "ad_fileio.h"
#include <bench.h>
#include <stdlib.h>
#include <string.h>

/* open file fp with filename = fname and mode = mode */
void open_file(FILE **fp, char *fname, char *mode) {
  if ((*fp = fopen(fname, mode)) == NULL) {
    printf("Error: File %s can NOT be opened with mode %s\n", fname, mode);
    bench_exit(1);
  }
} /* open_file */

/* close file fp */
void close_file(FILE **fp) {
  if (fclose(*fp) != 0) {
    printf("Error: Cannot close file\n");
    bench_exit(1);
  }
} /* close_file */

/* EOF */
