/* stb_image - v2.26 - public domain image loader - http://nothings.org/stb
                                  no warranty implied; use at your own risk

   Do this:
      #define STB_IMAGE_IMPLEMENTATION
   before you include this file in *one* C or C++ file to create the implementation.

   // i.e. it should look like this:
   #include ...
   #include ...
   #include ...
   #define STB_IMAGE_IMPLEMENTATION
   #include "stb_image.h"

   You can #define STBI_ASSERT(x) before the #include to avoid using assert.h.
   And #define STBI_MALLOC, STBI_REALLOC, and STBI_FREE to avoid using malloc,realloc,free


   QUICK NOTES:
      Primarily of interest to game developers and other people who can
          avoid problematic images and only need the trivial interface

      JPEG baseline & progressive (12 bpc/arithmetic not supported, same as stock IJG lib)
      PNG 1/2/4/8/16-bit-per-channel

      TGA (not sure what subset, if a subset)
      BMP non-1bpp, non-RLE
      PSD (composited view only, no extra channels, 8/16 bit-per-channel)

      GIF (*comp always reports as 4-channel)
      HDR (radiance rgbE format)
      PIC (Softimage PIC)
      PNM (PPM and PGM binary only)

      Animated GIF still needs a proper API, but here's one way to do it:
          http://gist.github.com/urraka/685d9a6340b26b830d49

      - decode from memory or through FILE (define STBI_NO_STDIO to remove code)
      - decode from arbitrary I/O callbacks
      - SIMD acceleration on x86/x64 (SSE2) and ARM (NEON)

   Full documentation under "DOCUMENTATION" below.


LICENSE

  See end of file for license information.

RECENT REVISION HISTORY:

      2.26  (2020-07-13) many minor fixes
      2.25  (2020-02-02) fix warnings
      2.24  (2020-02-02) fix warnings; thread-local failure_reason and flip_vertically
      2.23  (2019-08-11) fix clang static analysis warning
      2.22  (2019-03-04) gif fixes, fix warnings
      2.21  (2019-02-25) fix typo in comment
      2.20  (2019-02-07) support utf8 filenames in Windows; fix warnings and platform ifdefs
      2.19  (2018-02-11) fix warning
      2.18  (2018-01-30) fix warnings
      2.17  (2018-01-29) bugfix, 1-bit BMP, 16-bitness query, fix warnings
      2.16  (2017-07-23) all functions have 16-bit variants; optimizations; bugfixes
      2.15  (2017-03-18) fix png-1,2,4; all Imagenet JPGs; no runtime SSE detection on GCC
      2.14  (2017-03-03) remove deprecated STBI_JPEG_OLD; fixes for Imagenet JPGs
      2.13  (2016-12-04) experimental 16-bit API, only for PNG so far; fixes
      2.12  (2016-04-02) fix typo in 2.11 PSD fix that caused crashes
      2.11  (2016-04-02) 16-bit PNGS; enable SSE2 in non-gcc x64
                         RGB-format JPEG; remove white matting in PSD;
                         allocate large structures on the stack;
                         correct channel count for PNG & BMP
      2.10  (2016-01-22) avoid warning introduced in 2.09
      2.09  (2016-01-16) 16-bit TGA; comments in PNM files; STBI_REALLOC_SIZED

   See end of file for full revision history.


 ============================    Contributors    =========================

 Image formats                          Extensions, features
    Sean Barrett (jpeg, png, bmp)          Jetro Lauha (stbi_info)
    Nicolas Schulz (hdr, psd)              Martin "SpartanJ" Golini (stbi_info)
    Jonathan Dummer (tga)                  James "moose2000" Brown (iPhone PNG)
    Jean-Marc Lienher (gif)                Ben "Disch" Wenger (io callbacks)
    Tom Seddon (pic)                       Omar Cornut (1/2/4-bit PNG)
    Thatcher Ulrich (psd)                  Nicolas Guillemot (vertical flip)
    Ken Miller (pgm, ppm)                  Richard Mitton (16-bit PSD)
    github:urraka (animated gif)           Junggon Kim (PNM comments)
    Christopher Forseth (animated gif)     Daniel Gibson (16-bit TGA)
                                           socks-the-fox (16-bit PNG)
                                           Jeremy Sawicki (handle all ImageNet JPGs)
 Optimizations & bugfixes                  Mikhail Morozov (1-bit BMP)
    Fabian "ryg" Giesen                    Anael Seghezzi (is-16-bit query)
    Arseny Kapoulkine
    John-Mark Allen
    Carmelo J Fdez-Aguera

 Bug & warning fixes
    Marc LeBlanc            David Woo          Guillaume George     Martins Mozeiko
    Christpher Lloyd        Jerry Jansson      Joseph Thomson       Blazej Dariusz Roszkowski
    Phil Jordan                                Dave Moore           Roy Eltham
    Hayaki Saito            Nathan Reed        Won Chun
    Luke Graham             Johan Duparc       Nick Verigakis       the Horde3D community
    Thomas Ruf              Ronny Chevalier                         github:rlyeh
    Janez Zemva             John Bartholomew   Michal Cichon        github:romigrou
    Jonathan Blow           Ken Hamada         Tero Hanninen        github:svdijk
                            Laurent Gomila     Cort Stratton        github:snagar
    Aruelien Pocheville     Sergio Gonzalez    Thibault Reuille     github:Zelex
    Cass Everitt            Ryamond Barbiero                        github:grim210
    Paul Du Bois            Engin Manap        Aldo Culquicondor    github:sammyhw
    Philipp Wiesemann       Dale Weiler        Oriol Ferrer Mesia   github:phprus
    Josh Tobin                                 Matthew Gregan       github:poppolopoppo
    Julian Raschke          Gregory Mullen     Christian Floisand   github:darealshinji
    Baldur Karlsson         Kevin Schmidt      JR Smith             github:Michaelangel007
                            Brad Weinberger    Matvey Cherevko      [reserved]
    Luca Sas                Alexander Veselov  Zack Middleton       [reserved]
    Ryan C. Gordon          [reserved]                              [reserved]
                     DO NOT ADD YOUR NAME HERE

  To add your name to the credits, pick a random blank space in the middle and fill it.
  80% of merge conflicts on stb PRs are due to people adding their name at the end
  of the credits.
*/

// DOCUMENTATION
//
// Limitations:
//    - no 12-bit-per-channel JPEG
//    - no JPEGs with arithmetic coding
//    - GIF always returns *comp=4
//
// Basic usage (see HDR discussion below for HDR usage):
//    int x,y,n;
//    unsigned char *data = stbi_load(filename, &x, &y, &n, 0);
//    // ... process data if not NULL ...
//    // ... x = width, y = height, n = # 8-bit components per pixel ...
//    // ... replace '0' with '1'..'4' to force that many components per pixel
//    // ... but 'n' will always be the number that it would have been if you said 0
//    stbi_image_free(data)
//
// Standard parameters:
//    int *x                 -- outputs image width in pixels
//    int *y                 -- outputs image height in pixels
//    int *channels_in_file  -- outputs # of image components in image file
//    int desired_channels   -- if non-zero, # of image components requested in result
//
// The return value from an image loader is an 'unsigned char *' which points
// to the pixel data, or NULL on an allocation failure or if the image is
// corrupt or invalid. The pixel data consists of *y scanlines of *x pixels,
// with each pixel consisting of N interleaved 8-bit components; the first
// pixel pointed to is top-left-most in the image. There is no padding between
// image scanlines or between pixels, regardless of format. The number of
// components N is 'desired_channels' if desired_channels is non-zero, or
// *channels_in_file otherwise. If desired_channels is non-zero,
// *channels_in_file has the number of components that _would_ have been
// output otherwise. E.g. if you set desired_channels to 4, you will always
// get RGBA output, but you can check *channels_in_file to see if it's trivially
// opaque because e.g. there were only 3 channels in the source image.
//
// An output image with N components has the following components interleaved
// in this order in each pixel:
//
//     N=#comp     components
//       1           grey
//       2           grey, alpha
//       3           red, green, blue
//       4           red, green, blue, alpha
//
// If image loading fails for any reason, the return value will be NULL,
// and *x, *y, *channels_in_file will be unchanged. The function
// stbi_failure_reason() can be queried for an extremely brief, end-user
// unfriendly explanation of why the load failed. Define STBI_NO_FAILURE_STRINGS
// to avoid compiling these strings at all, and STBI_FAILURE_USERMSG to get slightly
// more user-friendly ones.
//
// Paletted PNG, BMP, GIF, and PIC images are automatically depalettized.
//
// ===========================================================================
//
// UNICODE:
//
//   If compiling for Windows and you wish to use Unicode filenames, compile
//   with
//       #define STBI_WINDOWS_UTF8
//   and pass utf8-encoded filenames. Call stbi_convert_wchar_to_utf8 to convert
//   Windows wchar_t filenames to utf8.
//
// ===========================================================================
//
// Philosophy
//
// stb libraries are designed with the following priorities:
//
//    1. easy to use
//    2. easy to maintain
//    3. good performance
//
// Sometimes I let "good performance" creep up in priority over "easy to maintain",
// and for best performance I may provide less-easy-to-use APIs that give higher
// performance, in addition to the easy-to-use ones. Nevertheless, it's important
// to keep in mind that from the standpoint of you, a client of this library,
// all you care about is #1 and #3, and stb libraries DO NOT emphasize #3 above all.
//
// Some secondary priorities arise directly from the first two, some of which
// provide more explicit reasons why performance can't be emphasized.
//
//    - Portable ("ease of use")
//    - Small source code footprint ("easy to maintain")
//    - No dependencies ("ease of use")
//
// ===========================================================================
//
// I/O callbacks
//
// I/O callbacks allow you to read from arbitrary sources, like packaged
// files or some other source. Data read from callbacks are processed
// through a small internal buffer (currently 128 bytes) to try to reduce
// overhead.
//
// The three functions you must define are "read" (reads some bytes of data),
// "skip" (skips some bytes of data), "eof" (reports if the stream is at the end).
//
// ===========================================================================
//
// SIMD support
//
// The JPEG decoder will try to automatically use SIMD kernels on x86 when
// supported by the compiler. For ARM Neon support, you must explicitly
// request it.
//
// (The old do-it-yourself SIMD API is no longer supported in the current
// code.)
//
// On x86, SSE2 will automatically be used when available based on a run-time
// test; if not, the generic C versions are used as a fall-back. On ARM targets,
// the typical path is to have separate builds for NEON and non-NEON devices
// (at least this is true for iOS and Android). Therefore, the NEON support is
// toggled by a build flag: define STBI_NEON to get NEON loops.
//
// If for some reason you do not want to use any of SIMD code, or if
// you have issues compiling it, you can disable it entirely by
// defining STBI_NO_SIMD.
//
// ===========================================================================
//
// HDR image support   (disable by defining STBI_NO_HDR)
//
// stb_image supports loading HDR images in general, and currently the Radiance
// .HDR file format specifically. You can still load any file through the existing
// interface; if you attempt to load an HDR file, it will be automatically remapped
// to LDR, assuming gamma 2.2 and an arbitrary scale factor defaulting to 1;
// both of these constants can be reconfigured through this interface:
//
//     stbi_hdr_to_ldr_gamma(2.2f);
//     stbi_hdr_to_ldr_scale(1.0f);
//
// (note, do not use _inverse_ constants; stbi_image will invert them
// appropriately).
//
// Additionally, there is a new, parallel interface for loading files as
// (linear) floats to preserve the full dynamic range:
//
//    float *data = stbi_loadf(filename, &x, &y, &n, 0);
//
// If you load LDR images through this interface, those images will
// be promoted to floating point values, run through the inverse of
// constants corresponding to the above:
//
//     stbi_ldr_to_hdr_scale(1.0f);
//     stbi_ldr_to_hdr_gamma(2.2f);
//
// Finally, given a filename (or an open file or memory block--see header
// file for details) containing image data, you can query for the "most
// appropriate" interface to use (that is, whether the image is HDR or
// not), using:
//
//     stbi_is_hdr(char *filename);
//
// ===========================================================================
//
// iPhone PNG support:
//
// By default we convert iphone-formatted PNGs back to RGB, even though
// they are internally encoded differently. You can disable this conversion
// by calling stbi_convert_iphone_png_to_rgb(0), in which case
// you will always just get the native iphone "format" through (which
// is BGR stored in RGB).
//
// Call stbi_set_unpremultiply_on_load(1) as well to force a divide per
// pixel to remove any premultiplied alpha *only* if the image file explicitly
// says there's premultiplied data (currently only happens in iPhone images,
// and only if iPhone convert-to-rgb processing is on).
//
// ===========================================================================
//
// ADDITIONAL CONFIGURATION
//
//  - You can suppress implementation of any of the decoders to reduce
//    your code footprint by #defining one or more of the following
//    symbols before creating the implementation.
//
//        STBI_NO_JPEG
//        STBI_NO_PNG
//        STBI_NO_BMP
//        STBI_NO_PSD
//        STBI_NO_TGA
//        STBI_NO_GIF
//        STBI_NO_HDR
//        STBI_NO_PIC
//        STBI_NO_PNM   (.ppm and .pgm)
//
//  - You can request *only* certain decoders and suppress all other ones
//    (this will be more forward-compatible, as addition of new decoders
//    doesn't require you to disable them explicitly):
//
//        STBI_ONLY_JPEG
//        STBI_ONLY_PNG
//        STBI_ONLY_BMP
//        STBI_ONLY_PSD
//        STBI_ONLY_TGA
//        STBI_ONLY_GIF
//        STBI_ONLY_HDR
//        STBI_ONLY_PIC
//        STBI_ONLY_PNM   (.ppm and .pgm)
//
//   - If you use STBI_NO_PNG (or _ONLY_ without PNG), and you still
//     want the zlib decoder to be available, #define STBI_SUPPORT_ZLIB
//
//  - If you define STBI_MAX_DIMENSIONS, stb_image will reject images greater
//    than that size (in either width or height) without further processing.
//    This is to let programs in the wild set an upper bound to prevent
//    denial-of-service attacks on untrusted data, as one could generate a
//    valid image of gigantic dimensions and force stb_image to allocate a
//    huge block of memory and spend disproportionate time decoding it. By
//    default this is set to (1 << 24), which is 16777216, but that's still
//    very big.

#include "stb.h"

#define STBI_VERSION 1

#include <limits.h>
#include <stdarg.h>
#include <stddef.h> // ptrdiff_t on osx
#include <stdlib.h>
#include <string.h>

#ifndef STBI_ASSERT
#include <bench.h>
#define STBI_ASSERT(x) assert(x)
#endif

#ifdef __cplusplus
#define stbi_inline inline
#else
#define stbi_inline
#endif

#include <stdint.h>
typedef uint16_t stbi__uint16;
typedef int16_t stbi__int16;
typedef uint32_t stbi__uint32;
typedef int32_t stbi__int32;

// should produce compiler error if size is wrong
typedef unsigned char validate_uint32[sizeof(stbi__uint32) == 4 ? 1 : -1];

#define STBI_NOTUSED(v) (void)sizeof(v)

#ifndef STBI_MALLOC
#define STBI_MALLOC(sz)        malloc(sz)
#define STBI_REALLOC(p, newsz) realloc(p, newsz)
#define STBI_FREE(p)           free(p)
#endif

#define STBI_SIMD_ALIGN(type, name) type name

#ifndef STBI_MAX_DIMENSIONS
#define STBI_MAX_DIMENSIONS (1 << 24)
#endif

///////////////////////////////////////////////
//
//  stbi__context struct and start_xxx functions

// stbi__context structure is our basic context used by all images, so it
// contains all the IO context, plus some basic image information
typedef struct {
  stbi__uint32 img_x, img_y;
  int img_n, img_out_n;

  int buflen;

  stbi_uc *img_buffer, *img_buffer_end;
  stbi_uc *img_buffer_original, *img_buffer_original_end;
} stbi__context;

// initialize a memory-decode context
static void stbi__start_mem(stbi__context *s, stbi_uc const *buffer, int len) {
  s->img_buffer = s->img_buffer_original = (stbi_uc *)buffer;
  s->img_buffer_end = s->img_buffer_original_end = (stbi_uc *)buffer + len;
}

static void stbi__rewind(stbi__context *s) {
  // conceptually rewind SHOULD rewind to the beginning of the stream,
  // but we just rewind to the beginning of the initial buffer, because
  // we only use it after doing 'test', which only ever looks at at most 92 bytes
  s->img_buffer = s->img_buffer_original;
  s->img_buffer_end = s->img_buffer_original_end;
}

enum {
  STBI_ORDER_RGB,
  STBI_ORDER_BGR
};

typedef struct {
  int bits_per_channel;
  int num_channels;
  int channel_order;
} stbi__result_info;

static int stbi__jpeg_test(stbi__context *s);
static void *stbi__jpeg_load(stbi__context *s, int *x, int *y, int *comp, int req_comp, stbi__result_info *ri);
static int stbi__jpeg_info(stbi__context *s, int *x, int *y, int *comp);

static const char *stbi__g_failure_reason;

STBIDEF const char *stbi_failure_reason(void) {
  return stbi__g_failure_reason;
}

#ifndef STBI_NO_FAILURE_STRINGS
static int stbi__err(const char *str) {
  stbi__g_failure_reason = str;
  return 0;
}
#endif

static void *stbi__malloc(size_t size) {
  return STBI_MALLOC(size);
}

// stb_image uses ints pervasively, including for offset calculations.
// therefore the largest decoded image size we can support with the
// current code, even on 64-bit targets, is INT_MAX. this is not a
// significant limitation for the intended use case.
//
// we do, however, need to make sure our size calculations don't
// overflow. hence a few helper functions for size calculations that
// multiply integers together, making sure that they're non-negative
// and no overflow occurs.

// return 1 if the sum is valid, 0 on overflow.
// negative terms are considered invalid.
static int stbi__addsizes_valid(int a, int b) {
  if (b < 0)
    return 0;
  // now 0 <= b <= INT_MAX, hence also
  // 0 <= INT_MAX - b <= INTMAX.
  // And "a + b <= INT_MAX" (which might overflow) is the
  // same as a <= INT_MAX - b (no overflow)
  return a <= INT_MAX - b;
}

// returns 1 if the product is valid, 0 on overflow.
// negative factors are considered invalid.
static int stbi__mul2sizes_valid(int a, int b) {
  if (a < 0 || b < 0)
    return 0;
  if (b == 0)
    return 1; // mul-by-0 is always safe
  // portable way to check for no overflows in a*b
  return a <= INT_MAX / b;
}

// returns 1 if "a*b + add" has no negative terms/factors and doesn't overflow
static int stbi__mad2sizes_valid(int a, int b, int add) {
  return stbi__mul2sizes_valid(a, b) && stbi__addsizes_valid(a * b, add);
}

// returns 1 if "a*b*c + add" has no negative terms/factors and doesn't overflow
static int stbi__mad3sizes_valid(int a, int b, int c, int add) {
  return stbi__mul2sizes_valid(a, b) && stbi__mul2sizes_valid(a * b, c) && stbi__addsizes_valid(a * b * c, add);
}

// returns 1 if "a*b*c*d + add" has no negative terms/factors and doesn't overflow

// mallocs with size overflow checking
static void *stbi__malloc_mad2(int a, int b, int add) {
  if (!stbi__mad2sizes_valid(a, b, add))
    return NULL;
  return stbi__malloc(a * b + add);
}

static void *stbi__malloc_mad3(int a, int b, int c, int add) {
  if (!stbi__mad3sizes_valid(a, b, c, add))
    return NULL;
  return stbi__malloc(a * b * c + add);
}

// stbi__err - error
// stbi__errpf - error returning pointer to float
// stbi__errpuc - error returning pointer to unsigned char

#ifdef STBI_NO_FAILURE_STRINGS
#define stbi__err(x, y) 0
#elif defined(STBI_FAILURE_USERMSG)
#define stbi__err(x, y) stbi__err(y)
#else
#define stbi__err(x, y) stbi__err(x)
#endif

#define stbi__errpf(x, y)  ((float *)(size_t)(stbi__err(x, y) ? NULL : NULL))
#define stbi__errpuc(x, y) ((unsigned char *)(size_t)(stbi__err(x, y) ? NULL : NULL))

static void *stbi__load_main(stbi__context *s, int *x, int *y, int *comp, int req_comp, stbi__result_info *ri,
                             int bpc) {
  memset(ri, 0, sizeof(*ri));         // make sure it's initialized if we add new fields
  ri->bits_per_channel = 8;           // default is 8 so most paths don't have to be changed
  ri->channel_order = STBI_ORDER_RGB; // all current input & output are this, but this is here so we can add BGR order
  ri->num_channels = 0;

  if (stbi__jpeg_test(s))
    return stbi__jpeg_load(s, x, y, comp, req_comp, ri);
  STBI_NOTUSED(bpc);

  return stbi__errpuc("unknown image type", "Image not of any known type, or corrupt");
}

static stbi_uc *stbi__convert_16_to_8(stbi__uint16 *orig, int w, int h, int channels) {
  int i;
  int img_len = w * h * channels;
  stbi_uc *reduced;

  reduced = (stbi_uc *)stbi__malloc(img_len);
  if (reduced == NULL)
    return stbi__errpuc("outofmem", "Out of memory");

  for (i = 0; i < img_len; ++i)
    reduced[i] = (stbi_uc)((orig[i] >> 8) & 0xFF); // top half of each byte is sufficient approx of 16->8 bit scaling

  STBI_FREE(orig);
  return reduced;
}

static unsigned char *stbi__load_and_postprocess_8bit(stbi__context *s, int *x, int *y, int *comp, int req_comp) {
  stbi__result_info ri;
  void *result = stbi__load_main(s, x, y, comp, req_comp, &ri, 8);

  if (result == NULL)
    return NULL;

  // it is the responsibility of the loaders to make sure we get either 8 or 16 bit.
  STBI_ASSERT(ri.bits_per_channel == 8 || ri.bits_per_channel == 16);

  if (ri.bits_per_channel != 8) {
    result = stbi__convert_16_to_8((stbi__uint16 *)result, *x, *y, req_comp == 0 ? *comp : req_comp);
    ri.bits_per_channel = 8;
  }

  // @TODO: move stbi__convert_format to here

  return (unsigned char *)result;
}

STBIDEF stbi_uc *stbi_load_from_memory(stbi_uc const *buffer, int len, int *x, int *y, int *comp, int req_comp) {
  stbi__context s;
  stbi__start_mem(&s, buffer, len);
  return stbi__load_and_postprocess_8bit(&s, x, y, comp, req_comp);
}

//////////////////////////////////////////////////////////////////////////////
//
// Common code used by all image loaders
//

enum {
  STBI__SCAN_load = 0,
  STBI__SCAN_type,
  STBI__SCAN_header
};

stbi_inline static stbi_uc stbi__get8(stbi__context *s) {
  //if (s->img_buffer < s->img_buffer_end)
  return *s->img_buffer++;
  //return 0;
}

stbi_inline static stbi_uc stbi__peep8(stbi__context *s) {
  //if (s->img_buffer < s->img_buffer_end)
  return *s->img_buffer;
  //return 0;
}

stbi_inline static int stbi__at_eof(stbi__context *s) {
  return s->img_buffer >= s->img_buffer_end;
}

static void stbi__skip(stbi__context *s, int n) {
  if (n == 0)
    return; // already there!
  if (n < 0) {
    s->img_buffer = s->img_buffer_end;
    return;
  }
  s->img_buffer += n;
}

static int stbi__get16be(stbi__context *s) {
  int z = stbi__get8(s);
  return (z << 8) + stbi__get8(s);
}

#define STBI__BYTECAST(x) ((stbi_uc)((x) & 255)) // truncate int to byte without warnings

//////////////////////////////////////////////////////////////////////////////
//
//  generic converter from built-in img_n to req_comp
//    individual types do this automatically as much as possible (e.g. jpeg
//    does all cases internally since it needs to colorspace convert anyway,
//    and it never has alpha, so very few cases ). png can automatically
//    interleave an alpha=255 channel, but falls back to this for other cases
//
//  assume data buffer is malloced, so malloc a new one and free that one
//  only failure mode is malloc failing

static stbi_uc stbi__compute_y(int r, int g, int b) {
  return (stbi_uc)(((r * 77) + (g * 150) + (29 * b)) >> 8);
}

//////////////////////////////////////////////////////////////////////////////
//
//  "baseline" JPEG/JFIF decoder
//
//    simple implementation
//      - doesn't support delayed output of y-dimension
//      - simple interface (only one output format: 8-bit interleaved RGB)
//      - doesn't try to recover corrupt jpegs
//      - doesn't allow partial loading, loading multiple at once
//      - still fast on x86 (copying globals into locals doesn't help x86)
//      - allocates lots of intermediate memory (full size of all components)
//        - non-interleaved case requires this anyway
//        - allows good upsampling (see next)
//    high-quality
//      - upsampled channels are bilinearly interpolated, even across blocks
//      - quality integer IDCT derived from IJG's 'slow'
//    performance
//      - fast huffman; reasonable integer IDCT
//      - some SIMD kernels for common paths on targets with SSE2/NEON
//      - uses a lot of intermediate memory, could cache poorly

// huffman decoding acceleration
#define FAST_BITS 9 // larger handles more cases; smaller stomps less cache

typedef struct {
  stbi_uc fast[1 << FAST_BITS];
  // weirdly, repacking this into AoS is a 10% speed loss, instead of a win
  stbi__uint16 code[256];
  stbi_uc values[256];
  stbi_uc size[257];
  unsigned int maxcode[18];
  int delta[17]; // old 'firstsymbol' - old 'firstcode'
} stbi__huffman;

typedef struct img_comp {
  int id;
  int h, v;
  int tq;
  int hd, ha;
  int dc_pred;

  int x, y, w2, h2;
  stbi_uc *data;
  void *raw_data, *raw_coeff;
  stbi_uc *linebuf;
  short *coeff;         // progressive only
  int coeff_w, coeff_h; // number of 8x8 coefficient blocks
} img_comp;

typedef struct {
  stbi__context *s;
  stbi__huffman huff_dc[4];
  stbi__huffman huff_ac[4];
  stbi__uint16 dequant[4][64];
  stbi__int16 fast_ac[4][1 << FAST_BITS];

  // sizes for components, interleaved MCUs
  int img_h_max, img_v_max;
  int img_mcu_x, img_mcu_y;
  int img_mcu_w, img_mcu_h;

  // definition of jpeg image component
  img_comp img_comp[4];

  stbi__uint32 code_buffer; // jpeg entropy-coded buffer
  int code_bits;            // number of valid bits
  unsigned char marker;     // marker seen while filling entropy buffer
  int more;                 // flag if we saw a marker so must stop

  int progressive;
  int spec_start;
  int spec_end;
  int succ_high;
  int succ_low;
  int eob_run;
  int jfif;
  int app14_color_transform; // Adobe APP14 tag
  int rgb;

  int scan_n, order[4];
  int restart_interval, todo;
} stbi__jpeg;

static int stbi__build_huffman(stbi__huffman *h, int *count) {
  int i, j, k = 0;
  unsigned int code;
  // build size list for each symbol (from JPEG spec)
  for (i = 0; i < 16; ++i)
    for (j = 0; j < count[i]; ++j)
      h->size[k++] = (stbi_uc)(i + 1);
  h->size[k] = 0;

  // compute actual symbols (from jpeg spec)
  code = 0;
  k = 0;
  for (j = 1; j <= 16; ++j) {
    // compute delta to add to code to compute symbol id
    h->delta[j] = k - code;
    if (h->size[k] == j) {
      while (h->size[k] == j)
        h->code[k++] = (stbi__uint16)(code++);
      if (code - 1 >= (1u << j))
        return stbi__err("bad code lengths", "Corrupt JPEG");
    }
    // compute largest code + 1 for this size, preshifted as needed later
    h->maxcode[j] = code << (16 - j);
    code <<= 1;
  }
  h->maxcode[j] = 0xffffffff;

  // build non-spec acceleration table; 255 is flag for not-accelerated
  memset(h->fast, 255, 1 << FAST_BITS);
  for (i = 0; i < k; ++i) {
    int s = h->size[i];
    if (s <= FAST_BITS) {
      int c = h->code[i] << (FAST_BITS - s);
      int m = 1 << (FAST_BITS - s);
      for (j = 0; j < m; ++j) {
        h->fast[c + j] = (stbi_uc)i;
      }
    }
  }
  return 1;
}

// build a table that decodes both magnitude and value of small ACs in
// one go.
static void stbi__build_fast_ac(stbi__int16 *fast_ac, stbi__huffman *h) {
  int i;
  for (i = 0; i < (1 << FAST_BITS); ++i) {
    stbi_uc fast = h->fast[i];
    fast_ac[i] = 0;
    if (fast < 255) {
      int rs = h->values[fast];
      int run = (rs >> 4) & 15;
      int magbits = rs & 15;
      int len = h->size[fast];

      if (magbits && len + magbits <= FAST_BITS) {
        // magnitude code followed by receive_extend code
        int k = ((i << len) & ((1 << FAST_BITS) - 1)) >> (FAST_BITS - magbits);
        int m = 1 << (magbits - 1);
        if (k < m)
          k += (~0U << magbits) + 1;
        // if the result is small enough, we can fit it in fast_ac table
        if (k >= -128 && k <= 127)
          fast_ac[i] = (stbi__int16)((k * 256) + (run * 16) + (len + magbits));
      }
    }
  }
}

static void stbi__grow_buffer_unsafe(stbi__jpeg *j) {
  do {
    unsigned int b = j->more ? stbi__peep8(j->s) : 0;
    j->s->img_buffer -= j->more;
    if (b == 0xff) {
      int c = stbi__get8(j->s);
      while (c == 0xff)
        c = stbi__get8(j->s); // consume fill bytes
      if (c != 0) {
        j->marker = (unsigned char)c;
        j->more = 0;
        return;
      }
    }
    j->code_buffer |= b << (24 - j->code_bits);
    j->code_bits += 8;
  } while (j->code_bits <= 24);
}

// decode a jpeg huffman value from the bitstream
stbi_inline static int stbi__jpeg_huff_decode(stbi__jpeg *j, stbi__huffman *h) {
  unsigned int temp;
  int c, k;

  if (j->code_bits < 16)
    stbi__grow_buffer_unsafe(j);

  // look at the top FAST_BITS and determine what symbol ID it is,
  // if the code is <= FAST_BITS
  c = (j->code_buffer >> (32 - FAST_BITS)) & ((1 << FAST_BITS) - 1);
  k = h->fast[c];
  if (k < 255) {
    int s = h->size[k];
    if (s > j->code_bits)
      return -1;
    j->code_buffer <<= s;
    j->code_bits -= s;
    return h->values[k];
  }

  // naive test is to shift the code_buffer down so k bits are
  // valid, then test against maxcode. To speed this up, we've
  // preshifted maxcode left so that it has (16-k) 0s at the
  // end; in other words, regardless of the number of bits, it
  // wants to be compared against something shifted to have 16;
  // that way we don't need to shift inside the loop.
  temp = j->code_buffer >> 16;
  for (k = FAST_BITS + 1;; ++k)
    if (temp < h->maxcode[k])
      break;
  if (k == 17) {
    // error! code not found
    j->code_bits -= 16;
    return -1;
  }

  if (k > j->code_bits)
    return -1;

  // convert the huffman code to the symbol id
  c = (j->code_buffer >> (32 - k)) + h->delta[k];
  STBI_ASSERT((j->code_buffer >> (32 - h->size[c])) == h->code[c]);

  // convert the id to a symbol
  j->code_bits -= k;
  j->code_buffer <<= k;
  return h->values[c];
}

// bias[n] = (-1<<n) + 1
static const int stbi__jbias[16] = {0,    -1,   -3,    -7,    -15,   -31,   -63,    -127,
                                    -255, -511, -1023, -2047, -4095, -8191, -16383, -32767};

// combined JPEG 'receive' and JPEG 'extend', since baseline
// always extends everything it receives.
stbi_inline static int stbi__extend_receive(stbi__jpeg *j, int n) {
  unsigned int k;
  int sgn;
  if (j->code_bits < n)
    stbi__grow_buffer_unsafe(j);

  sgn = (stbi__int32)j->code_buffer >> 31; // sign bit is always in MSB
  k = j->code_buffer >> (32 - n);
  j->code_buffer = j->code_buffer << n;
  j->code_bits -= n;
  return k + (stbi__jbias[n] & ~sgn);
}

// get some unsigned bits
stbi_inline static int stbi__jpeg_get_bits(stbi__jpeg *j, int n) {
  unsigned int k;
  if (j->code_bits < n)
    stbi__grow_buffer_unsafe(j);
  k = j->code_buffer >> (32 - n);
  j->code_buffer = j->code_buffer << n;
  j->code_bits -= n;
  return k;
}

stbi_inline static int stbi__jpeg_get_bit(stbi__jpeg *j) {
  unsigned int k;
  if (j->code_bits < 1)
    stbi__grow_buffer_unsafe(j);
  k = j->code_buffer;
  j->code_buffer <<= 1;
  --j->code_bits;
  return k & 0x80000000;
}

// given a value that's at position X in the zigzag stream,
// where does it appear in the 8x8 matrix coded as row-major?
static const stbi_uc stbi__jpeg_dezigzag[64 + 15] = {0, 1, 8, 16, 9, 2, 3, 10, 17, 24, 32, 25, 18, 11, 4, 5, 12, 19, 26,
                                                     33, 40, 48, 41, 34, 27, 20, 13, 6, 7, 14, 21, 28, 35, 42, 49, 56,
                                                     57, 50, 43, 36, 29, 22, 15, 23, 30, 37, 44, 51, 58, 59, 52, 45, 38,
                                                     31, 39, 46, 53, 60, 61, 54, 47, 55, 62, 63,
                                                     // let corrupt input sample past end
                                                     63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63};

// decode one 64-entry block--
static int stbi__jpeg_decode_block(stbi__jpeg *j, short data[64], stbi__huffman *hdc, stbi__huffman *hac,
                                   stbi__int16 *fac, int b, stbi__uint16 *dequant) {
  int diff, dc, k;
  int t;

  if (j->code_bits < 16)
    stbi__grow_buffer_unsafe(j);
  t = stbi__jpeg_huff_decode(j, hdc);
  if (t < 0)
    return stbi__err("bad huffman code", "Corrupt JPEG");

  // 0 all the ac values now so we can do it 32-bits at a time
  memset(data, 0, 64 * sizeof(data[0]));

  diff = t ? stbi__extend_receive(j, t) : 0;
  dc = j->img_comp[b].dc_pred + diff;
  j->img_comp[b].dc_pred = dc;
  data[0] = (short)(dc * dequant[0]);

  // decode AC components, see JPEG spec
  k = 1;
  do {
    unsigned int zig;
    int c, r, s;
    if (j->code_bits < 16)
      stbi__grow_buffer_unsafe(j);
    c = j->code_buffer >> (32 - FAST_BITS);
    r = fac[c];
    if (r) {              // fast-AC path
      k += (r >> 4) & 15; // run
      s = r & 15;         // combined length
      j->code_buffer <<= s;
      j->code_bits -= s;
      // decode into unzigzag'd location
      zig = stbi__jpeg_dezigzag[k++];
      data[zig] = (short)((r >> 8) * dequant[zig]);
    } else {
      int rs = stbi__jpeg_huff_decode(j, hac);
      if (rs < 0)
        return stbi__err("bad huffman code", "Corrupt JPEG");
      s = rs & 15;
      r = rs >> 4;
      if (s == 0) {
        if (rs != 0xf0)
          break; // end block
        k += 16;
      } else {
        k += r;
        // decode into unzigzag'd location
        zig = stbi__jpeg_dezigzag[k++];
        data[zig] = (short)(stbi__extend_receive(j, s) * dequant[zig]);
      }
    }
  } while (k < 64);
  return 1;
}

static int stbi__jpeg_decode_block_prog_dc(stbi__jpeg *j, short data[64], stbi__huffman *hdc, int b) {
  int diff, dc;
  int t;
  if (j->spec_end != 0)
    return stbi__err("can't merge dc and ac", "Corrupt JPEG");

  if (j->code_bits < 16)
    stbi__grow_buffer_unsafe(j);

  if (j->succ_high == 0) {
    // first scan for DC coefficient, must be first
    memset(data, 0, 64 * sizeof(data[0])); // 0 all the ac values now
    t = stbi__jpeg_huff_decode(j, hdc);
    if (t == -1)
      return stbi__err("can't merge dc and ac", "Corrupt JPEG");
    diff = t ? stbi__extend_receive(j, t) : 0;

    dc = j->img_comp[b].dc_pred + diff;
    j->img_comp[b].dc_pred = dc;
    data[0] = (short)(dc << j->succ_low);
  } else {
    // refinement scan for DC coefficient
    if (stbi__jpeg_get_bit(j))
      data[0] += (short)(1 << j->succ_low);
  }
  return 1;
}

// @OPTIMIZE: store non-zigzagged during the decode passes,
// and only de-zigzag when dequantizing
static int stbi__jpeg_decode_block_prog_ac(stbi__jpeg *j, short data[64], stbi__huffman *hac, stbi__int16 *fac) {
  int k;
  if (j->spec_start == 0)
    return stbi__err("can't merge dc and ac", "Corrupt JPEG");

  if (j->succ_high == 0) {
    int shift = j->succ_low;

    if (j->eob_run) {
      --j->eob_run;
      return 1;
    }

    k = j->spec_start;
    do {
      unsigned int zig;
      int c, r, s;
      if (j->code_bits < 16)
        stbi__grow_buffer_unsafe(j);
      c = (j->code_buffer >> (32 - FAST_BITS)) & ((1 << FAST_BITS) - 1);
      r = fac[c];
      if (r) {              // fast-AC path
        k += (r >> 4) & 15; // run
        s = r & 15;         // combined length
        j->code_buffer <<= s;
        j->code_bits -= s;
        zig = stbi__jpeg_dezigzag[k++];
        data[zig] = (short)((r >> 8) << shift);
      } else {
        int rs = stbi__jpeg_huff_decode(j, hac);
        if (rs < 0)
          return stbi__err("bad huffman code", "Corrupt JPEG");
        s = rs & 15;
        r = rs >> 4;
        if (s == 0) {
          if (r < 15) {
            j->eob_run = (1 << r);
            if (r)
              j->eob_run += stbi__jpeg_get_bits(j, r);
            --j->eob_run;
            break;
          }
          k += 16;
        } else {
          k += r;
          zig = stbi__jpeg_dezigzag[k++];
          data[zig] = (short)(stbi__extend_receive(j, s) << shift);
        }
      }
    } while (k <= j->spec_end);
  } else {
    // refinement scan for these AC coefficients

    short bit = (short)(1 << j->succ_low);

    if (j->eob_run) {
      --j->eob_run;
      for (k = j->spec_start; k <= j->spec_end; ++k) {
        short *p = &data[stbi__jpeg_dezigzag[k]];
        if (*p != 0)
          if (stbi__jpeg_get_bit(j))
            if ((*p & bit) == 0) {
              if (*p > 0)
                *p += bit;
              else
                *p -= bit;
            }
      }
    } else {
      k = j->spec_start;
      do {
        int r, s;
        int rs = stbi__jpeg_huff_decode(
            j, hac); // @OPTIMIZE see if we can use the fast path here, advance-by-r is so slow, eh
        if (rs < 0)
          return stbi__err("bad huffman code", "Corrupt JPEG");
        s = rs & 15;
        r = rs >> 4;
        if (s == 0) {
          if (r < 15) {
            j->eob_run = (1 << r) - 1;
            if (r)
              j->eob_run += stbi__jpeg_get_bits(j, r);
            r = 64; // force end of block
          } else {
            // r=15 s=0 should write 16 0s, so we just do
            // a run of 15 0s and then write s (which is 0),
            // so we don't have to do anything special here
          }
        } else {
          if (s != 1)
            return stbi__err("bad huffman code", "Corrupt JPEG");
          // sign bit
          if (stbi__jpeg_get_bit(j))
            s = bit;
          else
            s = -bit;
        }

        // advance by r
        while (k <= j->spec_end) {
          short *p = &data[stbi__jpeg_dezigzag[k++]];
          if (*p != 0) {
            if (stbi__jpeg_get_bit(j))
              if ((*p & bit) == 0) {
                if (*p > 0)
                  *p += bit;
                else
                  *p -= bit;
              }
          } else {
            if (r == 0) {
              *p = (short)s;
              break;
            }
            --r;
          }
        }
      } while (k <= j->spec_end);
    }
  }
  return 1;
}

// take a -128..127 value and stbi__clamp it and convert to 0..255
stbi_inline static stbi_uc stbi__clamp(int x) {
  // trick to use a single test to catch both cases
#if 0
   if ((unsigned int) x > 255) {
      if (x < 0) return 0;
      if (x > 255) return 255;
   }
   return (stbi_uc) x;
#else
  if ((unsigned)x <= 255)
    return x;
  return ((unsigned)x >> 31) + 255;
#endif
}

#define stbi__f2f(x) ((int)(((x) * 4096 + 0.5)))
#define stbi__fsh(x) ((x) * 4096)

#define stbi__f2f_0p5411961    ((int)0x000008a9)
#define stbi__f2f_n1p847759065 ((int)0xffffe271)
#define stbi__f2f_0p765366865  ((int)0x00000c3f)
#define stbi__f2f_1p175875602  ((int)0x000012d0)
#define stbi__f2f_0p298631336  ((int)0x000004c7)
#define stbi__f2f_2p053119869  ((int)0x000020da)
#define stbi__f2f_3p072711026  ((int)0x0000312a)
#define stbi__f2f_1p501321110  ((int)0x00001805)
#define stbi__f2f_n0p899976223 ((int)0xfffff19b)
#define stbi__f2f_n2p562915447 ((int)0xffffd6ff)
#define stbi__f2f_n1p961570560 ((int)0xffffe09e)
#define stbi__f2f_n0p390180644 ((int)0xfffff9c3)

// derived from jidctint -- DCT_ISLOW
#define STBI__IDCT_1D(s0, s1, s2, s3, s4, s5, s6, s7)     \
  int t0, t1, t2, t3, p1, p2, p3, p4, p5, x0, x1, x2, x3; \
  p2 = s2;                                                \
  p3 = s6;                                                \
  p1 = (p2 + p3) * stbi__f2f_0p5411961;                   \
  t2 = p1 + p3 * stbi__f2f_n1p847759065;                  \
  t3 = p1 + p2 * stbi__f2f_0p765366865;                   \
  p2 = s0;                                                \
  p3 = s4;                                                \
  t0 = stbi__fsh(p2 + p3);                                \
  t1 = stbi__fsh(p2 - p3);                                \
  x0 = t0 + t3;                                           \
  x3 = t0 - t3;                                           \
  x1 = t1 + t2;                                           \
  x2 = t1 - t2;                                           \
  t0 = s7;                                                \
  t1 = s5;                                                \
  t2 = s3;                                                \
  t3 = s1;                                                \
  p3 = t0 + t2;                                           \
  p4 = t1 + t3;                                           \
  p1 = t0 + t3;                                           \
  p2 = t1 + t2;                                           \
  p5 = (p3 + p4) * stbi__f2f_1p175875602;                 \
  t0 = t0 * stbi__f2f_0p298631336;                        \
  t1 = t1 * stbi__f2f_2p053119869;                        \
  t2 = t2 * stbi__f2f_3p072711026;                        \
  t3 = t3 * stbi__f2f_1p501321110;                        \
  p1 = p5 + p1 * stbi__f2f_n0p899976223;                  \
  p2 = p5 + p2 * stbi__f2f_n2p562915447;                  \
  p3 = p3 * stbi__f2f_n1p961570560;                       \
  p4 = p4 * stbi__f2f_n0p390180644;                       \
  t3 += p1 + p4;                                          \
  t2 += p2 + p3;                                          \
  t1 += p2 + p4;                                          \
  t0 += p1 + p3;

static void stbi__idct_block(stbi_uc *out, int out_stride, short data[64]) {
  int i, val[64], *v = val;
  stbi_uc *o;
  short *d = data;

  // columns
  for (i = 0; i < 8; ++i, ++d, ++v) {
    // if all zeroes, shortcut -- this avoids dequantizing 0s and IDCTing
    if (d[8] == 0 && d[16] == 0 && d[24] == 0 && d[32] == 0 && d[40] == 0 && d[48] == 0 && d[56] == 0) {
      //    no shortcut                 0     seconds
      //    (1|2|3|4|5|6|7)==0          0     seconds
      //    all separate               -0.047 seconds
      //    1 && 2|3 && 4|5 && 6|7:    -0.047 seconds
      int dcterm = d[0] * 4;
      v[0] = v[8] = v[16] = v[24] = v[32] = v[40] = v[48] = v[56] = dcterm;
    } else {
      STBI__IDCT_1D(d[0], d[8], d[16], d[24], d[32], d[40], d[48], d[56])
      // constants scaled things up by 1<<12; let's bring them back
      // down, but keep 2 extra bits of precision
      x0 += 512;
      x1 += 512;
      x2 += 512;
      x3 += 512;
      v[0] = (x0 + t3) >> 10;
      v[56] = (x0 - t3) >> 10;
      v[8] = (x1 + t2) >> 10;
      v[48] = (x1 - t2) >> 10;
      v[16] = (x2 + t1) >> 10;
      v[40] = (x2 - t1) >> 10;
      v[24] = (x3 + t0) >> 10;
      v[32] = (x3 - t0) >> 10;
    }
  }

  for (i = 0, v = val, o = out; i < 8; ++i, v += 8, o += out_stride) {
    // no fast case since the first 1D IDCT spread components out
    STBI__IDCT_1D(v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7])
    // constants scaled things up by 1<<12, plus we had 1<<2 from first
    // loop, plus horizontal and vertical each scale by sqrt(8) so together
    // we've got an extra 1<<3, so 1<<17 total we need to remove.
    // so we want to round that, which means adding 0.5 * 1<<17,
    // aka 65536. Also, we'll end up with -128 to 127 that we want
    // to encode as 0..255 by adding 128, so we'll add that before the shift
    x0 += 65536 + (128 << 17);
    x1 += 65536 + (128 << 17);
    x2 += 65536 + (128 << 17);
    x3 += 65536 + (128 << 17);
    // tried computing the shifts into temps, or'ing the temps to see
    // if any were out of range, but that was slower
    o[0] = stbi__clamp((x0 + t3) >> 17);
    o[7] = stbi__clamp((x0 - t3) >> 17);
    o[1] = stbi__clamp((x1 + t2) >> 17);
    o[6] = stbi__clamp((x1 - t2) >> 17);
    o[2] = stbi__clamp((x2 + t1) >> 17);
    o[5] = stbi__clamp((x2 - t1) >> 17);
    o[3] = stbi__clamp((x3 + t0) >> 17);
    o[4] = stbi__clamp((x3 - t0) >> 17);
  }
}

#define STBI__MARKER_none 0xff
// if there's a pending marker from the entropy stream, return that
// otherwise, fetch from the stream and get a marker. if there's no
// marker, return 0xff, which is never a valid marker value
static stbi_uc stbi__get_marker(stbi__jpeg *j) {
  stbi_uc x;
  if (j->marker != STBI__MARKER_none) {
    x = j->marker;
    j->marker = STBI__MARKER_none;
    return x;
  }
  x = stbi__get8(j->s);
  if (x != 0xff)
    return STBI__MARKER_none;
  while (x == 0xff)
    x = stbi__get8(j->s); // consume repeated 0xff fill bytes
  return x;
}

// in each scan, we'll have scan_n components, and the order
// of the components is specified by order[]
#define STBI__RESTART(x) ((x) >= 0xd0 && (x) <= 0xd7)

// after a restart interval, stbi__jpeg_reset the entropy decoder and
// the dc prediction
static void stbi__jpeg_reset(stbi__jpeg *j) {
  j->code_bits = 0;
  j->code_buffer = 0;
  j->more = 0xffffffff;
  j->img_comp[0].dc_pred = j->img_comp[1].dc_pred = j->img_comp[2].dc_pred = j->img_comp[3].dc_pred = 0;
  j->marker = STBI__MARKER_none;
  j->todo = j->restart_interval ? j->restart_interval : 0x7fffffff;
  j->eob_run = 0;
  // no more than 1<<31 MCUs if no restart_interal? that's plenty safe,
  // since we don't even allow 1<<30 pixels
}

static int stbi__parse_entropy_coded_data(stbi__jpeg *z) {
  stbi__jpeg_reset(z);
  if (!z->progressive) {
    if (z->scan_n == 1) {
      int i, j;
      STBI_SIMD_ALIGN(short, data[64]);
      int n = z->order[0];
      // non-interleaved data, we just need to process one block at a time,
      // in trivial scanline order
      // number of blocks to do just depends on how many actual "pixels" this
      // component has, independent of interleaved MCU blocking and such
      int w = (z->img_comp[n].x + 7) >> 3;
      int h = (z->img_comp[n].y + 7) >> 3;
      for (j = 0; j < h; ++j) {
        for (i = 0; i < w; ++i) {
          int ha = z->img_comp[n].ha;
          if (!stbi__jpeg_decode_block(z, data, z->huff_dc + z->img_comp[n].hd, z->huff_ac + ha, z->fast_ac[ha], n,
                                       z->dequant[z->img_comp[n].tq]))
            return 0;
          stbi__idct_block(z->img_comp[n].data + z->img_comp[n].w2 * j * 8 + i * 8, z->img_comp[n].w2, data);
          // every data block is an MCU, so countdown the restart interval
          if (--z->todo <= 0) {
            if (z->code_bits < 24)
              stbi__grow_buffer_unsafe(z);
            // if it's NOT a restart, then just bail, so we get corrupt data
            // rather than no data
            if (!STBI__RESTART(z->marker))
              return 1;
            stbi__jpeg_reset(z);
          }
        }
      }
      return 1;
    } else { // interleaved
      int i, j, k, x, y;
      STBI_SIMD_ALIGN(short, data[64]);
      for (j = 0; j < z->img_mcu_y; ++j) {
        for (i = 0; i < z->img_mcu_x; ++i) {
          // scan an interleaved mcu... process scan_n components in order
          for (k = 0; k < z->scan_n; ++k) {
            int n = z->order[k];
            img_comp *comp = &z->img_comp[n];
            int ha = comp->ha;
            int h = comp->h;
            int v = comp->v;
            int w2 = comp->w2;
            int w2_8 = w2 * 8;
            stbi_uc *data_ptr = comp->data + w2_8 * j * v + i * h * 8;
            stbi__huffman *hdc = z->huff_dc + comp->hd;
            stbi__huffman *hac = z->huff_ac + ha;
            stbi__int16 *fac = z->fast_ac[ha];
            stbi__uint16 *dequant = z->dequant[comp->tq];
            // scan out an mcu's worth of this component; that's just determined
            // by the basic H and V specified for the component
            for (y = 0; y < v; ++y) {
              for (x = 0; x < h; ++x) {
                int x2 = x * 8;
                if (!stbi__jpeg_decode_block(z, data, hdc, hac, fac, n, dequant))
                  return 0;
                stbi__idct_block(data_ptr + x2, w2, data);
              }
              data_ptr += w2_8;
            }
          }
          // after all interleaved components, that's an interleaved MCU,
          // so now count down the restart interval
          if (--z->todo <= 0) {
            if (z->code_bits < 24)
              stbi__grow_buffer_unsafe(z);
            if (!STBI__RESTART(z->marker))
              return 1;
            stbi__jpeg_reset(z);
          }
        }
      }
      return 1;
    }
  } else {
    if (z->scan_n == 1) {
      int i, j;
      int n = z->order[0];
      // non-interleaved data, we just need to process one block at a time,
      // in trivial scanline order
      // number of blocks to do just depends on how many actual "pixels" this
      // component has, independent of interleaved MCU blocking and such
      int w = (z->img_comp[n].x + 7) >> 3;
      int h = (z->img_comp[n].y + 7) >> 3;
      for (j = 0; j < h; ++j) {
        for (i = 0; i < w; ++i) {
          short *data = z->img_comp[n].coeff + 64 * (i + j * z->img_comp[n].coeff_w);
          if (z->spec_start == 0) {
            if (!stbi__jpeg_decode_block_prog_dc(z, data, &z->huff_dc[z->img_comp[n].hd], n))
              return 0;
          } else {
            int ha = z->img_comp[n].ha;
            if (!stbi__jpeg_decode_block_prog_ac(z, data, &z->huff_ac[ha], z->fast_ac[ha]))
              return 0;
          }
          // every data block is an MCU, so countdown the restart interval
          if (--z->todo <= 0) {
            if (z->code_bits < 24)
              stbi__grow_buffer_unsafe(z);
            if (!STBI__RESTART(z->marker))
              return 1;
            stbi__jpeg_reset(z);
          }
        }
      }
      return 1;
    } else { // interleaved
      int i, j, k, x, y;
      for (j = 0; j < z->img_mcu_y; ++j) {
        for (i = 0; i < z->img_mcu_x; ++i) {
          // scan an interleaved mcu... process scan_n components in order
          for (k = 0; k < z->scan_n; ++k) {
            int n = z->order[k];
            // scan out an mcu's worth of this component; that's just determined
            // by the basic H and V specified for the component
            for (y = 0; y < z->img_comp[n].v; ++y) {
              for (x = 0; x < z->img_comp[n].h; ++x) {
                int x2 = (i * z->img_comp[n].h + x);
                int y2 = (j * z->img_comp[n].v + y);
                short *data = z->img_comp[n].coeff + 64 * (x2 + y2 * z->img_comp[n].coeff_w);
                if (!stbi__jpeg_decode_block_prog_dc(z, data, &z->huff_dc[z->img_comp[n].hd], n))
                  return 0;
              }
            }
          }
          // after all interleaved components, that's an interleaved MCU,
          // so now count down the restart interval
          if (--z->todo <= 0) {
            if (z->code_bits < 24)
              stbi__grow_buffer_unsafe(z);
            if (!STBI__RESTART(z->marker))
              return 1;
            stbi__jpeg_reset(z);
          }
        }
      }
      return 1;
    }
  }
}

static void stbi__jpeg_dequantize(short *data, stbi__uint16 *dequant) {
  int i;
  for (i = 0; i < 64; ++i)
    data[i] *= dequant[i];
}

static void stbi__jpeg_finish(stbi__jpeg *z) {
  if (z->progressive) {
    // dequantize and idct the data
    int i, j, n;
    for (n = 0; n < z->s->img_n; ++n) {
      int w = (z->img_comp[n].x + 7) >> 3;
      int h = (z->img_comp[n].y + 7) >> 3;
      for (j = 0; j < h; ++j) {
        for (i = 0; i < w; ++i) {
          short *data = z->img_comp[n].coeff + 64 * (i + j * z->img_comp[n].coeff_w);
          stbi__jpeg_dequantize(data, z->dequant[z->img_comp[n].tq]);
          stbi__idct_block(z->img_comp[n].data + z->img_comp[n].w2 * j * 8 + i * 8, z->img_comp[n].w2, data);
        }
      }
    }
  }
}

static int stbi__process_marker(stbi__jpeg *z, int m) {
  int L;
  switch (m) {
    case STBI__MARKER_none: // no marker found
      return stbi__err("expected marker", "Corrupt JPEG");

    case 0xDD: // DRI - specify restart interval
      if (stbi__get16be(z->s) != 4)
        return stbi__err("bad DRI len", "Corrupt JPEG");
      z->restart_interval = stbi__get16be(z->s);
      return 1;

    case 0xDB: // DQT - define quantization table
      L = stbi__get16be(z->s) - 2;
      while (L > 0) {
        int q = stbi__get8(z->s);
        int p = q >> 4, sixteen = (p != 0);
        int t = q & 15, i;
        if (p != 0 && p != 1)
          return stbi__err("bad DQT type", "Corrupt JPEG");
        if (t > 3)
          return stbi__err("bad DQT table", "Corrupt JPEG");

        for (i = 0; i < 64; ++i)
          z->dequant[t][stbi__jpeg_dezigzag[i]] = (stbi__uint16)(sixteen ? stbi__get16be(z->s) : stbi__get8(z->s));
        L -= (sixteen ? 129 : 65);
      }
      return L == 0;

    case 0xC4: // DHT - define huffman table
      L = stbi__get16be(z->s) - 2;
      while (L > 0) {
        stbi_uc *v;
        int sizes[16], i, n = 0;
        int q = stbi__get8(z->s);
        int tc = q >> 4;
        int th = q & 15;
        if (tc > 1 || th > 3)
          return stbi__err("bad DHT header", "Corrupt JPEG");
        for (i = 0; i < 16; ++i) {
          sizes[i] = stbi__get8(z->s);
          n += sizes[i];
        }
        L -= 17;
        if (tc == 0) {
          if (!stbi__build_huffman(z->huff_dc + th, sizes))
            return 0;
          v = z->huff_dc[th].values;
        } else {
          if (!stbi__build_huffman(z->huff_ac + th, sizes))
            return 0;
          v = z->huff_ac[th].values;
        }
        for (i = 0; i < n; ++i)
          v[i] = stbi__get8(z->s);
        if (tc != 0)
          stbi__build_fast_ac(z->fast_ac[th], z->huff_ac + th);
        L -= n;
      }
      return L == 0;
  }

  // check for comment block or APP blocks
  if ((m >= 0xE0 && m <= 0xEF) || m == 0xFE) {
    L = stbi__get16be(z->s);
    if (L < 2) {
      if (m == 0xFE)
        return stbi__err("bad COM len", "Corrupt JPEG");
      else
        return stbi__err("bad APP len", "Corrupt JPEG");
    }
    L -= 2;

    if (m == 0xE0 && L >= 5) { // JFIF APP0 segment
      static const unsigned char tag[5] = {'J', 'F', 'I', 'F', '\0'};
      int ok = 1;
      int i;
      for (i = 0; i < 5; ++i)
        if (stbi__get8(z->s) != tag[i])
          ok = 0;
      L -= 5;
      if (ok)
        z->jfif = 1;
    } else if (m == 0xEE && L >= 12) { // Adobe APP14 segment
      static const unsigned char tag[6] = {'A', 'd', 'o', 'b', 'e', '\0'};
      int ok = 1;
      int i;
      for (i = 0; i < 6; ++i)
        if (stbi__get8(z->s) != tag[i])
          ok = 0;
      L -= 6;
      if (ok) {
        stbi__get8(z->s);                            // version
        stbi__get16be(z->s);                         // flags0
        stbi__get16be(z->s);                         // flags1
        z->app14_color_transform = stbi__get8(z->s); // color transform
        L -= 6;
      }
    }

    stbi__skip(z->s, L);
    return 1;
  }

  return stbi__err("unknown marker", "Corrupt JPEG");
}

// after we see SOS
static int stbi__process_scan_header(stbi__jpeg *z) {
  int i;
  int Ls = stbi__get16be(z->s);
  z->scan_n = stbi__get8(z->s);
  if (z->scan_n < 1 || z->scan_n > 4 || z->scan_n > (int)z->s->img_n)
    return stbi__err("bad SOS component count", "Corrupt JPEG");
  if (Ls != 6 + 2 * z->scan_n)
    return stbi__err("bad SOS len", "Corrupt JPEG");
  for (i = 0; i < z->scan_n; ++i) {
    int id = stbi__get8(z->s), which;
    int q = stbi__get8(z->s);
    for (which = 0; which < z->s->img_n; ++which)
      if (z->img_comp[which].id == id)
        break;
    if (which == z->s->img_n)
      return 0; // no match
    z->img_comp[which].hd = q >> 4;
    if (z->img_comp[which].hd > 3)
      return stbi__err("bad DC huff", "Corrupt JPEG");
    z->img_comp[which].ha = q & 15;
    if (z->img_comp[which].ha > 3)
      return stbi__err("bad AC huff", "Corrupt JPEG");
    z->order[i] = which;
  }

  {
    int aa;
    z->spec_start = stbi__get8(z->s);
    z->spec_end = stbi__get8(z->s); // should be 63, but might be 0
    aa = stbi__get8(z->s);
    z->succ_high = (aa >> 4);
    z->succ_low = (aa & 15);
    if (z->progressive) {
      if (z->spec_start > 63 || z->spec_end > 63 || z->spec_start > z->spec_end || z->succ_high > 13 ||
          z->succ_low > 13)
        return stbi__err("bad SOS", "Corrupt JPEG");
    } else {
      if (z->spec_start != 0)
        return stbi__err("bad SOS", "Corrupt JPEG");
      if (z->succ_high != 0 || z->succ_low != 0)
        return stbi__err("bad SOS", "Corrupt JPEG");
      z->spec_end = 63;
    }
  }

  return 1;
}

static int stbi__free_jpeg_components(stbi__jpeg *z, int ncomp, int why) {
  int i;
  for (i = 0; i < ncomp; ++i) {
    if (z->img_comp[i].raw_data) {
      STBI_FREE(z->img_comp[i].raw_data);
      z->img_comp[i].raw_data = NULL;
      z->img_comp[i].data = NULL;
    }
    if (z->img_comp[i].raw_coeff) {
      STBI_FREE(z->img_comp[i].raw_coeff);
      z->img_comp[i].raw_coeff = 0;
      z->img_comp[i].coeff = 0;
    }
    if (z->img_comp[i].linebuf) {
      STBI_FREE(z->img_comp[i].linebuf);
      z->img_comp[i].linebuf = NULL;
    }
  }
  return why;
}

static int stbi__process_frame_header(stbi__jpeg *z, int scan) {
  stbi__context *s = z->s;
  int Lf, p, i, q, h_max = 1, v_max = 1, c;
  Lf = stbi__get16be(s);
  if (Lf < 11)
    return stbi__err("bad SOF len", "Corrupt JPEG"); // JPEG
  p = stbi__get8(s);
  if (p != 8)
    return stbi__err("only 8-bit", "JPEG format not supported: 8-bit only"); // JPEG baseline
  s->img_y = stbi__get16be(s);
  if (s->img_y == 0)
    return stbi__err(
        "no header height",
        "JPEG format not supported: delayed height"); // Legal, but we don't handle it--but neither does IJG
  s->img_x = stbi__get16be(s);
  if (s->img_x == 0)
    return stbi__err("0 width", "Corrupt JPEG"); // JPEG requires
  if (s->img_y > STBI_MAX_DIMENSIONS)
    return stbi__err("too large", "Very large image (corrupt?)");
  if (s->img_x > STBI_MAX_DIMENSIONS)
    return stbi__err("too large", "Very large image (corrupt?)");
  c = stbi__get8(s);
  if (c != 3 && c != 1 && c != 4)
    return stbi__err("bad component count", "Corrupt JPEG");
  s->img_n = c;
  for (i = 0; i < c; ++i) {
    z->img_comp[i].data = NULL;
    z->img_comp[i].linebuf = NULL;
  }

  if (Lf != 8 + 3 * s->img_n)
    return stbi__err("bad SOF len", "Corrupt JPEG");

  z->rgb = 0;
  for (i = 0; i < s->img_n; ++i) {
    static const unsigned char rgb[3] = {'R', 'G', 'B'};
    z->img_comp[i].id = stbi__get8(s);
    if (s->img_n == 3 && z->img_comp[i].id == rgb[i])
      ++z->rgb;
    q = stbi__get8(s);
    z->img_comp[i].h = (q >> 4);
    if (!z->img_comp[i].h || z->img_comp[i].h > 4)
      return stbi__err("bad H", "Corrupt JPEG");
    z->img_comp[i].v = q & 15;
    if (!z->img_comp[i].v || z->img_comp[i].v > 4)
      return stbi__err("bad V", "Corrupt JPEG");
    z->img_comp[i].tq = stbi__get8(s);
    if (z->img_comp[i].tq > 3)
      return stbi__err("bad TQ", "Corrupt JPEG");
  }

  if (scan != STBI__SCAN_load)
    return 1;

  if (!stbi__mad3sizes_valid(s->img_x, s->img_y, s->img_n, 0))
    return stbi__err("too large", "Image too large to decode");

  for (i = 0; i < s->img_n; ++i) {
    if (z->img_comp[i].h > h_max)
      h_max = z->img_comp[i].h;
    if (z->img_comp[i].v > v_max)
      v_max = z->img_comp[i].v;
  }

  // compute interleaved mcu info
  z->img_h_max = h_max;
  z->img_v_max = v_max;
  z->img_mcu_w = h_max * 8;
  z->img_mcu_h = v_max * 8;
  // these sizes can't be more than 17 bits
  z->img_mcu_x = (s->img_x + z->img_mcu_w - 1) / z->img_mcu_w;
  z->img_mcu_y = (s->img_y + z->img_mcu_h - 1) / z->img_mcu_h;

  for (i = 0; i < s->img_n; ++i) {
    // number of effective pixels (e.g. for non-interleaved MCU)
    z->img_comp[i].x = (s->img_x * z->img_comp[i].h + h_max - 1) / h_max;
    z->img_comp[i].y = (s->img_y * z->img_comp[i].v + v_max - 1) / v_max;
    // to simplify generation, we'll allocate enough memory to decode
    // the bogus oversized data from using interleaved MCUs and their
    // big blocks (e.g. a 16x16 iMCU on an image of width 33); we won't
    // discard the extra data until colorspace conversion
    //
    // img_mcu_x, img_mcu_y: <=17 bits; comp[i].h and .v are <=4 (checked earlier)
    // so these muls can't overflow with 32-bit ints (which we require)
    z->img_comp[i].w2 = z->img_mcu_x * z->img_comp[i].h * 8;
    z->img_comp[i].h2 = z->img_mcu_y * z->img_comp[i].v * 8;
    z->img_comp[i].coeff = 0;
    z->img_comp[i].raw_coeff = 0;
    z->img_comp[i].linebuf = NULL;
    z->img_comp[i].raw_data = stbi__malloc_mad2(z->img_comp[i].w2, z->img_comp[i].h2, 15);
    if (z->img_comp[i].raw_data == NULL)
      return stbi__free_jpeg_components(z, i + 1, stbi__err("outofmem", "Out of memory"));
    // align blocks for idct using mmx/sse
    z->img_comp[i].data = (stbi_uc *)(((size_t)z->img_comp[i].raw_data + 15) & ~15);
    if (z->progressive) {
      // w2, h2 are multiples of 8 (see above)
      z->img_comp[i].coeff_w = z->img_comp[i].w2 / 8;
      z->img_comp[i].coeff_h = z->img_comp[i].h2 / 8;
      z->img_comp[i].raw_coeff = stbi__malloc_mad3(z->img_comp[i].w2, z->img_comp[i].h2, sizeof(short), 15);
      if (z->img_comp[i].raw_coeff == NULL)
        return stbi__free_jpeg_components(z, i + 1, stbi__err("outofmem", "Out of memory"));
      z->img_comp[i].coeff = (short *)(((size_t)z->img_comp[i].raw_coeff + 15) & ~15);
    }
  }

  return 1;
}

// use comparisons since in some cases we handle more than one case (e.g. SOF)
#define stbi__DNL(x) ((x) == 0xdc)
#define stbi__SOI(x) ((x) == 0xd8)
#define stbi__EOI(x) ((x) == 0xd9)
#define stbi__SOF(x) ((x) == 0xc0 || (x) == 0xc1 || (x) == 0xc2)
#define stbi__SOS(x) ((x) == 0xda)

#define stbi__SOF_progressive(x) ((x) == 0xc2)

static int stbi__decode_jpeg_header(stbi__jpeg *z, int scan) {
  int m;
  z->jfif = 0;
  z->app14_color_transform = -1; // valid values are 0,1,2
  z->marker = STBI__MARKER_none; // initialize cached marker to empty
  m = stbi__get_marker(z);
  if (!stbi__SOI(m))
    return stbi__err("no SOI", "Corrupt JPEG");
  if (scan == STBI__SCAN_type)
    return 1;
  m = stbi__get_marker(z);
  while (!stbi__SOF(m)) {
    if (!stbi__process_marker(z, m))
      return 0;
    m = stbi__get_marker(z);
    while (m == STBI__MARKER_none) {
      // some files have extra padding after their blocks, so ok, we'll scan
      if (stbi__at_eof(z->s))
        return stbi__err("no SOF", "Corrupt JPEG");
      m = stbi__get_marker(z);
    }
  }
  z->progressive = stbi__SOF_progressive(m);
  if (!stbi__process_frame_header(z, scan))
    return 0;
  return 1;
}

// decode image to YCbCr format
static int stbi__decode_jpeg_image(stbi__jpeg *j) {
  int m;
  for (m = 0; m < 4; m++) {
    j->img_comp[m].raw_data = NULL;
    j->img_comp[m].raw_coeff = NULL;
  }
  j->restart_interval = 0;
  if (!stbi__decode_jpeg_header(j, STBI__SCAN_load))
    return 0;
  m = stbi__get_marker(j);
  while (!stbi__EOI(m)) {
    if (stbi__SOS(m)) {
      if (!stbi__process_scan_header(j))
        return 0;
      if (!stbi__parse_entropy_coded_data(j))
        return 0;
      if (j->marker == STBI__MARKER_none) {
        // handle 0s at the end of image data from IP Kamera 9060
        while (!stbi__at_eof(j->s)) {
          int x = stbi__get8(j->s);
          if (x == 255) {
            j->marker = stbi__get8(j->s);
            break;
          }
        }
        // if we reach eof without hitting a marker, stbi__get_marker() below will fail and we'll eventually return 0
      }
    } else if (stbi__DNL(m)) {
      int Ld = stbi__get16be(j->s);
      stbi__uint32 NL = stbi__get16be(j->s);
      if (Ld != 4)
        return stbi__err("bad DNL len", "Corrupt JPEG");
      if (NL != j->s->img_y)
        return stbi__err("bad DNL height", "Corrupt JPEG");
    } else {
      if (!stbi__process_marker(j, m))
        return 0;
    }
    m = stbi__get_marker(j);
  }
  if (j->progressive)
    stbi__jpeg_finish(j);
  return 1;
}

// static jfif-centered resampling (across block boundaries)

typedef stbi_uc *(*resample_row_func)(stbi_uc *out, stbi_uc *in0, stbi_uc *in1, int w, int hs);

#define stbi__div4(x) ((stbi_uc)((x) >> 2))

static stbi_uc *resample_row_1(stbi_uc *out, stbi_uc *in_near, stbi_uc *in_far, int w, int hs) {
  STBI_NOTUSED(out);
  STBI_NOTUSED(in_far);
  STBI_NOTUSED(w);
  STBI_NOTUSED(hs);
  return in_near;
}

static stbi_uc *stbi__resample_row_v_2(stbi_uc *out, stbi_uc *in_near, stbi_uc *in_far, int w, int hs) {
  // need to generate two samples vertically for every one in input
  int i;
  STBI_NOTUSED(hs);
  for (i = 0; i < w; ++i)
    out[i] = stbi__div4(3 * in_near[i] + in_far[i] + 2);
  return out;
}

static stbi_uc *stbi__resample_row_h_2(stbi_uc *out, stbi_uc *in_near, stbi_uc *in_far, int w, int hs) {
  // need to generate two samples horizontally for every one in input
  int i;
  stbi_uc *input = in_near;

  if (w == 1) {
    // if only one sample, can't do any interpolation
    out[0] = out[1] = input[0];
    return out;
  }

  out[0] = input[0];
  out[1] = stbi__div4(input[0] * 3 + input[1] + 2);
  for (i = 1; i < w - 1; ++i) {
    int n = 3 * input[i] + 2;
    out[i * 2 + 0] = stbi__div4(n + input[i - 1]);
    out[i * 2 + 1] = stbi__div4(n + input[i + 1]);
  }
  out[i * 2 + 0] = stbi__div4(input[w - 2] * 3 + input[w - 1] + 2);
  out[i * 2 + 1] = input[w - 1];

  STBI_NOTUSED(in_far);
  STBI_NOTUSED(hs);

  return out;
}

#define stbi__div16(x) ((stbi_uc)((x) >> 4))

static stbi_uc *stbi__resample_row_hv_2(stbi_uc *out, stbi_uc *in_near, stbi_uc *in_far, int w, int hs) {
  // need to generate 2x2 samples for every one in input
  int i, t0, t1;
  if (w == 1) {
    out[0] = out[1] = stbi__div4(3 * in_near[0] + in_far[0] + 2);
    return out;
  }

  t1 = 3 * in_near[0] + in_far[0];
  out[0] = stbi__div4(t1 + 2);
  for (i = 1; i < w; ++i) {
    t0 = t1;
    t1 = 3 * in_near[i] + in_far[i];
    out[i * 2 - 1] = stbi__div16(3 * t0 + t1 + 8);
    out[i * 2] = stbi__div16(3 * t1 + t0 + 8);
  }
  out[w * 2 - 1] = stbi__div4(t1 + 2);

  STBI_NOTUSED(hs);

  return out;
}

static stbi_uc *stbi__resample_row_generic(stbi_uc *out, stbi_uc *in_near, stbi_uc *in_far, int w, int hs) {
  // resample with nearest-neighbor
  int i, j;
  STBI_NOTUSED(in_far);
  for (i = 0; i < w; ++i)
    for (j = 0; j < hs; ++j)
      out[i * hs + j] = in_near[i];
  return out;
}

// this is a reduced-precision calculation of YCbCr-to-RGB introduced
// to make sure the code produces the same results in both SIMD and scalar
#define stbi__float2fixed(x) (((int)((x) * 4096.0f + 0.5f)) << 8)

#define stbi__float2fixed_1p40200 ((int)0x00166f00)
#define stbi__float2fixed_0p71414 ((int)0x000b6d00)
#define stbi__float2fixed_0p34414 ((int)0x00058200)
#define stbi__float2fixed_1p77200 ((int)0x001c5a00)
static void stbi__YCbCr_to_RGB_row(stbi_uc *out, const stbi_uc *y, const stbi_uc *pcb, const stbi_uc *pcr, int count,
                                   int step) {
  int i;
  for (i = 0; i < count; ++i) {
    int y_fixed = (y[i] << 20) + (1 << 19); // rounding
    int r, g, b;
    int cr = pcr[i] - 128;
    int cb = pcb[i] - 128;
    r = y_fixed + cr * stbi__float2fixed_1p40200;
    g = y_fixed + (cr * -stbi__float2fixed_0p71414) + ((cb * -stbi__float2fixed_0p34414) & 0xffff0000);
    b = y_fixed + cb * stbi__float2fixed_1p77200;
    r >>= 20;
    g >>= 20;
    b >>= 20;
    if ((unsigned)r > 255) {
      if (r < 0)
        r = 0;
      else
        r = 255;
    }
    if ((unsigned)g > 255) {
      if (g < 0)
        g = 0;
      else
        g = 255;
    }
    if ((unsigned)b > 255) {
      if (b < 0)
        b = 0;
      else
        b = 255;
    }
    out[0] = (stbi_uc)r;
    out[1] = (stbi_uc)g;
    out[2] = (stbi_uc)b;
    out[3] = 255;
    out += step;
  }
}

// clean up the temporary component buffers
static void stbi__cleanup_jpeg(stbi__jpeg *j) {
  stbi__free_jpeg_components(j, j->s->img_n, 0);
}

typedef struct {
  resample_row_func resample;
  stbi_uc *line0, *line1;
  int hs, vs;  // expansion factor in each axis
  int w_lores; // horizontal pixels pre-expansion
  int ystep;   // how far through vertical expansion we are
  int ypos;    // which pre-expansion row we're on
} stbi__resample;

// fast 0..255 * 0..255 => 0..255 rounded multiplication
static stbi_uc stbi__blinn_8x8(stbi_uc x, stbi_uc y) {
  unsigned int t = x * y + 128;
  return (stbi_uc)((t + (t >> 8)) >> 8);
}

static stbi_uc *load_jpeg_image(stbi__jpeg *z, int *out_x, int *out_y, int *comp, int req_comp) {
  int n, decode_n, is_rgb;
  z->s->img_n = 0; // make stbi__cleanup_jpeg safe

  // validate req_comp
  if (req_comp < 0 || req_comp > 4)
    return stbi__errpuc("bad req_comp", "Internal error");

  // load a jpeg image from whichever source, but leave in YCbCr format
  if (!stbi__decode_jpeg_image(z)) {
    stbi__cleanup_jpeg(z);
    return NULL;
  }

  // determine actual number of components to generate
  n = req_comp ? req_comp : z->s->img_n >= 3 ? 3 : 1;

  is_rgb = z->s->img_n == 3 && (z->rgb == 3 || (z->app14_color_transform == 0 && !z->jfif));

  if (z->s->img_n == 3 && n < 3 && !is_rgb)
    decode_n = 1;
  else
    decode_n = z->s->img_n;

  // resample and color-convert
  {
    int k;
    unsigned int i, j;
    stbi_uc *output;
    stbi_uc *coutput[4] = {NULL, NULL, NULL, NULL};

    stbi__resample res_comp[4];

    for (k = 0; k < decode_n; ++k) {
      stbi__resample *r = &res_comp[k];

      // allocate line buffer big enough for upsampling off the edges
      // with upsample factor of 4
      z->img_comp[k].linebuf = (stbi_uc *)stbi__malloc(z->s->img_x + 3);
      if (!z->img_comp[k].linebuf) {
        stbi__cleanup_jpeg(z);
        return stbi__errpuc("outofmem", "Out of memory");
      }

      r->hs = z->img_h_max / z->img_comp[k].h;
      r->vs = z->img_v_max / z->img_comp[k].v;
      r->ystep = r->vs >> 1;
      r->w_lores = (z->s->img_x + r->hs - 1) / r->hs;
      r->ypos = 0;
      r->line0 = r->line1 = z->img_comp[k].data;

      if (r->hs == 1 && r->vs == 1)
        r->resample = resample_row_1;
      else if (r->hs == 1 && r->vs == 2)
        r->resample = stbi__resample_row_v_2;
      else if (r->hs == 2 && r->vs == 1)
        r->resample = stbi__resample_row_h_2;
      else if (r->hs == 2 && r->vs == 2)
        r->resample = stbi__resample_row_hv_2;
      else
        r->resample = stbi__resample_row_generic;
    }

    // can't error after this so, this is safe
    output = (stbi_uc *)stbi__malloc_mad3(n, z->s->img_x, z->s->img_y, 1);
    if (!output) {
      stbi__cleanup_jpeg(z);
      return stbi__errpuc("outofmem", "Out of memory");
    }

    // now go ahead and resample
    for (j = 0; j < z->s->img_y; ++j) {
      stbi_uc *out = output + n * z->s->img_x * j;
      for (k = 0; k < decode_n; ++k) {
        stbi__resample *r = &res_comp[k];
        int y_bot = r->ystep >= (r->vs >> 1);
        coutput[k] = r->resample(z->img_comp[k].linebuf, y_bot ? r->line1 : r->line0, y_bot ? r->line0 : r->line1,
                                 r->w_lores, r->hs);
        if (++r->ystep >= r->vs) {
          r->ystep = 0;
          r->line0 = r->line1;
          if (++r->ypos < z->img_comp[k].y)
            r->line1 += z->img_comp[k].w2;
        }
      }
      if (n >= 3) {
        stbi_uc *y = coutput[0];
        if (z->s->img_n == 3) {
          if (is_rgb) {
            for (i = 0; i < z->s->img_x; ++i) {
              out[0] = y[i];
              out[1] = coutput[1][i];
              out[2] = coutput[2][i];
              out[3] = 255;
              out += n;
            }
          } else {
            stbi__YCbCr_to_RGB_row(out, y, coutput[1], coutput[2], z->s->img_x, n);
          }
        } else if (z->s->img_n == 4) {
          if (z->app14_color_transform == 0) { // CMYK
            for (i = 0; i < z->s->img_x; ++i) {
              stbi_uc m = coutput[3][i];
              out[0] = stbi__blinn_8x8(coutput[0][i], m);
              out[1] = stbi__blinn_8x8(coutput[1][i], m);
              out[2] = stbi__blinn_8x8(coutput[2][i], m);
              out[3] = 255;
              out += n;
            }
          } else if (z->app14_color_transform == 2) { // YCCK
            stbi__YCbCr_to_RGB_row(out, y, coutput[1], coutput[2], z->s->img_x, n);
            for (i = 0; i < z->s->img_x; ++i) {
              stbi_uc m = coutput[3][i];
              out[0] = stbi__blinn_8x8(255 - out[0], m);
              out[1] = stbi__blinn_8x8(255 - out[1], m);
              out[2] = stbi__blinn_8x8(255 - out[2], m);
              out += n;
            }
          } else { // YCbCr + alpha?  Ignore the fourth channel for now
            stbi__YCbCr_to_RGB_row(out, y, coutput[1], coutput[2], z->s->img_x, n);
          }
        } else
          for (i = 0; i < z->s->img_x; ++i) {
            out[0] = out[1] = out[2] = y[i];
            out[3] = 255; // not used if n==3
            out += n;
          }
      } else {
        if (is_rgb) {
          if (n == 1)
            for (i = 0; i < z->s->img_x; ++i)
              *out++ = stbi__compute_y(coutput[0][i], coutput[1][i], coutput[2][i]);
          else {
            for (i = 0; i < z->s->img_x; ++i, out += 2) {
              out[0] = stbi__compute_y(coutput[0][i], coutput[1][i], coutput[2][i]);
              out[1] = 255;
            }
          }
        } else if (z->s->img_n == 4 && z->app14_color_transform == 0) {
          for (i = 0; i < z->s->img_x; ++i) {
            stbi_uc m = coutput[3][i];
            stbi_uc r = stbi__blinn_8x8(coutput[0][i], m);
            stbi_uc g = stbi__blinn_8x8(coutput[1][i], m);
            stbi_uc b = stbi__blinn_8x8(coutput[2][i], m);
            out[0] = stbi__compute_y(r, g, b);
            out[1] = 255;
            out += n;
          }
        } else if (z->s->img_n == 4 && z->app14_color_transform == 2) {
          for (i = 0; i < z->s->img_x; ++i) {
            out[0] = stbi__blinn_8x8(255 - coutput[0][i], coutput[3][i]);
            out[1] = 255;
            out += n;
          }
        } else {
          stbi_uc *y = coutput[0];
          if (n == 1)
            for (i = 0; i < z->s->img_x; ++i)
              out[i] = y[i];
          else
            for (i = 0; i < z->s->img_x; ++i) {
              *out++ = y[i];
              *out++ = 255;
            }
        }
      }
    }
    stbi__cleanup_jpeg(z);
    *out_x = z->s->img_x;
    *out_y = z->s->img_y;
    if (comp)
      *comp = z->s->img_n >= 3 ? 3 : 1; // report original components, not output
    return output;
  }
}

static void *stbi__jpeg_load(stbi__context *s, int *x, int *y, int *comp, int req_comp, stbi__result_info *ri) {
  unsigned char *result;
  stbi__jpeg *j = (stbi__jpeg *)stbi__malloc(sizeof(stbi__jpeg));
  STBI_NOTUSED(ri);
  j->s = s;
  result = load_jpeg_image(j, x, y, comp, req_comp);
  STBI_FREE(j);
  return result;
}

static int stbi__jpeg_test(stbi__context *s) {
  int r;
  stbi__jpeg *j = (stbi__jpeg *)stbi__malloc(sizeof(stbi__jpeg));
  j->s = s;
  r = stbi__decode_jpeg_header(j, STBI__SCAN_type);
  stbi__rewind(s);
  STBI_FREE(j);
  return r;
}

static int stbi__jpeg_info_raw(stbi__jpeg *j, int *x, int *y, int *comp) {
  if (!stbi__decode_jpeg_header(j, STBI__SCAN_header)) {
    stbi__rewind(j->s);
    return 0;
  }
  if (x)
    *x = j->s->img_x;
  if (y)
    *y = j->s->img_y;
  if (comp)
    *comp = j->s->img_n >= 3 ? 3 : 1;
  return 1;
}

static int stbi__jpeg_info(stbi__context *s, int *x, int *y, int *comp) {
  int result;
  stbi__jpeg *j = (stbi__jpeg *)(stbi__malloc(sizeof(stbi__jpeg)));
  j->s = s;
  result = stbi__jpeg_info_raw(j, x, y, comp);
  STBI_FREE(j);
  return result;
}

static int stbi__info_main(stbi__context *s, int *x, int *y, int *comp) {
  if (stbi__jpeg_info(s, x, y, comp))
    return 1;

  // test tga last because it's a crappy test!
  return stbi__err("unknown image type", "Image not of any known type, or corrupt");
}

STBIDEF int stbi_info_from_memory(stbi_uc const *buffer, int len, int *x, int *y, int *comp) {
  stbi__context s;
  stbi__start_mem(&s, buffer, len);
  return stbi__info_main(&s, x, y, comp);
}

/*
   revision history:
      2.20  (2019-02-07) support utf8 filenames in Windows; fix warnings and platform ifdefs
      2.19  (2018-02-11) fix warning
      2.18  (2018-01-30) fix warnings
      2.17  (2018-01-29) change sbti__shiftsigned to avoid clang -O2 bug
                         1-bit BMP
                         *_is_16_bit api
                         avoid warnings
      2.16  (2017-07-23) all functions have 16-bit variants;
                         STBI_NO_STDIO works again;
                         compilation fixes;
                         fix rounding in unpremultiply;
                         optimize vertical flip;
                         disable raw_len validation;
                         documentation fixes
      2.15  (2017-03-18) fix png-1,2,4 bug; now all Imagenet JPGs decode;
                         warning fixes; disable run-time SSE detection on gcc;
                         uniform handling of optional "return" values;
                         thread-safe initialization of zlib tables
      2.14  (2017-03-03) remove deprecated STBI_JPEG_OLD; fixes for Imagenet JPGs
      2.13  (2016-11-29) add 16-bit API, only supported for PNG right now
      2.12  (2016-04-02) fix typo in 2.11 PSD fix that caused crashes
      2.11  (2016-04-02) allocate large structures on the stack
                         remove white matting for transparent PSD
                         fix reported channel count for PNG & BMP
                         re-enable SSE2 in non-gcc 64-bit
                         support RGB-formatted JPEG
                         read 16-bit PNGs (only as 8-bit)
      2.10  (2016-01-22) avoid warning introduced in 2.09 by STBI_REALLOC_SIZED
      2.09  (2016-01-16) allow comments in PNM files
                         16-bit-per-pixel TGA (not bit-per-component)
                         info() for TGA could break due to .hdr handling
                         info() for BMP to shares code instead of sloppy parse
                         can use STBI_REALLOC_SIZED if allocator doesn't support realloc
                         code cleanup
      2.08  (2015-09-13) fix to 2.07 cleanup, reading RGB PSD as RGBA
      2.07  (2015-09-13) fix compiler warnings
                         partial animated GIF support
                         limited 16-bpc PSD support
                         #ifdef unused functions
                         bug with < 92 byte PIC,PNM,HDR,TGA
      2.06  (2015-04-19) fix bug where PSD returns wrong '*comp' value
      2.05  (2015-04-19) fix bug in progressive JPEG handling, fix warning
      2.04  (2015-04-15) try to re-enable SIMD on MinGW 64-bit
      2.03  (2015-04-12) extra corruption checking (mmozeiko)
                         stbi_set_flip_vertically_on_load (nguillemot)
                         fix NEON support; fix mingw support
      2.02  (2015-01-19) fix incorrect assert, fix warning
      2.01  (2015-01-17) fix various warnings; suppress SIMD on gcc 32-bit without -msse2
      2.00b (2014-12-25) fix STBI_MALLOC in progressive JPEG
      2.00  (2014-12-25) optimize JPG, including x86 SSE2 & NEON SIMD (ryg)
                         progressive JPEG (stb)
                         PGM/PPM support (Ken Miller)
                         STBI_MALLOC,STBI_REALLOC,STBI_FREE
                         GIF bugfix -- seemingly never worked
                         STBI_NO_*, STBI_ONLY_*
      1.48  (2014-12-14) fix incorrectly-named assert()
      1.47  (2014-12-14) 1/2/4-bit PNG support, both direct and paletted (Omar Cornut & stb)
                         optimize PNG (ryg)
                         fix bug in interlaced PNG with user-specified channel count (stb)
      1.46  (2014-08-26)
              fix broken tRNS chunk (colorkey-style transparency) in non-paletted PNG
      1.45  (2014-08-16)
              fix MSVC-ARM internal compiler error by wrapping malloc
      1.44  (2014-08-07)
              various warning fixes from Ronny Chevalier
      1.43  (2014-07-15)
              fix MSVC-only compiler problem in code changed in 1.42
      1.42  (2014-07-09)
              don't define _CRT_SECURE_NO_WARNINGS (affects user code)
              fixes to stbi__cleanup_jpeg path
              added STBI_ASSERT to avoid requiring assert.h
      1.41  (2014-06-25)
              fix search&replace from 1.36 that messed up comments/error messages
      1.40  (2014-06-22)
              fix gcc struct-initialization warning
      1.39  (2014-06-15)
              fix to TGA optimization when req_comp != number of components in TGA;
              fix to GIF loading because BMP wasn't rewinding (whoops, no GIFs in my test suite)
              add support for BMP version 5 (more ignored fields)
      1.38  (2014-06-06)
              suppress MSVC warnings on integer casts truncating values
              fix accidental rename of 'skip' field of I/O
      1.37  (2014-06-04)
              remove duplicate typedef
      1.36  (2014-06-03)
              convert to header file single-file library
              if de-iphone isn't set, load iphone images color-swapped instead of returning NULL
      1.35  (2014-05-27)
              various warnings
              fix broken STBI_SIMD path
              fix bug where stbi_load_from_file no longer left file pointer in correct place
              fix broken non-easy path for 32-bit BMP (possibly never used)
              TGA optimization by Arseny Kapoulkine
      1.34  (unknown)
              use STBI_NOTUSED in stbi__resample_row_generic(), fix one more leak in tga failure case
      1.33  (2011-07-14)
              make stbi_is_hdr work in STBI_NO_HDR (as specified), minor compiler-friendly improvements
      1.32  (2011-07-13)
              support for "info" function for all supported filetypes (SpartanJ)
      1.31  (2011-06-20)
              a few more leak fixes, bug in PNG handling (SpartanJ)
      1.30  (2011-06-11)
              added ability to load files via callbacks to accomidate custom input streams (Ben Wenger)
              removed deprecated format-specific test/load functions
              removed support for installable file formats (stbi_loader) -- would have been broken for IO callbacks anyway
              error cases in bmp and tga give messages and don't leak (Raymond Barbiero, grisha)
              fix inefficiency in decoding 32-bit BMP (David Woo)
      1.29  (2010-08-16)
              various warning fixes from Aurelien Pocheville
      1.28  (2010-08-01)
              fix bug in GIF palette transparency (SpartanJ)
      1.27  (2010-08-01)
              cast-to-stbi_uc to fix warnings
      1.26  (2010-07-24)
              fix bug in file buffering for PNG reported by SpartanJ
      1.25  (2010-07-17)
              refix trans_data warning (Won Chun)
      1.24  (2010-07-12)
              perf improvements reading from files on platforms with lock-heavy fgetc()
              minor perf improvements for jpeg
              deprecated type-specific functions so we'll get feedback if they're needed
              attempt to fix trans_data warning (Won Chun)
      1.23    fixed bug in iPhone support
      1.22  (2010-07-10)
              removed image *writing* support
              stbi_info support from Jetro Lauha
              GIF support from Jean-Marc Lienher
              iPhone PNG-extensions from James Brown
              warning-fixes from Nicolas Schulz and Janez Zemva (i.stbi__err. Janez (U+017D)emva)
      1.21    fix use of 'stbi_uc' in header (reported by jon blow)
      1.20    added support for Softimage PIC, by Tom Seddon
      1.19    bug in interlaced PNG corruption check (found by ryg)
      1.18  (2008-08-02)
              fix a threading bug (local mutable static)
      1.17    support interlaced PNG
      1.16    major bugfix - stbi__convert_format converted one too many pixels
      1.15    initialize some fields for thread safety
      1.14    fix threadsafe conversion bug
              header-file-only version (#define STBI_HEADER_FILE_ONLY before including)
      1.13    threadsafe
      1.12    const qualifiers in the API
      1.11    Support installable IDCT, colorspace conversion routines
      1.10    Fixes for 64-bit (don't use "unsigned long")
              optimized upsampling by Fabian "ryg" Giesen
      1.09    Fix format-conversion for PSD code (bad global variables!)
      1.08    Thatcher Ulrich's PSD code integrated by Nicolas Schulz
      1.07    attempt to fix C++ warning/errors again
      1.06    attempt to fix C++ warning/errors again
      1.05    fix TGA loading to return correct *comp and use good luminance calc
      1.04    default float alpha is 1, not 255; use 'void *' for stbi_image_free
      1.03    bugfixes to STBI_NO_STDIO, STBI_NO_HDR
      1.02    support for (subset of) HDR files, float interface for preferred access to them
      1.01    fix bug: possible bug in handling right-side up bmps... not sure
              fix bug: the stbi__bmp_load() and stbi__tga_load() functions didn't work at all
      1.00    interface to zlib that skips zlib header
      0.99    correct handling of alpha in palette
      0.98    TGA loader by lonesock; dynamically add loaders (untested)
      0.97    jpeg errors on too large a file; also catch another malloc failure
      0.96    fix detection of invalid v value - particleman@mollyrocket forum
      0.95    during header scan, seek to markers in case of padding
      0.94    STBI_NO_STDIO to disable stdio usage; rename all #defines the same
      0.93    handle jpegtran output; verbose errors
      0.92    read 4,8,16,24,32-bit BMP files of several formats
      0.91    output 24-bit Windows 3.0 BMP files
      0.90    fix a few more warnings; bump version number to approach 1.0
      0.61    bugfixes due to Marc LeBlanc, Christopher Lloyd
      0.60    fix compiling as c++
      0.59    fix warnings: merge Dave Moore's -Wall fixes
      0.58    fix bug: zlib uncompressed mode len/nlen was wrong endian
      0.57    fix bug: jpg last huffman symbol before marker was >9 bits but less than 16 available
      0.56    fix bug: zlib uncompressed mode len vs. nlen
      0.55    fix bug: restart_interval not initialized to 0
      0.54    allow NULL for 'int *comp'
      0.53    fix bug in png 3->4; speedup png decoding
      0.52    png handles req_comp=3,4 directly; minor cleanup; jpeg comments
      0.51    obey req_comp requests, 1-component jpegs return as 1-component,
              on 'test' only check type, not whether we support this variant
      0.50  (2006-11-19)
              first released version
*/

/*
------------------------------------------------------------------------------
This software is available under 2 licenses -- choose whichever you prefer.
------------------------------------------------------------------------------
ALTERNATIVE A - MIT License
Copyright (c) 2017 Sean Barrett
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
------------------------------------------------------------------------------
ALTERNATIVE B - Public Domain (www.unlicense.org)
This is free and unencumbered software released into the public domain.
Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
software, either in source code form or as a compiled binary, for any purpose,
commercial or non-commercial, and by any means.
In jurisdictions that recognize copyright laws, the author or authors of this
software dedicate any and all copyright interest in the software to the public
domain. We make this dedication for the benefit of the public at large and to
the detriment of our heirs and successors. We intend this dedication to be an
overt act of relinquishment in perpetuity of all present and future rights to
this software under copyright law.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
------------------------------------------------------------------------------
*/
