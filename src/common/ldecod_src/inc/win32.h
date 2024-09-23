
/*!
 ************************************************************************
 *  \file
 *     win32.h
 *
 *  \brief
 *     win32 definitions for H.264 codec.
 *
 *  \author
 *
 ************************************************************************
 */
#ifndef _WIN32_H_
#define _WIN32_H_

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <assert.h>

#if (defined(_OPENMP) || defined(SPEC_OPENMP)) && !defined(SPEC_SUPPRESS_OPENMP) && !defined(SPEC_AUTO_SUPPRESS_OPENMP)
# define OPENMP
# define NUM_THREADS 8
#endif

#if defined(WIN32) || defined (WIN64) || defined(SPEC_WINDOWS)
# include <io.h>
#ifndef SPEC
# include <sys/types.h>
# include <sys/stat.h>
#endif /* !SPEC */
# include <windows.h>
#if (_MSC_VER < 1400)
typedef int   intptr_t;
#else
# include <crtdefs.h>
#endif
#if (defined(_OPENMP) || defined(SPEC_OPENMP)) && !defined(SPEC_SUPPRESS_OPENMP) && !defined(SPEC_AUTO_SUPPRESS_OPENMP)
# include <omp.h>
#endif

# define strcmp _strcmpi

# define  snprintf _snprintf
# define  open     _open
# define  close    _close
# define  read     _read
# define  write    _write
# define  lseek    _lseeki64
# define  fsync    _commit
# define  tell     _telli64
#ifndef SPEC
# define  TIMEB    _timeb
# define  TIME_T    LARGE_INTEGER
#endif /*! SPEC */
# define  OPENFLAGS_WRITE _O_WRONLY|_O_CREAT|_O_BINARY|_O_TRUNC
# define  OPEN_PERMISSIONS _S_IREAD | _S_IWRITE
# define  OPENFLAGS_READ  _O_RDONLY|_O_BINARY
#ifndef SPEC_NO_UNDERBAR_INLINE
# define  inline   _inline
#endif
# define  forceinline __forceinline
#else
# include <unistd.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <time.h>
# include <stdint.h>
#if (defined(_OPENMP) || defined(SPEC_OPENMP)) && !defined(SPEC_SUPPRESS_OPENMP) && !defined(SPEC_AUTO_SUPPRESS_OPENMP)
# include <omp.h>
#endif

# define  TIMEB    timeb
# define  TIME_T   struct timeval
# define  tell(fd) lseek(fd, 0, SEEK_CUR)
# define  OPENFLAGS_WRITE O_WRONLY|O_CREAT|O_TRUNC
# define  OPENFLAGS_READ  O_RDONLY
# define  OPEN_PERMISSIONS S_IRUSR | S_IWUSR

# if __STDC_VERSION__ >= 199901L
   /* "inline" is a keyword */
# else
#  define inline /* nothing */
# endif
# define  forceinline inline
#endif

#if (defined(WIN32) || defined(WIN64) || defined(SPEC_WINDOWS)) && !defined(__GNUC__)
typedef __int64   int64;
typedef unsigned __int64   uint64;
# define FORMAT_OFF_T "I64d"
# ifndef INT64_MIN
#  define INT64_MIN        (-9223372036854775807i64 - 1i64)
# endif
#else
#if defined(SPEC_USE_LL_INT64)
typedef long long int64;
typedef unsigned long long  uint64;
# define FORMAT_OFF_T "lld"
#else
typedef int64_t int64;
typedef uint64_t uint64;
# define FORMAT_OFF_T "ld"
#endif  /* SPEC_USE_LL_INT64 */
# ifndef INT64_MIN
#  define INT64_MIN        (-9223372036854775807LL - 1LL)
# endif
#endif

#ifndef SPEC
void   gettime(TIME_T* time);
int64 timediff(TIME_T* start, TIME_T* end);
int64 timenorm(int64 cur_time);
#endif

#endif
