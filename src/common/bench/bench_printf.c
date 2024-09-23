#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

  
#define ZEROPAD    1
#define SIGN       2
#define PLUS       4
#define SPACE      8
#define LEFT      16
#define SPECIAL   32
#define LARGE     64
 
#define is_digit(c) ((c) >= '0' && (c) <= '9')

#define SZ_NUM_BUF    32
static char sprint_fe[SZ_NUM_BUF+1];
#define PRINT_BUF_SIZE 512
 
static const char *digits = "0123456789abcdefghijklmnopqrstuvwxyz";
static const char *upper_digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

static size_t strnlen(const char *s, size_t count)
{
  const char *sc;
  for (sc = s; *sc != '\0' && count--; ++sc);
  return sc - s;
}

static int skip_atoi(const char **s)
{
  int i = 0;
  while (is_digit(**s)) i = i*10 + *((*s)++) - '0';
  return i;
}

static char *number(char *str, long num, int base, int size, int precision, int type)
{
    char c, sign, tmp[66];
    const char *dig = digits;
    int i;
    if (type & LARGE)  dig = upper_digits;
    if (type & LEFT) type &= ~ZEROPAD;
    if (base < 2 || base > 36) return 0;
    c = (type & ZEROPAD) ? '0' : ' ';
    sign = 0;
    if (type & SIGN)
    {
        if (num < 0)
        {
            sign = '-';
            num = -num;
            size--;
        }
        else if (type & PLUS)
        {
            sign = '+';
            size--;
        }
        else if (type & SPACE)
        {
            sign = ' ';
            size--;
        }
    }
 
    if (type & SPECIAL)
    {
        if (base == 16)
            size -= 2;
        else if (base == 8)
            size--;
    }
    i = 0;
    if (num == 0)
      tmp[i++] = '0';
    else
    {
        while (num != 0)
        {
            tmp[i++] = dig[((unsigned long) num) % (unsigned) base];
            num = ((unsigned long) num) / (unsigned) base;
        }
    }
 
    if (i > precision) precision = i;
        size -= precision;
    if (!(type & (ZEROPAD | LEFT))) while (size-- > 0) *str++ = ' ';
    if (sign) *str++ = sign;
    if (type & SPECIAL)
    {
      if (base == 8)
        *str++ = '0';//0
      else if (base == 16)
      {
        *str++ = '0';
        *str++ = digits[33];//0x
      }
    }
    if (!(type & LEFT)) 
    while (size-- > 0) *str++ = c;
    while (i < precision--) *str++ = '0';
    while (i-- > 0) *str++ = tmp[i];
    while (size-- > 0) *str++ = ' ';
    return str;
}
static int ilog10(double n)
{
    int rv = 0;
 
    while (n >= 10)
    {    
        if (n >= 100000)
        {
            n /= 100000; rv += 5;
        }
        else
        {
            n /= 10; rv++;
        }
    }
    while (n < 1)
    {
        if (n < 0.00001)
        {
            n *= 100000; rv -= 5;
        }
        else
        {
            n *= 10; rv--;
        }
    }
    return rv;
}

static double i10x(int n)
{
    double rv = 1;
 
    while (n > 0)
    {
        if (n >= 5)
        {
            rv *= 100000; n -= 5;
        }
        else
        {
            rv *= 10; n--;
        }
    }
    while (n < 0)
    {        /* Right shift */
        if (n <= -5)
        {
            rv /= 100000; n += 5;
        }
        else
        {
            rv /= 10; n++;
        }
    }
    return rv;
}

static void ftoa(char* buf, double val, int prec, char fmt)
{
    int d;
    int e = 0, m = 0;
    char sign = 0;
    double w;
    const char *er = 0;
    const char ds = '.';
    unsigned int *pu=(unsigned int *)&val;

    if(((pu[1]&0x7ff00000)==0x7ff00000)&&(((pu[1]&0xfffff)!=0)||(pu[0]!=0)))
    {
        er = "NaN";
    }
    else
    {
        if (prec < 0) prec = 6;
        if (val < 0)
        {
            val = 0 - val;
            sign = '-';
        }
        else
        {
            sign = '+';
        }
        if(((pu[1]&0x7fffffff) ==0x7ff00000)&&(pu[0] == 0))
        {
            er = "INF";
        }
        else
        {
            if (fmt == 'f')
            {
                val += i10x(0 - prec) / 2;
                m = ilog10(val);
                if (m < 0) m = 0;
                if (m + prec + 3 >= SZ_NUM_BUF) er = "OV";
            }
            else
            {
                if (val != 0)
                {
                    val += i10x(ilog10(val) - prec) / 2;
                    e = ilog10(val);
 
                    if (e > 99 || prec + 7 >= SZ_NUM_BUF)
                    {
                        er = "OV";
                    }
                    else
                    {
                        if (e < -99) e = -99;
                        val /= i10x(e);
                    }
                }
            }
        }
        if (!er)
        {
            if (sign == '-')
                *buf++ = sign;
 
            do
            {
                if (m == -1)
                    *buf++ = ds;
                w = i10x(m);
                d = (int)(val / w); val -= d * w;
 
                *buf++ = (char)('0' + d);
 
            } while (--m >= -prec);
 
            if (fmt != 'f')
            {
                *buf++ = (char)fmt;
                if (e < 0) {
                    e = 0 - e; *buf++ = '-';
                }
                else {
                    *buf++ = '+';
                }
                *buf++ = (char)('0' + e / 10);
                *buf++ = (char)('0' + e % 10);
            }
        }
    }
    if (er)
    {    
        if (sign)  *buf++ = sign;
        do
        {
            *buf++ = *er++;
        } while (*er);
    }
    *buf = 0;
}
int bench_vsprintf(char *buf, const char *fmt, va_list args)
{
    int len = 0;
    unsigned long long num = 0;
    int i = 0, j = 0, base = 0;
    char * str;
    const char *s;
    int flags;        /* flags to number() */
    int field_width;  /* width of output field */
    int precision;    /* min. # of digits for integers; max number of chars for from string */
    int qualifier;    /* 'h', 'l', or 'L' for integer fields */
                      /* 'z' support added 23/7/1999 S.H.    */
                      /* 'z' changed to 'Z' --davidm 1/25/99 */

    for (str=buf ; *fmt ; ++fmt)
    {
        if (*fmt != '%')
        {
            *str++ = *fmt;
            continue;
        }
        /* flags */
        flags = 0;
        repeat:
            ++fmt;    
            switch (*fmt)
            {
                case '-': flags |= LEFT; goto repeat;
                case '+': flags |= PLUS; goto repeat;
                case ' ': flags |= SPACE; goto repeat;
                case '#': flags |= SPECIAL; goto repeat;
                case '0': flags |= ZEROPAD; goto repeat;
            }
 
       
        field_width = -1;
        if ('0' <= *fmt && *fmt <= '9')
            field_width = skip_atoi(&fmt);
        else if (*fmt == '*')
        {
            ++fmt;/*skip '*' */
            /* it's the next argument */
            field_width = va_arg(args, int);
            if (field_width < 0) {
                field_width = -field_width;
                flags |= LEFT;
            }
        }
        precision = -1;
        if (*fmt == '.')
        {
            ++fmt;
            if ('0' <= *fmt && *fmt <= '9')
                precision = skip_atoi(&fmt);
            else if (*fmt == '*') 
            {
                ++fmt;
                /* it's the next argument */
                precision = va_arg(args, int);
            }
            if (precision < 0)
                precision = 0;
        }
        qualifier = -1;
        if (*fmt == 'l' && *(fmt + 1) == 'l')
        {
            qualifier = 'q';
            fmt += 2;
        }
        else if (*fmt == 'h' || *fmt == 'l' || *fmt == 'L'|| *fmt == 'Z')
        {
            qualifier = *fmt;
            ++fmt;
        }
        /* default base */
        base = 10;
        switch (*fmt)
        {
            case 'c':
                if (!(flags & LEFT))
                   while (--field_width > 0)
                   *str++ = ' ';
                *str++ = (unsigned char) va_arg(args, int);
                while (--field_width > 0)
                *str++ = ' ';
                continue;
            case 's':
                s = va_arg(args, char *);
                if (!s)
                    s = "";
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
                if (field_width == -1)
                {
                    field_width = 2*sizeof(void *);
                    flags |= ZEROPAD;
                }
                str = number(str,(unsigned long) va_arg(args, void *), 16,field_width, precision, flags);
                continue;
            case 'n':
                if (qualifier == 'l')
                {
                    long * ip = va_arg(args, long *);
                    *ip = (str - buf);
                }
                else if (qualifier == 'Z')
                {
                    size_t * ip = va_arg(args, size_t *);
                    *ip = (str - buf);
                }
                else
                {
                    int * ip = va_arg(args, int *);
                    *ip = (str - buf);
                }
                continue;
            case 'f':                    /* Floating point (decimal) */
            case 'e':                    /* Floating point (e) */
            case 'E':                    /* Floating point (E) */
                ftoa(sprint_fe, va_arg(args, double), precision, *fmt);    /* 浮点转字符串*/
                if (!(flags&LEFT))
                {
                    for (j = strnlen(sprint_fe, SZ_NUM_BUF); j<field_width; j++)
                    *str++= ' ';
                }
                i = 0;
                while(sprint_fe[i]) *str++ = sprint_fe[i++];    /* 主体 */
                while (j++ < field_width) *str++ = ' ';
   
                continue;
            case '%':
                *str++ = '%';
                continue;
            case 'o':
                base = 8;
                break;
            case 'X':
                flags |= LARGE;
            case 'x':
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
        {
            num = va_arg(args, unsigned long);
            if (flags & SIGN)
                num = (signed long) num;
        }
        else if (qualifier == 'q')
        {
            num = va_arg(args, unsigned long long);
            if (flags & SIGN)
                num = (signed long long) num;
        }
        else if (qualifier == 'Z')
        {
            num = va_arg(args, size_t);
        }
        else if (qualifier == 'h')
        {
            num = (unsigned short) va_arg(args, int);
            if (flags & SIGN)
                num = (signed short) num;
        }
        else
        {
            num = va_arg(args, unsigned int);
            if (flags & SIGN)
                num = (signed int) num;
        }
        str = number(str, num, base, field_width, precision, flags);
    }
    *str = '\0';
    return str-buf;
}

int bench_sprintf( char *s, const char *fmt, ... )
{
    va_list arg;
    va_start( arg, fmt );
    int length = bench_vsprintf( s, fmt, arg );
    va_end( arg );
    return length;
}

int bench_printf(const char *fmt, ... )
{
    char s[PRINT_BUF_SIZE];
    va_list arg;
    va_start( arg, fmt );
    int length = bench_vsprintf( s, fmt, arg );
    va_end( arg );
    for(int i = 0; s[i] != '\0'; i++)
    {
        putch(s[i]);
    }
    return length;
}
