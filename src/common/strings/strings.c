#include <klib.h>
#include <my_malloc.h>


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
  char* ret = (char*)my_malloc(len + 1);

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



