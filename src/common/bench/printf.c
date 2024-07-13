#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

  
#define ZEROPAD    1       /* 无数据位用0填充 */
#define SIGN       2       /* 符号位 */
#define PLUS       4       /* 符号位正数显示正号 */
#define SPACE      8       /* 符号位非负数显示空格 */
#define LEFT      16       /* 左对齐 */
#define SPECIAL   32       /* 显示其他进制的前缀,比如16进制添加前缀0x */
#define LARGE     64       /* 使用大写母 */
 
#define is_digit(c) ((c) >= '0' && (c) <= '9')
//浮点字符串缓存
#define SZ_NUM_BUF    32
static char sprint_fe[SZ_NUM_BUF+1];
 
static const char *digits = "0123456789abcdefghijklmnopqrstuvwxyz";
static const char *upper_digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
// 字符串长度
static size_t strnlen(const char *s, size_t count)
{
  const char *sc;
  for (sc = s; *sc != '\0' && count--; ++sc);
  return sc - s;
}
// 字符转10进制数
static int skip_atoi(const char **s)
{
  int i = 0;
  while (is_digit(**s)) i = i*10 + *((*s)++) - '0';
  return i;
}
// 
static char *number(char *str, long num, int base, int size, int precision, int type)
{
    char c, sign, tmp[66];
    const char *dig = digits;
    int i;
    //  大写
    if (type & LARGE)  dig = upper_digits;
    // 左对齐，去掉补0
    if (type & LEFT) type &= ~ZEROPAD;
    // 
    if (base < 2 || base > 36) return 0;
    // 补0或补空格
    c = (type & ZEROPAD) ? '0' : ' ';
    /*符号位处理,符号位占用1位-STR*/
    sign = 0;
    if (type & SIGN)
    {
        if (num < 0)
        {
            sign = '-';
            num = -num;
            size--;
        }
        // 正数打印正号
        else if (type & PLUS)
        {
            sign = '+';
            size--;
        }
        // 符号位打印空格
        else if (type & SPACE)
        {
            sign = ' ';
            size--;
        }
    }
/*符号位处理-END*/
 
/*进制转换-STR*/
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
/*进制转换-END*/
 
/*数据有效位置处理*/
    if (i > precision) precision = i;
        size -= precision;
/*非左对齐且非空余位置不补0,左侧补充空格*/
    if (!(type & (ZEROPAD | LEFT))) while (size-- > 0) *str++ = ' ';
    // 输出符号位
    if (sign) *str++ = sign;
    // 输出8进制或16进制前缀
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
    /*左侧补充剩余位,如补0或者补充空格*/ 
    if (!(type & LEFT)) 
    while (size-- > 0) *str++ = c;
    /*实际数据小于有效长度,左侧补0处理*/
    while (i < precision--) *str++ = '0';
    /*复制有效字符*/ 
    while (i-- > 0) *str++ = tmp[i];
    /*左对齐,右侧补充空格*/ 
    while (size-- > 0) *str++ = ' ';
    return str;
}
// 计算浮点精度
static int ilog10(double n)    /* 在整数输出中计算log10(n) */
{
    int rv = 0;
 
    while (n >= 10)
    {    /* 右移小数位 */
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
    {        /* 左移小数位 */
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
// 整数位数
static double i10x(int n)    /* 计算10^n的整数输入 */
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
// 浮点数据转字符串%f,%e,%E
// char* buf,       字符串缓存 
// double val,      浮点数
// int prec,        小数位数
// char fmt         类型标识
static void ftoa(char* buf, double val, int prec, char fmt)                   
{
    int d;
    int e = 0, m = 0;
    char sign = 0;
    double w;
    const char *er = 0;
    const char ds = '.';
    unsigned int *pu=(unsigned int *)&val;
    // 阶码全1,尾数不为0，不存在的数"NaN"
    if(((pu[1]&0x7ff00000)==0x7ff00000)&&(((pu[1]&0xfffff)!=0)||(pu[0]!=0)))
    {
        er = "NaN";
    }
    else
    {
        // 默认6 位小数
        if (prec < 0) prec = 6;
        // 符号处理
        if (val < 0)
        {
            val = 0 - val;
            sign = '-';
        }
        else
        {
            sign = '+';
        }
        // 阶码全1,尾数部分全0，符号位为0表示正无穷。
        // 阶码全1,尾数部分全0，符号位为1表示负无穷。
        if(((pu[1]&0x7fffffff) ==0x7ff00000)&&(pu[0] == 0))
        {
            er = "INF";
        }
        //
        else
        {
            // ‘f’类型
            if (fmt == 'f')
            {
                val += i10x(0 - prec) / 2;    /*用于四舍五入,比如1.67保留1位小数为1.7 */
                m = ilog10(val);            /*整数位数*/
                if (m < 0) m = 0;
                if (m + prec + 3 >= SZ_NUM_BUF) er = "OV";    /* 最大缓存 */
            }
            else
            {    /* E类型 x.xxxxxxe+xx*/
                if (val != 0)
                {
                    val += i10x(ilog10(val) - prec) / 2;    /* 用于四舍五入,prec表示底数部分的小数位数*/
                    e = ilog10(val);                        /*整数位数*/
 
                    if (e > 99 || prec + 7 >= SZ_NUM_BUF)  //指数范围,及最大缓存,
                    {
                        er = "OV";
                    }
                    else
                    {
                        if (e < -99) e = -99;
                        val /= i10x(e);    /* 计算底数 */
                    }
                }
            }
        }
        // 有效浮点
        if (!er)
        {
            // 符号位
            if (sign == '-')
                *buf++ = sign;
 
            do
            {
                /* 进入小数部分时插入小数分隔符 */
                if (m == -1)
                    *buf++ = ds;
                //剪掉最高的数字d
                w = i10x(m);
                //
                d = (int)(val / w); val -= d * w;
 
                *buf++ = (char)('0' + d);    /* 记录10进制 */
 
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
    // 特殊值
    if (er)
    {    // 符号
        if (sign)  *buf++ = sign;
        // 数据字符串
        do
        {
            *buf++ = *er++;
        } while (*er);
    }
    *buf = 0;    /* 结束符 */
}
int my_vsprintf(char *buf, const char *fmt, va_list args)
{
    int len = 0;
    unsigned long long num = 0;
    int i = 0, j = 0, base = 0;
    char * str;
    const char *s;/*s所指向的内存单元不可改写，但是s可以改写*/
    int flags;        /* flags to number() */
    int field_width;  /* width of output field */
    int precision;    /* min. # of digits for integers; max number of chars for from string */
    int qualifier;    /* 'h', 'l', or 'L' for integer fields */
                      /* 'z' support added 23/7/1999 S.H.    */
                      /* 'z' changed to 'Z' --davidm 1/25/99 */

    for (str=buf ; *fmt ; ++fmt)
    {
        if (*fmt != '%') /*使指针指向格式控制符'%,以方便以后处理flags'*/
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
                case '-': flags |= LEFT; goto repeat;/*左对齐-left justify*/
                case '+': flags |= PLUS; goto repeat;/*p plus with ’+‘*/
                case ' ': flags |= SPACE; goto repeat;/*p with space*/
                case '#': flags |= SPECIAL; goto repeat;/*根据其后的转义字符的不同而有不同含义*/
                case '0': flags |= ZEROPAD; goto repeat;/*当有指定参数时，无数字的参数将补上0*/
            }
 
       
        field_width = -1;
        if ('0' <= *fmt && *fmt <= '9')
            field_width = skip_atoi(&fmt);
        else if (*fmt == '*')
        {
            ++fmt;/*skip '*' */
            /* it's the next argument */
            field_width = va_arg(args, int);// 下个参数变量表述位宽
            if (field_width < 0) {
                field_width = -field_width;
                flags |= LEFT;
            }
        }
        /* get the precision-----即是处理.pre 有效位 */
        precision = -1;
        if (*fmt == '.')
        {
            ++fmt;
            if ('0' <= *fmt && *fmt <= '9')
                precision = skip_atoi(&fmt);
            else if (*fmt == '*') /*如果精度域中是字符'*'，表示下一个参数指定精度。因此调用va_arg 取精度值。若此时宽度值小于0，则将字段精度值取为0。*/
            {
                ++fmt;
                /* it's the next argument */
                precision = va_arg(args, int);
            }
            if (precision < 0)
                precision = 0;
        }
        /* get the conversion qualifier 分析长度修饰符，并将其存入qualifer 变量*/
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
        /*处理type部分*/
        switch (*fmt)
        {
            case 'c':
                /*非左对齐,左侧填充空格-Satrt*/
                if (!(flags & LEFT))
                   while (--field_width > 0)
                   *str++ = ' ';
                /*非左对齐,左侧填充空格-End*/
                *str++ = (unsigned char) va_arg(args, int);
                /*左对齐,右侧填充空格-Satrt*/
                while (--field_width > 0)
                *str++ = ' ';
                /*左对齐,右侧填充空格-End*/    
                //continue在此处是跳出本次for循环
                continue;
            case 's':
                s = va_arg(args, char *);
                if (!s)
                    s = "";
                len = strnlen(s, precision);/*取字符串的长度，最大为precision*/
                /*非左对齐,左侧填充空格-Satrt*/
                if (!(flags & LEFT))
                while (len < field_width--)
                    *str++ = ' ';
                    /*非左对齐,左侧填充空格-End*/
                for (i = 0; i < len; ++i)
                    *str++ = *s++;
                /*左对齐,右侧填充空格-Satrt*/
                while (len < field_width--)
                    *str++ = ' ';
                /*左对齐,右侧填充空格-End*/    
                continue;
            case 'p':
                /*没有设置宽度域，则默认宽度为指针变量长度,32位系统默认为8，且需要添0处理*/
                if (field_width == -1)
                {
                    field_width = 2*sizeof(void *);
                    flags |= ZEROPAD;
                }
                str = number(str,(unsigned long) va_arg(args, void *), 16,field_width, precision, flags);
                continue;
            // 形参作为指针变量,向指针变量所指向的地址写入当前转换的字符长度
            case 'n':
                // ln长整型地址
                if (qualifier == 'l')
                {
                    long * ip = va_arg(args, long *);
                    *ip = (str - buf);
                }
                // zn 字节地址
                else if (qualifier == 'Z')
                {
                    size_t * ip = va_arg(args, size_t *);
                    *ip = (str - buf);
                }
                // n 整形地址
                else
                {
                    int * ip = va_arg(args, int *);
                    *ip = (str - buf);
                }
                continue;
            // %f %e %E %lf均使用double类型
            case 'f':                    /* Floating point (decimal) */
            case 'e':                    /* Floating point (e) */
            case 'E':                    /* Floating point (E) */
                // double数据转字符串
                ftoa(sprint_fe, va_arg(args, double), precision, *fmt);    /* 浮点转字符串*/
                // 右对齐 左侧补充空格
                if (!(flags&LEFT))
                {
                    for (j = strnlen(sprint_fe, SZ_NUM_BUF); j<field_width; j++)
                    *str++= ' ';
                }
                // 数据主体
                i = 0;
                while(sprint_fe[i]) *str++ = sprint_fe[i++];    /* 主体 */
                // 左对齐 右侧补充空格
                while (j++ < field_width) *str++ = ' ';
   
                continue;
            // %%表示%
            case '%':
                *str++ = '%';
                continue;
            /* 设置进制*/
            case 'o':
                base = 8;
                break;
                /*大写*/
            case 'X':
                flags |= LARGE;
            case 'x':
                base = 16;
                break;
            /*有符号类型*/
            case 'd':
            case 'i':
                flags |= SIGN;
            /*无符号类型*/
            case 'u':
                break;
            default:
                /*非参数打印*/
                *str++ = '%';
                if (*fmt)
                *str++ = *fmt;
                else
                --fmt;
                continue;
        }
        /*同时如果flags有符号位的话，将参数转变成有符号的数*/
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
    *str = '\0';/*最后在转换好的字符串上加上NULL*/
    return str-buf;/*返回转换好的字符串的长度值*/
}

int my_sprintf( char *s, const char *fmt, ... )
{
    va_list arg;
    va_start( arg, fmt );
    int length = my_vsprintf( s, fmt, arg );
    va_end( arg );
    return length;
}

//int my_printf(const char *fmt, ... )
//{
//    char s[512];
//    va_list arg;
//    va_start( arg, fmt );
//    int length = my_vsprintf( s, fmt, arg );
//    va_end( arg );
//    for(int i = 0; s[i] != '\0'; i++)
//    {
//        putch(s[i]);
//    }
//    return length;
//}

int my_printf(const char *fmt, ...) {
  return 0;

}
