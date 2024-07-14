#include <klib.h>
#include <bench_malloc.h>


#define __tolower(c)    ((('A' <= (c))&&((c) <= 'Z')) ? ((c) - 'A' + 'a') : (c))
int strcasecmp(const char *s1, const char *s2)
{
  if(s1 == NULL || s2 == NULL)
    return 0;

  while((*s1 != '\0') && (__tolower(*s1) == __tolower(*s2)))
  {
    s1++; s2++;
  }
  return (*s1 - *s2);
}

int strncasecmp(const char *s1, const char *s2, size_t n)
{
  if(s1 == NULL || s2 == NULL)
    return 0;

  while((*s1 != '\0') && (__tolower(*s1) == __tolower(*s2)) && (n > 1))
  {
    s1++; s2++;
    n--;
  }
  return (*s1 - *s2);
}

char* strdup(const char* str)
{
  if(str == NULL)
    return NULL;

  char* strat = (char*)str;
  int len = 0;
  while (*str++ != '\0')
    len++;
  char* ret = (char*)bench_malloc(len + 1);

  while ((*ret++ = *strat++) != '\0')
  {}

  return ret - (len + 1);
}

size_t strspn(const char *str, const char *group)
{
	const char *p = NULL;
	const char *a = NULL;
	size_t count = 0;

	for (p = str; *p != '\0'; ++p)
	{
		for (a = group; *a != '\0'; ++a)
		{
			if (*p == *a)
			{
				++count;
				break;
			}
		}

		if (*a == '\0')
		{
			return count;
		}
	}

	return count;
}

size_t strcspn ( const char * str1, const char * str2 ) {
  char *p1 = (char *)str1;
  char *p2;
  while (*p1 != '\0') {
    p2 = (char *)str2;
    while (*p2 != '\0') {
        if (*p2 == *p1) return p1-str1;
        ++p2;
    }
    ++p1;
  }
  return  p1 - str1;
}

unsigned long strtoul(const char *pstart, char **pend, int base) 
{ 
  const char *s = pstart; 
  unsigned long result = 0; 
  char c; 

  assert (base > 2 && base < 36); 

  // 去掉前导空格和+ - 符号 
  do { 
      c = *s++; 
  } while ((c == ' ')); 
  if (c == '-' || c == '+'){ 
      c = *s++;         
  } 
  //判断进制,并去除前导0x或者0 
  if ((base == 0 || base == 16) && 
      c == '0' && (*s == 'x' || *s == 'X') && 
      ((s[1] >= '0' && s[1] <= '9') || 
      (s[1] >= 'A' && s[1] <= 'F') || 
      (s[1] >= 'a' && s[1] <= 'f'))) { 
      c = s[1]; 
      s += 2; 
      base = 16; 
  } 
  if (base == 0) {
      base = c == '0' ? 8 : 10;  
  }
  for ( ; *s; c = *s++)   { 
    if (c >= '0' && c <= '9') {
      c -= '0'; 
    } else if (c >= 'A' && c <= 'Z') {
      c -= 'A' - 10; 
    } else if (c >= 'a' && c <= 'z') {
      c -= 'a' - 10; 
    } else {
      break; 
    }
    result *= base; 
    result += c; 
  } 
  if (pend != NULL) { 
      *pend = (char *)(s - 1); 
  }
  return result; 
}

unsigned long long strtoull(const char *pstart, char **pend, int base) 
{ 
  const char *s = pstart; 
  unsigned long long result = 0; 
  char c; 

  assert (base > 2 && base < 36); 

  // 去掉前导空格和+ - 符号 
  do { 
      c = *s++; 
  } while ((c == ' ')); 
  if (c == '-' || c == '+'){ 
      c = *s++;         
  } 
  //判断进制,并去除前导0x或者0 
  if ((base == 0 || base == 16) && 
      c == '0' && (*s == 'x' || *s == 'X') && 
      ((s[1] >= '0' && s[1] <= '9') || 
      (s[1] >= 'A' && s[1] <= 'F') || 
      (s[1] >= 'a' && s[1] <= 'f'))) { 
      c = s[1]; 
      s += 2; 
      base = 16; 
  } 
  if (base == 0) {
      base = c == '0' ? 8 : 10;  
  }
  for ( ; *s; c = *s++)   { 
    if (c >= '0' && c <= '9') {
      c -= '0'; 
    } else if (c >= 'A' && c <= 'Z') {
      c -= 'A' - 10; 
    } else if (c >= 'a' && c <= 'z') {
      c -= 'a' - 10; 
    } else {
      break; 
    }
    result *= base; 
    result += c; 
  } 
  if (pend != NULL) { 
      *pend = (char *)(s - 1); 
  }
  return result; 
}

long strtol(const char *pstart, char **pend, int base) 
{ 
  const char *s = pstart; 
  long result = 0; 
  char c; 
  long sign = 1;

  assert (base > 2 && base < 36); 

  // 去掉前导空格和+ - 符号 
  do { 
      c = *s++; 
  } while ((c == ' ')); 
  if (c == '-' || c == '+'){ 
    sign = (c == '-') ? -1: 1;
    c = *s++;         
  } 
  //判断进制,并去除前导0x或者0 
  if ((base == 0 || base == 16) && 
      c == '0' && (*s == 'x' || *s == 'X') && 
      ((s[1] >= '0' && s[1] <= '9') || 
      (s[1] >= 'A' && s[1] <= 'F') || 
      (s[1] >= 'a' && s[1] <= 'f'))) { 
      c = s[1]; 
      s += 2; 
      base = 16; 
  } 
  if (base == 0) {
      base = c == '0' ? 8 : 10;  
  }
  for ( ; *s; c = *s++)   { 
    if (c >= '0' && c <= '9') {
      c -= '0'; 
    } else if (c >= 'A' && c <= 'Z') {
      c -= 'A' - 10; 
    } else if (c >= 'a' && c <= 'z') {
      c -= 'a' - 10; 
    } else {
      break; 
    }
    result *= base; 
    result += c; 
  } 
  if (pend != NULL) { 
      *pend = (char *)(s - 1); 
  }
  return sign * result; 
}

long long strtoll(const char *pstart, char **pend, int base) 
{ 
  const char *s = pstart; 
  long long result = 0; 
  char c; 
  long long sign = 1;

  assert (base > 2 && base < 36); 

  // 去掉前导空格和+ - 符号 
  do { 
      c = *s++; 
  } while ((c == ' ')); 
  if (c == '-' || c == '+'){ 
    sign = (c == '-') ? -1: 1;
    c = *s++;         
  } 
  //判断进制,并去除前导0x或者0 
  if ((base == 0 || base == 16) && 
      c == '0' && (*s == 'x' || *s == 'X') && 
      ((s[1] >= '0' && s[1] <= '9') || 
      (s[1] >= 'A' && s[1] <= 'F') || 
      (s[1] >= 'a' && s[1] <= 'f'))) { 
      c = s[1]; 
      s += 2; 
      base = 16; 
  } 
  if (base == 0) {
      base = c == '0' ? 8 : 10;  
  }
  for ( ; *s; c = *s++)   { 
    if (c >= '0' && c <= '9') {
      c -= '0'; 
    } else if (c >= 'A' && c <= 'Z') {
      c -= 'A' - 10; 
    } else if (c >= 'a' && c <= 'z') {
      c -= 'a' - 10; 
    } else {
      break; 
    }
    result *= base; 
    result += c; 
  } 
  if (pend != NULL) { 
      *pend = (char *)(s - 1); 
  }
  return sign * result; 
}

double strtod(const char *pstart, char **pend) 
{ 
  const char *s = pstart; 
  double result = 0; 
  char c; 
  double sign = 1.0;
  double frac = 0.1;

  // 去掉前导空格和+ - 符号 
  do { 
      c = *s++; 
  } while ((c == ' ')); 
  if (c == '-' || c == '+'){ 
    sign = (c == '-') ? -1.0 : 1.0;
    c = *s++;         
  } 

  for ( ; ; c = *s++)   { 
    if (c >= '0' && c <= '9') {
      c -= '0'; 
    } else {
      break; 
    }
    result *= 10; 
    result += c; 
  } 
  if(c == '.') {
    c = *s++;
    for ( ; ; c = *s++)   { 
      if (c >= '0' && c <= '9') {
        c -= '0'; 
      } else {
        break; 
      }
      result += c * frac; 
      frac *= 0.1;
    } 
  }

  if (pend != NULL) { 
      *pend = (char *)(s - 1); 
  }
  return (sign * result); 
}

long double strtold(const char *pstart, char **pend) 
{ 
  const char *s = pstart; 
  long double result = 0; 
  char c; 
  long double sign = 1.0;
  long double frac = 0.1;

  // 去掉前导空格和+ - 符号 
  do { 
      c = *s++; 
  } while ((c == ' ')); 
  if (c == '-' || c == '+'){ 
    sign = (c == '-') ? -1.0 : 1.0;
    c = *s++;         
  } 

  for ( ; ; c = *s++)   { 
    if (c >= '0' && c <= '9') {
      c -= '0'; 
    } else {
      break; 
    }
    result *= 10; 
    result += c; 
  } 
  if(c == '.') {
    c = *s++;
    for ( ; ; c = *s++)   { 
      if (c >= '0' && c <= '9') {
        c -= '0'; 
      } else {
        break; 
      }
      result += c * frac; 
      frac *= 0.1;
    } 
  }

  if (pend != NULL) { 
      *pend = (char *)(s - 1); 
  }
  return (sign * result); 
}

float strtof(const char *pstart, char **pend) 
{ 
  const char *s = pstart; 
  float result = 0; 
  char c; 
  float sign = 1.0;
  float frac = 0.1;

  // 去掉前导空格和+ - 符号 
  do { 
      c = *s++; 
  } while ((c == ' ')); 
  if (c == '-' || c == '+'){ 
    sign = (c == '-') ? -1.0 : 1.0;
    c = *s++;         
  } 

  for ( ; ; c = *s++)   { 
    if (c >= '0' && c <= '9') {
      c -= '0'; 
    } else {
      break; 
    }
    result *= 10; 
    result += c; 
  } 
  if(c == '.') {
    c = *s++;
    for ( ; ; c = *s++)   { 
      if (c >= '0' && c <= '9') {
        c -= '0'; 
      } else {
        break; 
      }
      result += c * frac; 
      frac *= 0.1;
    } 
  }

  if (pend != NULL) { 
      *pend = (char *)(s - 1); 
  }
  return (sign * result); 
}

char *strchr(const char *s, const char ch)
{
  if (NULL == s)
    return NULL;	 
  
  const char *pSrc = s;
  while ('\0' != *pSrc)
  {
    if (*pSrc == ch)
    {
      return (char *)pSrc;
    }		   
    pSrc++;
  }	 
  if(ch == 0) 
  {
    return (char *)pSrc;
  }
  return NULL;
}

char *strrchr(const char *s, const char ch)
{
  if(s == NULL)
  {
      return NULL;
  }

  char *p_char = NULL;
  while(*s != '\0')
  {
    if(*s == ch)
    {
        p_char = (char *)s;
    }
    s++;
  }
  if(ch == 0)
  {
    p_char = (char *)s;
  }
  return p_char;
}

char* strstr(const char* dest, const char* src)
{
  assert(0);
}



