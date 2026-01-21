#include <bench.h>
#include <stdarg.h>
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

static Obuf obuf;

void obuf_init() {
  bench_obuf_init(&obuf, 4096);
}

#define MAX_DISPLAY (8 * 1024 * 1024)

void obuf_display() {
  int l = obuf.len > MAX_DISPLAY ? MAX_DISPLAY : obuf.len;
  fwrite(obuf.p, l, 1, stdout);
  printf("\n");
  if (obuf.len > MAX_DISPLAY) {
    printf("Warning: Output is truncated to %d bytes\n", MAX_DISPLAY);
  }
}

uint32_t obuf_checksum() {
  return bench_checksum(obuf.p, obuf.p + obuf.len);
}

void obuf_exit() {
  free(obuf.p);
}

int my_putchar(int c) {
  bench_obuf_append(&obuf, &c, 1);
  return (unsigned char)c;
}

int my_fputc(int c, FILE *fp) {
  assert(fp == stdout);
  return my_putchar(c);
}

int my_fputs(const char *s, FILE *fp) {
  assert(fp == stdout);
  bench_obuf_append(&obuf, s, strlen(s));
  return 0;
}

int my_puts(const char *s) {
  my_fputs(s, stdout);
  my_putchar('\n');
  return 0;
}

int my_printf(const char *fmt, ...) {
  char buf[256];
  va_list ap;
  va_start(ap, fmt);
  int ret = vsnprintf(buf, 256, fmt, ap);
  assert(ret < 256);
  va_end(ap);
  my_fputs(buf, stdout);
  return ret;
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
