#include <stdint.h>
// #include <assert.h>
// #include <stdio.h>
#include <stdarg.h>
#include <klib.h>

uint64_t __make_mantissa_base8(const char *__tagp) {
  uint64_t __r = 0;
  while (*__tagp != '\0') {
    char __tmp = *__tagp;

    if (__tmp >= '0' && __tmp <= '7')
      __r = (__r * 8u) + __tmp - '0';
    else
      return 0;

    ++__tagp;
  }

  return __r;
}

uint64_t __make_mantissa_base10(const char *__tagp) {
  uint64_t __r = 0;
  while (*__tagp != '\0') {
    char __tmp = *__tagp;

    if (__tmp >= '0' && __tmp <= '9')
      __r = (__r * 10u) + __tmp - '0';
    else
      return 0;

    ++__tagp;
  }

  return __r;
}

uint64_t __make_mantissa_base16(const char *__tagp) {
  uint64_t __r = 0;
  while (*__tagp != '\0') {
    char __tmp = *__tagp;

    if (__tmp >= '0' && __tmp <= '9')
      __r = (__r * 16u) + __tmp - '0';
    else if (__tmp >= 'a' && __tmp <= 'f')
      __r = (__r * 16u) + __tmp - 'a' + 10;
    else if (__tmp >= 'A' && __tmp <= 'F')
      __r = (__r * 16u) + __tmp - 'A' + 10;
    else
      return 0;

    ++__tagp;
  }

  return __r;
}

uint64_t __make_mantissa(const char *__tagp) {
  if (*__tagp == '0') {
    ++__tagp;

    if (*__tagp == 'x' || *__tagp == 'X')
      return __make_mantissa_base16(__tagp);
    else
      return __make_mantissa_base8(__tagp);
  }

  return __make_mantissa_base10(__tagp);
}

double nan(const char *__tagp) {
  union {
    double val;
    struct ieee_double {
      uint64_t mantissa : 51;
      uint32_t quiet : 1;
      uint32_t exponent : 11;
      uint32_t sign : 1;
    } bits;
  } __tmp;
  assert(sizeof(__tmp.val) == sizeof(__tmp.bits));

  __tmp.bits.sign = 0u;
  __tmp.bits.exponent = 2047u;//~0u;
  __tmp.bits.quiet = 1u;
  __tmp.bits.mantissa = __make_mantissa(__tagp);

  return __tmp.val;

}


