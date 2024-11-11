#include "trap.h"

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef uint32_t size_t;
#define NULL 0
#define LENGTH(x) sizeof(x) / sizeof(x[0])

void *memset(void *s, int c, size_t n) {
  char *p = NULL;
  if (s == NULL)
    return s;

  p = (char *)s;
  while (n > 0) {
    *(p++) = c;
    n--;
  }
  return s;
}

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }
int div_safe(int a, int b) { return b != 0 ? a / b : 0; }

int test_data[] = {0, 1, 2, 3, 0x7fffffff, 0x80000000, 0x80000001, 0xffffffff};
int ans_data[1000] = {0};

#define NR_DATA 1000

int add_main() {
  int i, j;
  for (i = 0; i < NR_DATA; i++) {
    for (j = 0; j < NR_DATA; j++) {
      int expected = add(test_data[i % 8], test_data[j % 8]);
      check(add(test_data[i % 8], test_data[j % 8]) == expected);
    }
  }
  return 0;
}

int sub_main() {
  int i, j;
  for (i = 0; i < NR_DATA; i++) {
    for (j = 0; j < NR_DATA; j++) {
      int expected = sub(test_data[i % 8], test_data[j % 8]);
      check(sub(test_data[i % 8], test_data[j % 8]) == expected);
    }
  }
  return 0;
}

int mul_main() {
  int i, j;
  for (i = 0; i < NR_DATA; i++) {
    for (j = 0; j < NR_DATA; j++) {
      int expected = mul(test_data[i % 8], test_data[j % 8]);
      check(mul(test_data[i % 8], test_data[j % 8]) == expected);
    }
  }
  return 0;
}

int div_main() {
  int i, j;
  for (i = 0; i < NR_DATA; i++) {
    for (j = 0; j < NR_DATA; j++) {
      int expected = div_safe(test_data[i % 8], test_data[(j % 7) + 1]);
      check(div_safe(test_data[i % 8], test_data[(j % 7) + 1]) == expected);
    }
  }
  return 0;
}

int main() {
  memset(ans_data, 0, sizeof(ans_data));

  for (int k = 0; k < 10; k++) {
    add_main();
    sub_main();
    mul_main();
    div_main();
  }
  return 0;
}

