#include <bench.h>
#include <luaconf.h>
#include <setjmp.h>
#include <stdio.h>
#include <time.h>

LUA_NUMBER floor(LUA_NUMBER x) {
  return x;
}
LUA_NUMBER pow(LUA_NUMBER x, LUA_NUMBER y) {
  assert(0);
}
LUA_NUMBER fmod(LUA_NUMBER x, LUA_NUMBER y) {
  assert(0);
}
LUA_NUMBER frexp(LUA_NUMBER x, int *exp) {
  assert(0);
}
LUA_NUMBER tan(LUA_NUMBER x) {
  assert(0);
}
LUA_NUMBER sqrt(LUA_NUMBER x) {
  assert(0);
}
LUA_NUMBER sin(LUA_NUMBER x) {
  assert(0);
}
LUA_NUMBER log2(LUA_NUMBER x) {
  assert(0);
}
LUA_NUMBER log10(LUA_NUMBER x) {
  assert(0);
}
LUA_NUMBER log(LUA_NUMBER x) {
  assert(0);
}
LUA_NUMBER exp(LUA_NUMBER x) {
  assert(0);
}
LUA_NUMBER cos(LUA_NUMBER x) {
  assert(0);
}
LUA_NUMBER atan2(LUA_NUMBER y, LUA_NUMBER x) {
  assert(0);
}
LUA_NUMBER asin(LUA_NUMBER x) {
  assert(0);
}
LUA_NUMBER acos(LUA_NUMBER x) {
  assert(0);
}
LUA_NUMBER ceil(LUA_NUMBER x) {
  return x;
}
LUA_NUMBER fabs(LUA_NUMBER x) {
  assert(0);
}
LUA_NUMBER ldexp(LUA_NUMBER x, int exp) {
  assert(0);
}
LUA_NUMBER nan(const char *tagp) {
  assert(0);
}
//float nanf(const char *tagp) { assert(0); }

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

int strcoll(const char *s1, const char *s2) {
  return strcmp(s1, s2);
}

FILE *tmpfile() {
  assert(0);
}

size_t strspn(const char *, const char *) {
  return 0;
}

int ungetc(int c, FILE *fp) {
  assert(0);
}

int setvbuf(FILE *fp, char *buf, int mode, size_t size) {
  assert(0);
}

typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler) {
  return NULL;
}

char *fgets(char *s, int size, FILE *fp) {
  return NULL;
}

void *memchr(const void *s, int c, size_t n) {
  uint8_t *t = (uint8_t *)s;
  for (size_t i = 0; i < n; i++) {
    if (((const uint8_t *)t)[i] == (uint8_t)c) {
      return &t[i];
    }
  }
  return NULL;
}

void longjmp(jmp_buf env, int val) {
  assert(0);
}

int setjmp(jmp_buf env) {
  return 0;
}

void abort() {
  assert(0);
}

FILE *fopen64(const char *pathname, const char *mode) {
  return fopen(pathname, mode);
}

FILE *freopen(const char *pathname, const char *mode, FILE *fp) {
  assert(0);
}

FILE *freopen64(const char *pathname, const char *mode, FILE *fp) {
  assert(0);
}

char *strstr(const char *haystack, const char *needle) {
  return NULL;
}

char *setlocale(int category, const char *locale) {
  return "";
}

int rename(const char *oldpath, const char *newpath) {
  assert(0);
}

int remove(const char *pathname) {
  assert(0);
}

int system(const char *command) {
  assert(0);
}

clock_t clock() {
  assert(0);
}

char *tmpnam(char s[L_tmpnam]) {
  assert(0);
}

time_t mktime(struct tm *tm) {
  assert(0);
}

time_t time(time_t *tloc) {
  return 0;
}

struct tm *localtime(const time_t *timep) {
  assert(0);
}

size_t strftime(char *s, size_t max, const char *format, const struct tm *tm) {
  assert(0);
}

struct tm *gmtime(const time_t *timep) {
  assert(0);
}
