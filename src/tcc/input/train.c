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

// ***************************************
// *************************************** //
int add(int a, int b) {
  int c = a + b;
  return c;
}

int add_test_data[] = {0,          1,          2,          0x7fffffff,
                       0x80000000, 0x80000001, 0xfffffffe, 0xffffffff};
int add_ans[] = {
    0,          0x1, 0x2,        0x7fffffff, 0x80000000, 0x80000001, 0xfffffffe,
    0xffffffff, 0x1, 0x2,        0x3,        0x80000000, 0x80000001, 0x80000002,
    0xffffffff, 0,   0x2,        0x3,        0x4,        0x80000001, 0x80000002,
    0x80000003, 0,   0x1,        0x7fffffff, 0x80000000, 0x80000001, 0xfffffffe,
    0xffffffff, 0,   0x7ffffffd, 0x7ffffffe, 0x80000000, 0x80000001, 0x80000002,
    0xffffffff, 0,   0x1,        0x7ffffffe, 0x7fffffff, 0x80000001, 0x80000002,
    0x80000003, 0,   0x1,        0x2,        0x7fffffff, 0x80000000, 0xfffffffe,
    0xffffffff, 0,   0x7ffffffd, 0x7ffffffe, 0x7fffffff, 0xfffffffc, 0xfffffffd,
    0xffffffff, 0,   0x1,        0x7ffffffe, 0x7fffffff, 0x80000000, 0xfffffffd,
    0xfffffffe};

#define add_NR_DATA 8

int add_main() {
  int i, j, ans_idx = 0;
  for (i = 0; i < add_NR_DATA; i++) {
    for (j = 0; j < add_NR_DATA; j++) {
      check(add(add_test_data[i], add_test_data[j]) == add_ans[ans_idx++]);
    }
    check(j == add_NR_DATA);
  }

  check(i == add_NR_DATA);

  return 0;
}

int main() {
  add_main();
  return 0;
}
