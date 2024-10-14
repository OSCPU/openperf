#ifndef __strings_h__
#define __strings_h__

#include <stddef.h>

int strcasecmp(const char *s1, const char *s2);
int strncasecmp(const char *s1, const char *s2, size_t n);
char *strdup(const char *str);
size_t strspn(const char *str, const char *group);
size_t strcspn(const char *str1, const char *str2);

unsigned long strtoul(const char *pstart, char **pend, int base);
unsigned long long strtoull(const char *pstart, char **pend, int base);
long strtol(const char *pstart, char **pend, int base);
long long strtoll(const char *pstart, char **pend, int base);
double strtod(const char *pstart, char **pend);
long double strtold(const char *pstart, char **pend);
float strtof(const char *pstart, char **pend);
char *strchr(const char *s, const char ch);
char *strstr(const char *dest, const char *src);
char *strrchr(const char *s, const char ch);

#endif
