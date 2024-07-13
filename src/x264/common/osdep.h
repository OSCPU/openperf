/*****************************************************************************
 * osdep.h: platform-specific code
 *****************************************************************************
 * Copyright (C) 2007-2024 x264 project
 *
 * Authors: Loren Merritt <lorenm@u.washington.edu>
 *          Laurent Aimar <fenrir@via.ecp.fr>
 *          Henrik Gramner <henrik@gramner.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02111, USA.
 *
 * This program is also available under a commercial proprietary license.
 * For more information, contact us at licensing@x264.com.
 *****************************************************************************/

#ifndef X264_OSDEP_H
#define X264_OSDEP_H

#define _LARGEFILE_SOURCE 1
#define _FILE_OFFSET_BITS 64

#define BIT_DEPTH 8

#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <openlibm.h>
#include <inttypes.h>
#include <strings.h>
#include <x264.h>
#include <bench_malloc.h>
#include <printf.h>


// #define strtok_r(str,delim,save) strtok(str,delim)

// #if defined(_MSC_VER) && _MSC_VER < 1900
// /* MSVC pre-VS2015 has broken snprintf/vsnprintf implementations which are incompatible with C99. */
// static inline int x264_vsnprintf( char *s, size_t n, const char *fmt, va_list arg )
// {
//     int length = -1;

//     if( n )
//     {
//         va_list arg2;
//         va_copy( arg2, arg );
//         length = _vsnprintf( s, n, fmt, arg2 );
//         va_end( arg2 );

//         /* _(v)snprintf adds a null-terminator only if the length is less than the buffer size. */
//         if( length < 0 || length >= n )
//             s[n-1] = '\0';
//     }

//     /* _(v)snprintf returns a negative number if the length is greater than the buffer size. */
//     if( length < 0 )
//         return _vscprintf( fmt, arg );

//     return length;
// }

// static inline int x264_snprintf( char *s, size_t n, const char *fmt, ... )
// {
//     va_list arg;
//     va_start( arg, fmt );
//     int length = x264_vsnprintf( s, n, fmt, arg );
//     va_end( arg );
//     return length;
// }

// #define snprintf  x264_snprintf
// #define vsnprintf x264_vsnprintf
// #endif


#define sprintf my_sprintf
#define x264_printf my_printf

// #define x264_fopen       fopen
// #define x264_rename      rename
// #define x264_struct_stat struct stat
// #define x264_fstat       fstat
// #define x264_stat        stat


/* mdate: return the current date in microsecond */
// X264_API int64_t x264_mdate( void );


// #define x264_vfprintf vfprintf


// static inline int x264_is_regular_file_path( const char *filename )
// {
//     x264_struct_stat file_stat;
//     if( x264_stat( filename, &file_stat ) )
//         return 1;
//     return S_ISREG( file_stat.st_mode );
// }


// static inline int x264_is_regular_file( FILE *filehandle )
// {
//     x264_struct_stat file_stat;
//     if( x264_fstat( fileno( filehandle ), &file_stat ) )
//         return 1;
//     return S_ISREG( file_stat.st_mode );
// }

#define x264_glue3_expand(x,y,z) x##_##y##_##z
#define x264_glue3(x,y,z) x264_glue3_expand(x,y,z)

#ifdef _MSC_VER
#define DECLARE_ALIGNED( var, n ) __declspec(align(n)) var
#else
#define DECLARE_ALIGNED( var, n ) var __attribute__((aligned(n)))
#endif

#define ALIGNED_4( var )  DECLARE_ALIGNED( var, 4 )
#define ALIGNED_8( var )  DECLARE_ALIGNED( var, 8 )
#define ALIGNED_16( var ) DECLARE_ALIGNED( var, 16 )

// ARM compilers don't reliably align stack variables
// - EABI requires only 8 byte stack alignment to be maintained
// - gcc can't align stack variables to more even if the stack were to be correctly aligned outside the function
// - armcc can't either, but is nice enough to actually tell you so
// - Apple gcc only maintains 4 byte alignment
// - llvm can align the stack, but only in svn and (unrelated) it exposes bugs in all released GNU binutils...

#define ALIGNED_ARRAY_EMU( mask, type, name, sub1, ... )\
    uint8_t name##_u [sizeof(type sub1 __VA_ARGS__) + mask]; \
    type (*name) __VA_ARGS__ = (void*)((intptr_t)(name##_u+mask) & ~mask)

#define ALIGNED_ARRAY_8( type, name, sub1, ... ) ALIGNED_8( type name sub1 __VA_ARGS__ )

#define ALIGNED_ARRAY_16( type, name, sub1, ... ) ALIGNED_16( type name sub1 __VA_ARGS__ )


#define EXPAND(x) x

#define NATIVE_ALIGN 16
#define ALIGNED_32 ALIGNED_16
#define ALIGNED_64 ALIGNED_16
#define ALIGNED_ARRAY_32 ALIGNED_ARRAY_16
#define ALIGNED_ARRAY_64 ALIGNED_ARRAY_16

// #if STACK_ALIGNMENT > 16 || (ARCH_X86 && STACK_ALIGNMENT > 4)
// #define REALIGN_STACK __attribute__((force_align_arg_pointer))
// #else
// #define REALIGN_STACK
// #endif

#define REALIGN_STACK

#if defined(__GNUC__) && (__GNUC__ > 3 || __GNUC__ == 3 && __GNUC_MINOR__ > 0)
#define UNUSED __attribute__((unused))
#define ALWAYS_INLINE __attribute__((always_inline)) inline
#define NOINLINE __attribute__((noinline))
#define MAY_ALIAS __attribute__((may_alias))
#define x264_constant_p(x) __builtin_constant_p(x)
#define x264_nonconstant_p(x) (!__builtin_constant_p(x))
#else
#ifdef _MSC_VER
#define ALWAYS_INLINE __forceinline
#define NOINLINE __declspec(noinline)
#else
#define ALWAYS_INLINE inline
#define NOINLINE
#endif
#define UNUSED
#define MAY_ALIAS
#define x264_constant_p(x) 0
#define x264_nonconstant_p(x) 0
#endif

/* threads */
#define x264_pthread_t               int
#define x264_pthread_create(t,u,f,d) 0
#define x264_pthread_join(t,s)


#define x264_pthread_mutex_t         int
#define x264_pthread_mutex_init(m,f) 0
#define x264_pthread_mutex_destroy(m)
#define x264_pthread_mutex_lock(m)
#define x264_pthread_mutex_unlock(m)
#define x264_pthread_cond_t          int
#define x264_pthread_cond_init(c,f)  0
#define x264_pthread_cond_destroy(c)
#define x264_pthread_cond_broadcast(c)
#define x264_pthread_cond_wait(c,m)
#define x264_pthread_attr_t          int
#define x264_pthread_attr_init(a)    0
#define x264_pthread_attr_destroy(a)
#define X264_PTHREAD_MUTEX_INITIALIZER 0



#define x264_threading_init() 0


static ALWAYS_INLINE int x264_pthread_fetch_and_add( int *val, int add, x264_pthread_mutex_t *mutex )
{
    int res = *val;
    *val += add;
    return res;
}

#define WORD_SIZE sizeof(void*)

#define asm __asm__


static ALWAYS_INLINE uint32_t endian_fix32( uint32_t x )
{
    return (x<<24) + ((x<<8)&0xff0000) + ((x>>8)&0xff00) + (x>>24);
}

static ALWAYS_INLINE uint64_t endian_fix64( uint64_t x )
{
    return endian_fix32(x>>32) + ((uint64_t)endian_fix32(x)<<32);
}

static ALWAYS_INLINE uintptr_t endian_fix( uintptr_t x )
{
    return WORD_SIZE == 8 ? endian_fix64(x) : endian_fix32(x);
}
static ALWAYS_INLINE uint16_t endian_fix16( uint16_t x )
{
    return (uint16_t)((x<<8)|(x>>8));
}


/* For values with 4 bits or less. */
static ALWAYS_INLINE int x264_ctz_4bit( uint32_t x )
{
    static uint8_t lut[16] = {4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0};
    return lut[x];
}

#if defined(__GNUC__) && (__GNUC__ > 3 || __GNUC__ == 3 && __GNUC_MINOR__ > 3)
#define x264_clz(x) __builtin_clz(x)
#define x264_ctz(x) __builtin_ctz(x)
#else
static ALWAYS_INLINE int x264_clz( uint32_t x )
{
    static uint8_t lut[16] = {4,3,2,2,1,1,1,1,0,0,0,0,0,0,0,0};
    int y, z = (((x >> 16) - 1) >> 27) & 16;
    x >>= z^16;
    z += y = ((x - 0x100) >> 28) & 8;
    x >>= y^8;
    z += y = ((x - 0x10) >> 29) & 4;
    x >>= y^4;
    return z + lut[x];
}

static ALWAYS_INLINE int x264_ctz( uint32_t x )
{
    static uint8_t lut[16] = {4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0};
    int y, z = (((x & 0xffff) - 1) >> 27) & 16;
    x >>= z;
    z += y = (((x & 0xff) - 1) >> 28) & 8;
    x >>= y;
    z += y = (((x & 0xf) - 1) >> 29) & 4;
    x >>= y;
    return z + lut[x&0xf];
}
#endif

#define x264_prefetch(x)

#endif /* X264_OSDEP_H */
