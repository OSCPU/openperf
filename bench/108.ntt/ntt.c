// ported from https://github.com/Nedal-haltam/NTT/blob/abf0e919d689560443f626c7490e831d0aa00f5e/cmain.cpp

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Vec {
  int *a;
  int len;
} Vec;

Vec newVec(int len) {
  Vec v = {.len = len};
  v.a = calloc(1, len * sizeof(int));
  return v;
}

int mod_pow(int base, int exp, int mod) {
  int result = 1;
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
    printf("%d, ", a.a[i]);
  }
  printf("%d]\n", a.a[a.len - 1]);
}

Vec ntt_naive(Vec a, int pr, int mod, bool invert) {
  int n = a.len;
  Vec A = newVec(n);
  int root = mod_pow(pr, (mod - 1) / n, mod);
  if (invert)
    root = mod_pow(root, mod - 2, mod);
  for (int k = 0; k < n; ++k) {
    for (int j = 0; j < n; ++j) {
      int power = ((1LL * j * k) % n);
      int omega = mod_pow(root, power, mod);
      A.a[k] = (A.a[k] + 1LL * a.a[j] * omega % mod) % mod;
    }
  }
  if (invert) {
    int n_inv = mod_pow(n, mod - 2, mod);
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
  memcpy(fa.a, a.a, a.len * sizeof(int));
  memcpy(fb.a, b.a, b.len * sizeof(int));

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

int main() {
  int p = 7681;
  int pr = 17;
  Vec a = newVec(10);
  for (int i = 0; i < 10; i++) {
    a.a[i] = i + 1;
  }
  Vec b = newVec(5);
  for (int i = 0; i < 5; i++) {
    b.a[i] = i + 1;
  }
  printf("The prime number is : %d\n", p);
  printf("The primitive root is : %d\n", pr);
  printf("The first polynomial is : \n");
  DisplayVector(a);
  printf("The second polynomial is : \n");
  DisplayVector(b);
  printf("The result of polynomial multiplication is : \n");
  Vec c = NTTMultiply(a, b, pr, p);
  DisplayVector(c);

  printf("Checking result...\n");
  int wrong = 0;
  Vec ValidC = NaivePolynomialMult(a, b);
  for (int i = 0; i < ValidC.len; i++) {
    if (c.a[i] != ValidC.a[i]) {
      printf("Error in NTT multiplication at index %d: expected %d, got %d\n", i, ValidC.a[i], c.a[i]);
      printf("The result of naive polynomial multiplication is : \n");
      DisplayVector(ValidC);
      wrong = 1;
      break;
    }
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
