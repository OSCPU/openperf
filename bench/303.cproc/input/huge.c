#define R_5(x)       x x x x x
#define R_10(x)      R_5(x) R_5(x)
#define R_100(x)     R_10(R_10(x))
#define R_1000(x)    R_10(R_100(x))
#define R_10000(x)   R_100(R_100(x))
#define R_100000(x)  R_10(R_10000(x))
#define R_1000000(x) R_10(R_100000(x))
#define R_5000000(x) R_5(R_1000000(x))
#define X                  \
  {                        \
    k++;                   \
    printf("k = %d\n", k); \
  }

int printf(const char *fmt, ...);
int k = 0;
int main() {
  R_5000000(X)
  return 0;
}
