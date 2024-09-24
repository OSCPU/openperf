/* the following is optional depending on the timing function used */

/* map the FORTRAN math functions, etc. to the C versions */
#define DSIN sin
#define DCOS cos
#define DATAN atan
#define DLOG log
#define DEXP exp
#define DSQRT sqrt
#define IF if

/* function prototypes */
void POUT(long N, long J, long K, double X1, double X2, double X3, double X4);
void PA(double E[]);
void P0(void);
void P3(double X, double Y, double *Z);
#define USAGE "usage: whetdc [-c] [loops]\n"

/*
        COMMON T,T1,T2,E1(4),J,K,L
*/

typedef struct {
  long loopstart;
} bench_whestone_config;
