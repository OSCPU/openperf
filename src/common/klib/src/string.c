#include <klib-macros.h>
#include <klib.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  int i = 0;
  while (s[i] != '\0') {
    i++;
  }

  return i;
}

char *strcpy(char *dst, const char *src) {
  int i = 0;
  while (src[i] != '\0') {
    dst[i] = src[i];
    i++;
  }

  dst[i] = '\0';

  return dst;
}

char *strncpy(char *dst, const char *src, size_t n) {
  panic("Not implemented");
}

char *strcat(char *dst, const char *src) {
  int i = 0;
  int j = 0;
  while (dst[i] != '\0') {
    i++;
  }

  while (src[j] != '\0') {
    dst[i] = src[j];
    i++;
    j++;
  }

  dst[i] = '\0';

  return dst;
}

int strcmp(const char *s1, const char *s2) {
  int i = 0;
  int result = 0;

  while (true) {
    if (s1[i] == s2[i]) {
      i++;

      if (s1[i] == '\0' && s2[i] == '\0') {
        break;
      }
      continue;
    } else if (s1[i] < s2[i]) {
      result = -1;
      break;
    } else {
      result = 1;
      break;
    }
  }

  return result;
}

int strncmp(const char *s1, const char *s2, size_t n) {
  int i = 0;
  int result = 0;

  while (i < n) {
    if (s1[i] == s2[i]) {
      i++;

      if (s1[i] == '\0' && s2[i] == '\0') {
        break;
      }
      continue;
    } else if (s1[i] < s2[i]) {
      result = -1;
      break;
    } else {
      result = 1;
      break;
    }
  }

  return result;
}

void *memset(void *s, int c, size_t n) {
  char *dst = s;
  int i = 0;
  while (i < n) {
    dst[i] = c;
    i++;
  }

  return s;
}

void *memmove(void *dst, const void *src, size_t n) {
  uintptr_t offset = 0;
  while (dst + offset != src && offset < n) {
    ((char *)dst)[offset] = ((char *)src)[offset];
    offset++;
  }

  return dst;
}

void *memcpy(void *out, const void *in, size_t n) {
  uintptr_t offset = 0;
  while (offset < n) {
    ((char *)out)[offset] = ((char *)in)[offset];
    offset++;
  }

  return out;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  int i = 0;
  int result = 0;
  const char *s1_char = s1;
  const char *s2_char = s2;

  while (i < n) {
    if (s1_char[i] == s2_char[i]) {
      i++;
      continue;
    } else if (s1_char[i] < s2_char[i]) {
      result = -1;
      break;
    } else {
      result = 1;
      break;
    }
  }

  return result;
}

#endif
