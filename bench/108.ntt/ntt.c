// ported from https://github.com/Nedal-haltam/NTT/blob/abf0e919d689560443f626c7490e831d0aa00f5e/cmain.cpp

#include <algorithm>
#include <complex>
#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <assert.h>
#include <iomanip>
#include <math.h>
#include <time.h>

using namespace std;

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

template <class T> void DisplayVector(vector<T> vec) {
  cout << "[";
  for (size_t i = 0; i < vec.size() - 1; i++) {
    cout << vec[i] << ", ";
  }
  cout << vec[vec.size() - 1];
  cout << "]\n";
}

template <class T> void FillVectorRandom(vector<T> &vec, T a, T b, T (*GetRandomT)(T, T)) {
  for (size_t i = 0; i < vec.size(); i++)
    vec[i] = GetRandomT(a, b);
}

template <class T> bool CompareVectors(vector<T> &c, vector<T> &cother) {
  assert(c.size() == cother.size());
  for (size_t i = 0; i < c.size(); i++) {
    if (c[i] != cother[i]) {
      cout << "difference found\n";
      return false;
    }
  }
  return true;
}

clock_t clocker;
void StartClock() {
  clocker = clock();
}
void EvaluateClock(string Message) {
  clock_t t = clock() - clocker;
  cout << Message << "\n";
  cout << std::fixed << std::setprecision(3) << "Time taken: " << (double)(t) / CLOCKS_PER_SEC << "s\n";
}

int GetRandomInt(int a, int b) {
  return a + (rand() % (b - a + 1));
}

complex<double> GetRandomComplex(complex<double> a, complex<double> b) {
  complex<double> t(b - a + complex<double>(1, 1));
  return complex<double>(a.real() + rand() % (int)t.real(), a.imag() + rand() % (int)t.imag());
}

void bit_reverse_permutation(std::vector<int> &data) {
  int n = data.size();
  int bits = std::log2(n);

  for (int i = 0; i < n; ++i) {
    int rev = 0;
    int x = i;
    for (int j = 0; j < bits; ++j) {
      rev = (rev << 1) | (x & 1);
      x >>= 1;
    }
    if (i < rev) {
      std::swap(data[i], data[rev]);
    }
  }
}

vector<int> ntt_naive(vector<int> &a, int pr, int mod, bool invert = false) {
  int n = a.size();
  vector<int> A(n, 0);
  int root = mod_pow(pr, (mod - 1) / n, mod);
  if (invert)
    root = mod_pow(root, mod - 2, mod);
  for (int k = 0; k < n; ++k) {
    for (int j = 0; j < n; ++j) {
      int power = ((1LL * j * k) % n);
      int omega = mod_pow(root, power, mod);
      A[k] = (A[k] + 1LL * a[j] * omega % mod) % mod;
    }
  }
  if (invert) {
    int n_inv = mod_pow(n, mod - 2, mod);
    for (size_t i = 0; i < A.size(); i++) {
      A[i] = (1LL * A[i] * n_inv) % mod;
    }
  }
  return A;
}

vector<int> NTTMultiply(vector<int> &a, vector<int> &b, int root, int mod) {
  vector<int> fa(a), fb(b);
  size_t n = 1;
  while (n < a.size() + b.size())
    n <<= 1;
  fa.resize(n);
  fb.resize(n);
  fa = ntt_naive(fa, root, mod, false);
  fb = ntt_naive(fb, root, mod, false);
  for (size_t i = 0; i < n; i++) {
    fa[i] = (1LL * fa[i] * fb[i]) % mod;
  }
  return ntt_naive(fa, root, mod, true);
}

vector<int> NaivePolynomialMult(vector<int> &a, vector<int> &b) {
  vector<int> c(a.size() + b.size() - 1, 0);
  for (size_t i = 0; i < a.size(); i++) {
    for (size_t j = 0; j < b.size(); j++) {
      c[i + j] += a[i] * b[j];
    }
  }
  return c;
}

void TestNTT(int n, int p, int pr) {
  vector<int> a;
  for (int i = 0; i < n; i++)
    a.push_back(i + 1);
  vector<int> ntt = ntt_naive(a, pr, p);
  vector<int> intt = ntt_naive(ntt, pr, p, true);
  cout << "The prime number is : " << p << "\n";
  cout << "The primitive root is : " << pr << "\n";
  cout << "The original vector is : \n";
  DisplayVector(a);
  cout << "The NTT of the vector is : \n";
  DisplayVector(ntt);
  cout << "The inverse NTT of the vector is : \n";
  DisplayVector(intt);
}
int main() {
  srand(time(0));
  int n = 16;
  int p = 7681;
  int pr = 17;
  vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  vector<int> b = {1, 2, 3, 4, 5};
  cout << "Naive NTT Polynomial Multiplication\n";
  cout << "The prime number is : " << p << "\n";
  cout << "The primitive root is : " << pr << "\n";
  cout << "The first polynomial is : \n";
  DisplayVector(a);
  cout << "The second polynomial is : \n";
  DisplayVector(b);
  cout << "The result of polynomial multiplication is : \n";
  vector<int> c = NTTMultiply(a, b, pr, p);
  DisplayVector(c);
  cout << "--------------------------------\n";
  vector<int> ValidC = NaivePolynomialMult(a, b);
  for (size_t i = 0; i < ValidC.size(); i++) {
    if (c[i] != ValidC[i]) {
      cout << "Error in NTT multiplication at index " << i << ": expected " << ValidC[i] << ", got " << c[i] << "\n";
      cout << "The result of naive polynomial multiplication is : \n";
      DisplayVector(ValidC);
      return 1;
    }
  }
  TestNTT(n, p, pr);

  return 0;
}
