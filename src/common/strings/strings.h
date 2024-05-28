#ifndef __strings_h__
#define __strings_h__

int    strcasecmp   (const char *s1, const char *s2);
int    strncasecmp  (const char *s1, const char *s2, size_t n);
char*  strdup       (const char* str);
size_t strspn       (const char *str, const char *group);
size_t strcspn      ( const char * str1, const char * str2 );

#endif

