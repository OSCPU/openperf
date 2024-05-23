#include <am.h>
#include <klib-macros.h>
#include <klib.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

static inline int isdigit(int ch) { return (ch >= '0') && (ch <= '9'); }

static size_t strnlen(const char *s, size_t count)
{
  const char *sc;
  for (sc = s; *sc != '\0' && count--; ++sc);
  return sc - s;
}

static int skip_atoi(const char **s) {
  int i = 0;

  while (isdigit(**s))
    i = i * 10 + *((*s)++) - '0';
  return i;
}

#define ZEROPAD 1  /* pad with zero */
#define SIGN 2     /* unsigned/signed long */
#define PLUS 4     /* show plus */
#define SPACE 8    /* space if plus */
#define LEFT 16    /* left justified */
#define SMALL 32   /* Must be 32 == 0x20 */
#define SPECIAL 64 /* 0x */

#define __do_div(n, base)                                                      \
  ({                                                                           \
    int __res;                                                                 \
    __res = ((unsigned long)n) % (unsigned)base;                               \
    n = ((unsigned long)n) / (unsigned)base;                                   \
    __res;                                                                     \
  })

static char *number(char *str, long num, int base, int size, int precision,
                    int type) {
  /* we are called with base 8, 10 or 16, only, thus don't need "G..."  */
  static const char digits[16] =
      "0123456789ABCDEF"; /* "GHIJKLMNOPQRSTUVWXYZ"; */

  char tmp[66];
  char c, sign, locase;
  int i;

  /* locase = 0 or 0x20. ORing digits or letters with 'locase'
   * produces same digits or (maybe lowercased) letters */
  locase = (type & SMALL);
  if (type & LEFT)
    type &= ~ZEROPAD;
  if (base < 2 || base > 16)
    return NULL;
  c = (type & ZEROPAD) ? '0' : ' ';
  sign = 0;
  if (type & SIGN) {
    if (num < 0) {
      sign = '-';
      num = -num;
      size--;
    } else if (type & PLUS) {
      sign = '+';
      size--;
    } else if (type & SPACE) {
      sign = ' ';
      size--;
    }
  }
  if (type & SPECIAL) {
    if (base == 16)
      size -= 2;
    else if (base == 8)
      size--;
  }
  i = 0;
  if (num == 0)
    tmp[i++] = '0';
  else
    while (num != 0)
      tmp[i++] = (digits[__do_div(num, base)] | locase);
  if (i > precision)
    precision = i;
  size -= precision;
  if (!(type & (ZEROPAD + LEFT)))
    while (size-- > 0)
      *str++ = ' ';
  if (sign)
    *str++ = sign;
  if (type & SPECIAL) {
    if (base == 8)
      *str++ = '0';
    else if (base == 16) {
      *str++ = '0';
      *str++ = ('X' | locase);
    }
  }
  if (!(type & LEFT))
    while (size-- > 0)
      *str++ = c;
  while (i < precision--)
    *str++ = '0';
  while (i-- > 0)
    *str++ = tmp[i];
  while (size-- > 0)
    *str++ = ' ';
  return str;
}

#define SZ_NUM_BUF    32
static char sprint_fe[SZ_NUM_BUF+1];

static int ilog10(double n) /* 在整数输出中计算 log10(n) */
{
  int rv = 0;

  while (n >= 10) { /* 右移小数位 */
    if (n >= 100000) {
      n /= 100000;
      rv += 5;
    } else {
      n /= 10;
      rv++;
    }
  }
  while (n < 1) { /* 左移小数位 */
    if (n < 0.00001) {
      n *= 100000;
      rv -= 5;
    } else {
      n *= 10;
      rv--;
    }
  }
  return rv;
}
// 整数位数
static double i10x(int n) /* 计算 10^n 的整数输入 */
{
  double rv = 1;

  while (n > 0) {
    if (n >= 5) {
      rv *= 100000;
      n -= 5;
    } else {
      rv *= 10;
      n--;
    }
  }
  while (n < 0) { /* Right shift */
    if (n <= -5) {
      rv /= 100000;
      n += 5;
    } else {
      rv /= 10;
      n++;
    }
  }
  return rv;
}
// 浮点数据转字符串%f,%e,%E
// char* buf,       字符串缓存
// double val,      浮点数
// int prec,        小数位数
// char fmt         类型标识
static void ftoa(char *buf, double val, int prec, char fmt) {
  int d;
  int e = 0, m = 0;
  char sign = 0;
  double w;
  const char *er = 0;
  const char ds = '.';
  unsigned int *pu = (unsigned int *)&val;
  // 阶码全 1，尾数不为 0，不存在的数"NaN"
  if (((pu[1] & 0x7ff00000) == 0x7ff00000) &&
      (((pu[1] & 0xfffff) != 0) || (pu[0] != 0))) {
    er = "NaN";
  } else {
    // 默认 6 位小数
    if (prec < 0)
      prec = 6;
    // 符号处理
    if (val < 0) {
      val = 0 - val;
      sign = '-';
    } else {
      sign = '+';
    }
    // 阶码全 1，尾数部分全 0，符号位为 0 表示正无穷。
    // 阶码全 1，尾数部分全 0，符号位为 1 表示负无穷。
    if (((pu[1] & 0x7fffffff) == 0x7ff00000) && (pu[0] == 0)) {
      er = "INF";
    }
    //
    else {
      // ‘f’类型
      if (fmt == 'f') {
        val += i10x(0 - prec) / 2; /*用于四舍五入，比如 1.67 保留 1 位小数为 1.7 */
        m = ilog10(val); /*整数位数*/
        if (m < 0)
          m = 0;
        if (m + prec + 3 >= SZ_NUM_BUF)
          er = "OV"; /* 最大缓存 */
      } else {       /* E 类型 x.xxxxxxe+xx*/
        if (val != 0) {
          val += i10x(ilog10(val) - prec) /
                 2; /* 用于四舍五入，prec 表示底数部分的小数位数*/
          e = ilog10(val); /*整数位数*/

          if (e > 99 || prec + 7 >= SZ_NUM_BUF) //指数范围，及最大缓存，
          {
            er = "OV";
          } else {
            if (e < -99)
              e = -99;
            val /= i10x(e); /* 计算底数 */
          }
        }
      }
    }
    // 有效浮点
    if (!er) {
      // 符号位
      if (sign == '-')
        *buf++ = sign;

      do {
        /* 进入小数部分时插入小数分隔符 */
        if (m == -1)
          *buf++ = ds;
        //剪掉最高的数字 d
        w = i10x(m);
        //
        d = (int)(val / w);
        val -= d * w;

        *buf++ = (char)('0' + d); /* 记录 10 进制 */

      } while (--m >= -prec);

      if (fmt != 'f') {
        *buf++ = (char)fmt;
        if (e < 0) {
          e = 0 - e;
          *buf++ = '-';
        } else {
          *buf++ = '+';
        }
        *buf++ = (char)('0' + e / 10);
        *buf++ = (char)('0' + e % 10);
      }
    }
  }
  // 特殊值
  if (er) { // 符号
    if (sign)
      *buf++ = sign;
    // 数据字符串
    do {
      *buf++ = *er++;
    } while (*er);
  }
  *buf = 0; /* 结束符 */
}

int vsprintf(char *buf, const char *fmt, va_list args) {
  int len;
  unsigned long num;
  int i, j, base;
  char *str;
  const char *s;

  int flags; /* flags to number() */

  int field_width; /* width of output field */
  int precision;   /* min. # of digits for integers; max
                      number of chars for from string */
  int qualifier;   /* 'h', 'l', or 'L' for integer fields */

  for (str = buf; *fmt; ++fmt) {
    if (*fmt != '%') {
      *str++ = *fmt;
      continue;
    }

    /* process flags */
    flags = 0;
  repeat:
    ++fmt; /* this also skips first '%' */
    switch (*fmt) {
    case '-':
      flags |= LEFT;
      goto repeat;
    case '+':
      flags |= PLUS;
      goto repeat;
    case ' ':
      flags |= SPACE;
      goto repeat;
    case '#':
      flags |= SPECIAL;
      goto repeat;
    case '0':
      flags |= ZEROPAD;
      goto repeat;
    }

    /* get field width */
    field_width = -1;
    if (isdigit(*fmt))
      field_width = skip_atoi(&fmt);
    else if (*fmt == '*') {
      ++fmt;
      /* it's the next argument */
      field_width = va_arg(args, int);
      if (field_width < 0) {
        field_width = -field_width;
        flags |= LEFT;
      }
    }

    /* get the precision */
    precision = -1;
    if (*fmt == '.') {
      ++fmt;
      if (isdigit(*fmt))
        precision = skip_atoi(&fmt);
      else if (*fmt == '*') {
        ++fmt;
        /* it's the next argument */
        precision = va_arg(args, int);
      }
      if (precision < 0)
        precision = 0;
    }

    /* get the conversion qualifier */
    qualifier = -1;
    if (*fmt == 'h' || *fmt == 'l' || *fmt == 'L') {
      qualifier = *fmt;
      ++fmt;
    }

    /* default base */
    base = 10;

    switch (*fmt) {
    case 'c':
      if (!(flags & LEFT))
        while (--field_width > 0)
          *str++ = ' ';
      *str++ = (unsigned char)va_arg(args, int);
      while (--field_width > 0)
        *str++ = ' ';
      continue;

    case 's':
      s = va_arg(args, char *);
      len = strnlen(s, precision);

      if (!(flags & LEFT))
        while (len < field_width--)
          *str++ = ' ';
      for (i = 0; i < len; ++i)
        *str++ = *s++;
      while (len < field_width--)
        *str++ = ' ';
      continue;

    case 'p':
      if (field_width == -1) {
        field_width = 2 * sizeof(void *);
        flags |= ZEROPAD;
      }
      str = number(str, (unsigned long)va_arg(args, void *), 16, field_width,
                   precision, flags);
      continue;

    case 'n':
      if (qualifier == 'l') {
        long *ip = va_arg(args, long *);
        *ip = (str - buf);
      } else {
        int *ip = va_arg(args, int *);
        *ip = (str - buf);
      }
      continue;

    case 'f': /* Floating point (decimal) */
    case 'e': /* Floating point (e) */
    case 'E': /* Floating point (E) */
      // double 数据转字符串
      ftoa(sprint_fe, va_arg(args, double), precision, *fmt); /* 浮点转字符串*/
      // 右对齐 左侧补充空格
      if (!(flags & LEFT)) {
        for (j = strnlen(sprint_fe, SZ_NUM_BUF); j < field_width; j++)
          *str++ = ' ';
      }
      // 数据主体
      i = 0;
      while (sprint_fe[i])
        *str++ = sprint_fe[i++]; /* 主体 */
      // 左对齐 右侧补充空格
      while (j++ < field_width)
        *str++ = ' ';
      continue;

    case '%':
      *str++ = '%';
      continue;

      /* integer number formats - set up the flags and "break" */
    case 'o':
      base = 8;
      break;

    case 'x':
      flags |= SMALL;
    case 'X':
      base = 16;
      break;

    case 'd':
    case 'i':
      flags |= SIGN;
    case 'u':
      break;

    default:
      *str++ = '%';
      if (*fmt)
        *str++ = *fmt;
      else
        --fmt;
      continue;
    }
    if (qualifier == 'l')
      num = va_arg(args, unsigned long);
    else if (qualifier == 'h') {
      num = (unsigned short)va_arg(args, int);
      if (flags & SIGN)
        num = (short)num;
    } else if (flags & SIGN)
      num = va_arg(args, int);
    else
      num = va_arg(args, unsigned int);
    str = number(str, num, base, field_width, precision, flags);
  }
  *str = '\0';
  return str - buf;
}

int sprintf(char *buf, const char *fmt, ...) {
  va_list args;
  int i;

  va_start(args, fmt);
  i = vsprintf(buf, fmt, args);
  va_end(args);
  return i;
}

int printf(const char *fmt, ...) {
  char printf_buf[1024];
  va_list args;
  int printed;

  va_start(args, fmt);
  printed = vsprintf(printf_buf, fmt, args);
  va_end(args);

  for (int i = 0; i < printed; i++)
    putch(printf_buf[i]);

  return printed;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
