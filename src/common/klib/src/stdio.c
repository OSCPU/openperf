#include <am.h>
#include <klib-macros.h>
#include <klib.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {
  va_list vl;
  va_start(vl, fmt);
  int j = 0;
  char c;
  int d;
  char *s;
  while (fmt[j] != '\0') {
    char src_char = fmt[j];
    if (src_char != '%') {
      putch(fmt[j]);
      j++;
      continue;
    }

    bool find_type = false;
    while (!find_type) {
      switch (fmt[j + 1]) {
      case 's':
        s = va_arg(vl, char *);
        while (*s != '\0') {
          putch(*s);
          s++;
        }
        find_type = true;
        break;
      case 'd':
        d = va_arg(vl, int);
        char sd[256];
        sprintf(sd, "%d", d);
        int i = 0;
        while (sd[i] != '\0') {
          putch(sd[i]);
          i++;
        }
        find_type = true;
        break;
      case 'u':
        d = va_arg(vl, int);
        sprintf(sd, "%d", d);
        i = 0;
        while (sd[i] != '\0') {
          putch(sd[i]);
          i++;
        }
        find_type = true;
        break;
      case 'x':
        d = va_arg(vl, int);
        sprintf(sd, "%d", d);
        i = 0;
        while (sd[i] != '\0') {
          putch(sd[i]);
          i++;
        }
        find_type = true;
        break;
      case 'c':
        c = va_arg(vl, int);
        putch(c);
        find_type = true;
        break;
      default:
        j++;
        continue;
      }
    }

    j += 2;
  }

  return 0;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  panic("Not implemented");
}

int sprintf(char *out, const char *fmt, ...) {
  va_list vl;
  va_start(vl, fmt);
  int i = 0;
  int j = 0;
  while (fmt[j] != '\0') {
    char src_char = fmt[j];
    if (src_char != '%') {
      out[i] = src_char;
      i++;
      j++;

      continue;
    }
    switch (fmt[j + 1]) {
    case 'd': {
      int src_arg_num = va_arg(vl, int);
      if (src_arg_num < 0) {
        out[i] = '-';
        src_arg_num = -src_arg_num;
        i++;
      }

      char tmp_buffer[32] = "";
      int tmp_i = 0;
      tmp_buffer[tmp_i] = src_arg_num % 10 + '0';
      while (src_arg_num > 9) {
        tmp_i++;
        src_arg_num /= 10;
        tmp_buffer[tmp_i] = src_arg_num % 10 + '0';
      }

      out[i] = tmp_buffer[tmp_i];
      i++;
      while (tmp_i > 0) {
        tmp_i--;
        out[i] = tmp_buffer[tmp_i];
        i++;
      }

      j += 2;
      break;
    }
    case 's': {
      out[i] = '\0';
      strcat(out, va_arg(vl, char *));
      while (out[i] != '\0') {
        i++;
      }
      j += 2;
      break;
    }
    default: {
      out[i] = src_char;
      i++;
      j++;
    } break;
    }
  }
  out[i] = '\0';
  va_end(vl);
  return *out;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
