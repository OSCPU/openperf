
/*!
 *************************************************************************************
 * \file win32.c
 *
 * \brief
 *    Platform dependent code
 *
 * \author
 *    Main contributors (see contributors.h for copyright, address and affiliation details)
 *      - Karsten Suehring                  <suehring@hhi.de>
 *************************************************************************************
 */

#if defined(SPEC_WINDOWS)
#include <time.h>
#define TIME_T time_t
#endif /* SPEC_WINDOWS */

#include "global.h"


#if defined(_WIN32) || defined(SPEC_WINDOWS)

static LARGE_INTEGER freq;

void gettime(TIME_T* time)
{
#if !defined(SPEC_WINDOWS)
  QueryPerformanceCounter(time);
#endif /* SPEC_WINDOWS */
}

int64 timediff(TIME_T* start, TIME_T* end)
{
#if !defined(SPEC_WINDOWS)
  return (int64)((end->QuadPart - start->QuadPart));
#else
  return 0;
#endif
}

int64 timenorm(int64  cur_time)
{
#if !defined(SPEC_WINDOWS)
  static int first = 1;

  if(first) 
  {
    QueryPerformanceFrequency(&freq);
    first = 0;
  }

  return (int64)(cur_time * 1000 /(freq.QuadPart));
#else
       return 0;
#endif /* SPEC_WINDOWS */
}

#else

#if !defined(SPEC)
/* SPEC NOTE: timezone tz is obsolete */
static struct timezone tz;

void gettime(TIME_T* time)
{
  gettimeofday(time, &tz);
}
#else
void gettime(TIME_T* time) { }
#endif /* !SPEC */

int64 timediff(TIME_T* start, TIME_T* end)
{
  int t1, t2;

  t1 =  end->tv_sec  - start->tv_sec;
  t2 =  end->tv_usec - start->tv_usec;
  return (int64) t2 + (int64) t1 * (int64) 1000000;
}

int64 timenorm(int64 cur_time)
{
  return (int64)(cur_time / (int64) 1000);
}
#endif
