#ifndef __SOFT_FP_H__
#define __SOFT_FP_H__

#include "sfp-machine.h"

#define abort()   // 54
/* For unreachable default cases in switch statements over bitwise OR
   of FP_CLS_* values.  */
#if (defined __GNUC__							\
     && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5)))
# define _FP_UNREACHABLE	__builtin_unreachable ()
#else
# define _FP_UNREACHABLE	abort ()
#endif
// 63
#if ((defined __GNUC__							\
      && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)))	\
     || (defined __STDC_VERSION__ && __STDC_VERSION__ >= 201112L))
# define _FP_STATIC_ASSERT(expr, msg)		\
  _Static_assert ((expr), msg)
#else
# define _FP_STATIC_ASSERT(expr, msg)					\
  extern int (*__Static_assert_function (void))				\
    [!!sizeof (struct { int __error_if_negative: (expr) ? 2 : -1; })]
#endif


#define _FP_ZERO_INIT	  = 0		// 82
#define _FP_WORKBITS		3			// 85
#define _FP_WORK_LSB		((_FP_W_TYPE) 1 << 3)
#define _FP_WORK_ROUND		((_FP_W_TYPE) 1 << 2)	// 87
#define _FP_WORK_GUARD		((_FP_W_TYPE) 1 << 1)
#define _FP_WORK_STICKY		((_FP_W_TYPE) 1 << 0)	// 89

#ifndef FP_RND_NEAREST
# define FP_RND_NEAREST		0
# define FP_RND_ZERO		1
# define FP_RND_PINF		2
# define FP_RND_MINF		3
#endif
#ifndef FP_ROUNDMODE
# define FP_ROUNDMODE		FP_RND_NEAREST
#endif

/* By default don't care about exceptions.  */	// 101
#ifndef FP_EX_INVALID
# define FP_EX_INVALID		0
#endif
#ifndef FP_EX_OVERFLOW
# define FP_EX_OVERFLOW		0
#endif
#ifndef FP_EX_UNDERFLOW
# define FP_EX_UNDERFLOW	0
#endif
#ifndef FP_EX_DIVZERO
# define FP_EX_DIVZERO		0
#endif
#ifndef FP_EX_INEXACT
# define FP_EX_INEXACT		0
#endif
#ifndef FP_EX_DENORM
# define FP_EX_DENORM		0
#endif

/* Sub-exceptions of "invalid".  */		// 121
/* Signaling NaN operand.  */
#ifndef FP_EX_INVALID_SNAN
# define FP_EX_INVALID_SNAN	0
#endif
/* Inf * 0.  */							// 126
#ifndef FP_EX_INVALID_IMZ
# define FP_EX_INVALID_IMZ	0
#endif

/* Inf - Inf.  */						// 134
#ifndef FP_EX_INVALID_ISI
# define FP_EX_INVALID_ISI	0
#endif
/* 0 / 0.  */
#ifndef FP_EX_INVALID_ZDZ
# define FP_EX_INVALID_ZDZ	0
#endif
/* Inf / Inf.  */
#ifndef FP_EX_INVALID_IDI
# define FP_EX_INVALID_IDI	0
#endif

/* Invalid conversion to integer.  */
#ifndef FP_EX_INVALID_CVI
# define FP_EX_INVALID_CVI	0
#endif
/* Invalid comparison.  */				// 154
#ifndef FP_EX_INVALID_VC				
# define FP_EX_INVALID_VC	0			
#endif

/* _FP_STRUCT_LAYOUT may be defined as an attribute to determine the
   struct layout variant used for structures where bit-fields are used
   to access specific parts of binary floating-point numbers.  This is
   required for systems where the default ABI uses struct layout with
   differences in how consecutive bit-fields are laid out from the
   default expected by soft-fp.  */
#ifndef _FP_STRUCT_LAYOUT
# define _FP_STRUCT_LAYOUT
#endif
										// 169
#ifdef _FP_DECL_EX
# define FP_DECL_EX					\
  int _fex = 0;						\
  _FP_DECL_EX
#else
# define FP_DECL_EX int _fex = 0
#endif

/* Initialize any machine-specific state used in FP_ROUNDMODE,
   FP_TRAPPING_EXCEPTIONS or FP_HANDLE_EXCEPTIONS.  */
#ifndef FP_INIT_ROUNDMODE
# define FP_INIT_ROUNDMODE do {} while (0)
#endif

/* Initialize any machine-specific state used in
   FP_TRAPPING_EXCEPTIONS or FP_HANDLE_EXCEPTIONS.  */
# define FP_INIT_TRAPPING_EXCEPTIONS FP_INIT_ROUNDMODE	// 186

/* Initialize any machine-specific state used in
   FP_HANDLE_EXCEPTIONS.  */
#define FP_INIT_EXCEPTIONS FP_INIT_TRAPPING_EXCEPTIONS	// 192

#define FP_HANDLE_EXCEPTIONS do {} while (0)	// 196

#define FP_DENORM_ZERO  0			// 201
#define FP_SET_EXCEPTION(ex)	_fex |= (ex)		// 212
#define FP_CUR_EXCEPTIONS		 (_fex)				// 215
#define FP_TRAPPING_EXCEPTIONS 0					// 219
 

													// 259
#define _FP_ROUND_NEAREST(wc, X)				\
  do								\
    {								\
      if ((_FP_FRAC_LOW_##wc (X) & 15) != _FP_WORK_ROUND)	\
	_FP_FRAC_ADDI_##wc (X, _FP_WORK_ROUND);			\
    }								\
  while (0)

#define _FP_ROUND_ZERO(wc, X)		(void) 0

#define _FP_ROUND_PINF(wc, X)				\
  do							\
    {							\
      if (!X##_s && (_FP_FRAC_LOW_##wc (X) & 7))	\
	_FP_FRAC_ADDI_##wc (X, _FP_WORK_LSB);		\
    }							\
  while (0)

#define _FP_ROUND_MINF(wc, X)			\
  do						\
    {						\
      if (X##_s && (_FP_FRAC_LOW_##wc (X) & 7))	\
	_FP_FRAC_ADDI_##wc (X, _FP_WORK_LSB);	\
    }						\
  while (0)

#define _FP_ROUND(wc, X)			\
  do						\
    {						\
      if (_FP_FRAC_LOW_##wc (X) & 7)		\
	{					\
	  FP_SET_EXCEPTION (FP_EX_INEXACT);	\
	  switch (FP_ROUNDMODE)			\
	    {					\
	    case FP_RND_NEAREST:		\
	      _FP_ROUND_NEAREST (wc, X);	\
	      break;				\
	    case FP_RND_ZERO:			\
	      _FP_ROUND_ZERO (wc, X);		\
	      break;				\
	    case FP_RND_PINF:			\
	      _FP_ROUND_PINF (wc, X);		\
	      break;				\
	    case FP_RND_MINF:			\
	      _FP_ROUND_MINF (wc, X);		\
	      break;				\
	    }					\
	}					\
    }						\
  while (0)

#define FP_CLS_NORMAL		0		// 310
#define FP_CLS_ZERO		1
#define FP_CLS_INF		2
#define FP_CLS_NAN		3

#define _FP_CLS_COMBINE(x, y)	(((x) << 2) | (y))	// 315

#include "op-1.h"
#include "op-2.h"
#include "op-4.h"
#include "op-8.h"
#include "op-common.h"

/* Sigh.  Silly things longlong.h needs.  */
#define UWtype		_FP_W_TYPE
#define W_TYPE_SIZE	_FP_W_TYPE_SIZE

typedef int QItype __attribute__ ((mode (QI)));
typedef int SItype __attribute__ ((mode (SI)));
typedef int DItype __attribute__ ((mode (DI)));
typedef unsigned int UQItype __attribute__ ((mode (QI)));
typedef unsigned int USItype __attribute__ ((mode (SI)));
typedef unsigned int UDItype __attribute__ ((mode (DI)));
#if _FP_W_TYPE_SIZE == 32
typedef unsigned int UHWtype __attribute__ ((mode (HI)));
#elif _FP_W_TYPE_SIZE == 64
typedef USItype UHWtype;
#endif

#ifndef CMPtype
# define CMPtype	int
#endif

#define SI_BITS		(__CHAR_BIT__ * (int) sizeof (SItype))
#define DI_BITS		(__CHAR_BIT__ * (int) sizeof (DItype))

#include "longlong.h"

#endif



