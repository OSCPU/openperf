// ported from https://github.com/Nedal-haltam/NTT/blob/abf0e919d689560443f626c7490e831d0aa00f5e/cmain.cpp

#include <bench.h>
#include <stdbool.h>

static const struct {
  int alen, blen;
  uint32_t cs;
  uint64_t ref_time;
} *ps, settings[BENCH_NR_SETTING] = {
         {2, 2, 0xe052005f, 0},
         {8, 8, 0x977ed4e2, 7},
         {300, 300, 0xbb2f314d, 66168},
         {5000, 5000, 0x7344b1bf, 24822314},
};

typedef uint32_t T;
typedef struct Vec {
  T *a;
  int len;
} Vec;

Vec newVec(int len) {
  Vec v = {.len = len};
  v.a = calloc(1, len * sizeof(v.a[0]));
  return v;
}

T mod_pow(T base, T exp, T mod) {
  T result = 1;
  base %= mod;
  while (exp > 0) {
    if (exp & 1)
      result = (1LL * result * base) % mod;
    base = (1LL * base * base) % mod;
    exp >>= 1;
  }
  return result;
}

void DisplayVector(Vec a) {
  printf("[");
  for (int i = 0; i < a.len - 1; i++) {
    printf("%u, ", a.a[i]);
  }
  printf("%u]\n", a.a[a.len - 1]);
}

Vec ntt_naive(Vec a, T pr, T mod, bool invert) {
  int n = a.len;
  Vec A = newVec(n);
  T root = mod_pow(pr, (mod - 1) / n, mod);
  if (invert)
    root = mod_pow(root, mod - 2, mod);
  for (int k = 0; k < n; ++k) {
    for (int j = 0; j < n; ++j) {
      T power = ((1LL * j * k) % n);
      T omega = mod_pow(root, power, mod);
      A.a[k] = (A.a[k] + 1LL * a.a[j] * omega % mod) % mod;
    }
  }
  if (invert) {
    T n_inv = mod_pow(n, mod - 2, mod);
    for (int i = 0; i < A.len; i++) {
      A.a[i] = (1LL * A.a[i] * n_inv) % mod;
    }
  }
  return A;
}

Vec NTTMultiply(Vec a, Vec b, int root, int mod) {
  int n = 1;
  while (n < a.len + b.len)
    n <<= 1;

  Vec fa = newVec(n), fb = newVec(n);
  memcpy(fa.a, a.a, a.len * sizeof(a.a[0]));
  memcpy(fb.a, b.a, b.len * sizeof(b.a[0]));

  Vec tmp = ntt_naive(fa, root, mod, false);
  free(fa.a);
  fa = tmp;

  tmp = ntt_naive(fb, root, mod, false);
  free(fb.a);
  fb = tmp;

  for (int i = 0; i < n; i++) {
    fa.a[i] = (1LL * fa.a[i] * fb.a[i]) % mod;
  }

  tmp = ntt_naive(fa, root, mod, true);
  free(fa.a);
  free(fb.a);
  return tmp;
}

Vec NaivePolynomialMult(Vec a, Vec b) {
  Vec c = newVec(a.len + b.len - 1);
  for (int i = 0; i < a.len; i++) {
    for (int j = 0; j < b.len; j++) {
      c.a[i + j] += a.a[i] * b.a[j];
    }
  }
  return c;
}

static const T p = 998244353;
static const T pr = 3;
static Vec a, b, c;

void bench_init(int setting) {
  ps = &settings[setting];
  bench_srand(1);
  a = newVec(settings[setting].alen);
  for (int i = 0; i < a.len; i++) {
    a.a[i] = bench_rand() & 0xff;
  }
  b = newVec(settings[setting].blen);
  for (int i = 0; i < b.len; i++) {
    b.a[i] = bench_rand() & 0xff;
  }
  printf("The prime number is : %u\n", p);
  printf("The primitive root is : %u\n", pr);
  printf("The length of the 1st polynomial is : %d\n", a.len);
  printf("The length of the 2nd polynomial is : %d\n", b.len);
}

uint64_t bench_run() {
  printf("Computing the result of polynomial multiplication...\n");
  c = NTTMultiply(a, b, pr, p);
  return ps->ref_time;
}

int bench_validate() {
  printf("Checking result...\n");
  int wrong = 0;
  Vec ValidC = NaivePolynomialMult(a, b);
  for (int i = 0; i < ValidC.len; i++) {
    if (c.a[i] != ValidC.a[i]) {
      printf("Error in NTT multiplication at index %d: expected %u, got %u\n", i, ValidC.a[i], c.a[i]);
      printf("The result of polynomial multiplication is : \n");
      DisplayVector(c);
      printf("The result of naive polynomial multiplication is : \n");
      DisplayVector(ValidC);
      wrong = 1;
      break;
    }
  }

  uint32_t checksum = bench_checksum(c.a, c.a + c.len);
  printf("cs = 0x%08x\n", checksum);
  if (ps->cs != checksum) {
    wrong = 1;
  }

  if (wrong) {
    printf("Wrong result!\n");
  }

  free(a.a);
  free(b.a);
  free(c.a);
  free(ValidC.a);
  return wrong;
}
