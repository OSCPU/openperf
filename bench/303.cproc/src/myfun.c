#include <bench.h>
#include <stdio.h>

static unsigned char char_buf;
static int char_buf_valid = 0;

int my_getc(FILE *fp) {
  if (char_buf_valid) {
    char_buf_valid = 0;
    return char_buf;
  }
  return getc(fp);
}

int my_ungetc(int c, FILE *fp) {
  assert(!char_buf_valid);
  char_buf_valid = 1;
  char_buf = c;
  return c;
}

int __ucmpdi2(unsigned long long a, unsigned long long b) {
  if (a < b)
    return 0;
  else if (a > b)
    return 2;
  else
    return 1;
}

char *strpbrk(const char *s, const char *accept) {
  for (; *s != '\0'; s++) {
    for (const char *p = accept; *p != '\0'; p++) {
      if (*s == *p) {
        return (char *)s;
      }
    }
  }
  return NULL;
}
