/*****************************************************************************
 * quant.c: quantization and level-run
 *****************************************************************************
 * Copyright (C) 2005-2024 x264 project
 *
 * Authors: Loren Merritt <lorenm@u.washington.edu>
 *          Fiona Glaser <fiona@x264.com>
 *          Christian Heine <sennindemokrit@gmx.net>
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

#include "common.h"


#define QUANT_ONE( coef, mf, f ) \
{ \
    if( (coef) > 0 ) \
        (coef) = ((f) + (uint32_t)(coef)) * (mf) >> 16; \
    else \
        (coef) = -(int32_t)(((f) + (uint32_t)(-coef)) * (mf) >> 16); \
    nz |= (coef); \
}

static int quant_8x8( dctcoef dct[64], udctcoef mf[64], udctcoef bias[64] )
{
    int nz = 0;
    for( int i = 0; i < 64; i++ )
        QUANT_ONE( dct[i], mf[i], bias[i] );
    return !!nz;
}

static int quant_4x4( dctcoef dct[16], udctcoef mf[16], udctcoef bias[16] )
{
    int nz = 0;
    for( int i = 0; i < 16; i++ )
        QUANT_ONE( dct[i], mf[i], bias[i] );
    return !!nz;
}

static int quant_4x4x4( dctcoef dct[4][16], udctcoef mf[16], udctcoef bias[16] )
{
    int nza = 0;
    for( int j = 0; j < 4; j++ )
    {
        int nz = 0;
        for( int i = 0; i < 16; i++ )
            QUANT_ONE( dct[j][i], mf[i], bias[i] );
        nza |= (!!nz)<<j;
    }
    return nza;
}

static int quant_4x4_dc( dctcoef dct[16], int mf, int bias )
{
    int nz = 0;
    for( int i = 0; i < 16; i++ )
        QUANT_ONE( dct[i], mf, bias );
    return !!nz;
}

static int quant_2x2_dc( dctcoef dct[4], int mf, int bias )
{
    int nz = 0;
    QUANT_ONE( dct[0], mf, bias );
    QUANT_ONE( dct[1], mf, bias );
    QUANT_ONE( dct[2], mf, bias );
    QUANT_ONE( dct[3], mf, bias );
    return !!nz;
}

#define DEQUANT_SHL( x ) \
    dct[x] = ( dct[x] * dequant_mf[i_mf][x] ) * (1 << i_qbits)

#define DEQUANT_SHR( x ) \
    dct[x] = ( dct[x] * dequant_mf[i_mf][x] + f ) >> (-i_qbits)

static void dequant_4x4( dctcoef dct[16], int dequant_mf[6][16], int i_qp )
{
    const int i_mf = i_qp%6;
    const int i_qbits = i_qp/6 - 4;

    if( i_qbits >= 0 )
    {
        for( int i = 0; i < 16; i++ )
            DEQUANT_SHL( i );
    }
    else
    {
        const int f = 1 << (-i_qbits-1);
        for( int i = 0; i < 16; i++ )
            DEQUANT_SHR( i );
    }
}

static void dequant_8x8( dctcoef dct[64], int dequant_mf[6][64], int i_qp )
{
    const int i_mf = i_qp%6;
    const int i_qbits = i_qp/6 - 6;

    if( i_qbits >= 0 )
    {
        for( int i = 0; i < 64; i++ )
            DEQUANT_SHL( i );
    }
    else
    {
        const int f = 1 << (-i_qbits-1);
        for( int i = 0; i < 64; i++ )
            DEQUANT_SHR( i );
    }
}

static void dequant_4x4_dc( dctcoef dct[16], int dequant_mf[6][16], int i_qp )
{
    const int i_qbits = i_qp/6 - 6;

    if( i_qbits >= 0 )
    {
        const int i_dmf = dequant_mf[i_qp%6][0] << i_qbits;
        for( int i = 0; i < 16; i++ )
            dct[i] *= i_dmf;
    }
    else
    {
        const int i_dmf = dequant_mf[i_qp%6][0];
        const int f = 1 << (-i_qbits-1);
        for( int i = 0; i < 16; i++ )
            dct[i] = ( dct[i] * i_dmf + f ) >> (-i_qbits);
    }
}

#define IDCT_DEQUANT_2X4_START \
    int a0 = dct[0] + dct[1]; \
    int a1 = dct[2] + dct[3]; \
    int a2 = dct[4] + dct[5]; \
    int a3 = dct[6] + dct[7]; \
    int a4 = dct[0] - dct[1]; \
    int a5 = dct[2] - dct[3]; \
    int a6 = dct[4] - dct[5]; \
    int a7 = dct[6] - dct[7]; \
    int b0 = a0 + a1; \
    int b1 = a2 + a3; \
    int b2 = a4 + a5; \
    int b3 = a6 + a7; \
    int b4 = a0 - a1; \
    int b5 = a2 - a3; \
    int b6 = a4 - a5; \
    int b7 = a6 - a7;

static void idct_dequant_2x4_dc( dctcoef dct[8], dctcoef dct4x4[8][16], int dequant_mf[6][16], int i_qp )
{
    IDCT_DEQUANT_2X4_START
    int dmf = dequant_mf[i_qp%6][0] << i_qp/6;
    dct4x4[0][0] = ((b0 + b1) * dmf + 32) >> 6;
    dct4x4[1][0] = ((b2 + b3) * dmf + 32) >> 6;
    dct4x4[2][0] = ((b0 - b1) * dmf + 32) >> 6;
    dct4x4[3][0] = ((b2 - b3) * dmf + 32) >> 6;
    dct4x4[4][0] = ((b4 - b5) * dmf + 32) >> 6;
    dct4x4[5][0] = ((b6 - b7) * dmf + 32) >> 6;
    dct4x4[6][0] = ((b4 + b5) * dmf + 32) >> 6;
    dct4x4[7][0] = ((b6 + b7) * dmf + 32) >> 6;
}

static void idct_dequant_2x4_dconly( dctcoef dct[8], int dequant_mf[6][16], int i_qp )
{
    IDCT_DEQUANT_2X4_START
    int dmf = dequant_mf[i_qp%6][0] << i_qp/6;
    dct[0] = ((b0 + b1) * dmf + 32) >> 6;
    dct[1] = ((b2 + b3) * dmf + 32) >> 6;
    dct[2] = ((b0 - b1) * dmf + 32) >> 6;
    dct[3] = ((b2 - b3) * dmf + 32) >> 6;
    dct[4] = ((b4 - b5) * dmf + 32) >> 6;
    dct[5] = ((b6 - b7) * dmf + 32) >> 6;
    dct[6] = ((b4 + b5) * dmf + 32) >> 6;
    dct[7] = ((b6 + b7) * dmf + 32) >> 6;
}

static ALWAYS_INLINE void optimize_chroma_idct_dequant_2x4( dctcoef out[8], dctcoef dct[8], int dmf )
{
    IDCT_DEQUANT_2X4_START
    out[0] = ((b0 + b1) * dmf + 2080) >> 6; /* 2080 = 32 + (32<<6) */
    out[1] = ((b2 + b3) * dmf + 2080) >> 6;
    out[2] = ((b0 - b1) * dmf + 2080) >> 6;
    out[3] = ((b2 - b3) * dmf + 2080) >> 6;
    out[4] = ((b4 - b5) * dmf + 2080) >> 6;
    out[5] = ((b6 - b7) * dmf + 2080) >> 6;
    out[6] = ((b4 + b5) * dmf + 2080) >> 6;
    out[7] = ((b6 + b7) * dmf + 2080) >> 6;
}
#undef IDCT_DEQUANT_2X4_START

static ALWAYS_INLINE void optimize_chroma_idct_dequant_2x2( dctcoef out[4], dctcoef dct[4], int dmf )
{
    int d0 = dct[0] + dct[1];
    int d1 = dct[2] + dct[3];
    int d2 = dct[0] - dct[1];
    int d3 = dct[2] - dct[3];
    out[0] = ((d0 + d1) * dmf >> 5) + 32;
    out[1] = ((d0 - d1) * dmf >> 5) + 32;
    out[2] = ((d2 + d3) * dmf >> 5) + 32;
    out[3] = ((d2 - d3) * dmf >> 5) + 32;
}

static ALWAYS_INLINE int optimize_chroma_round( dctcoef *ref, dctcoef *dct, int dequant_mf, int chroma422 )
{
    dctcoef out[8];

    if( chroma422 )
        optimize_chroma_idct_dequant_2x4( out, dct, dequant_mf );
    else
        optimize_chroma_idct_dequant_2x2( out, dct, dequant_mf );

    int sum = 0;
    for( int i = 0; i < (chroma422?8:4); i++ )
        sum |= ref[i] ^ out[i];
    return sum >> 6;
}

static ALWAYS_INLINE int optimize_chroma_dc_internal( dctcoef *dct, int dequant_mf, int chroma422 )
{
    /* dequant_mf = h->dequant4_mf[CQM_4IC + b_inter][i_qp%6][0] << i_qp/6, max 32*64 */
    dctcoef dct_orig[8];
    int coeff, nz;

    if( chroma422 )
        optimize_chroma_idct_dequant_2x4( dct_orig, dct, dequant_mf );
    else
        optimize_chroma_idct_dequant_2x2( dct_orig, dct, dequant_mf );

    /* If the DC coefficients already round to zero, terminate early. */
    int sum = 0;
    for( int i = 0; i < (chroma422?8:4); i++ )
        sum |= dct_orig[i];
    if( !(sum >> 6) )
        return 0;

    /* Start with the highest frequency coefficient... is this the best option? */
    for( nz = 0, coeff = (chroma422?7:3); coeff >= 0; coeff-- )
    {
        int level = dct[coeff];
        int sign = level>>31 | 1; /* dct[coeff] < 0 ? -1 : 1 */

        while( level )
        {
            dct[coeff] = level - sign;
            if( optimize_chroma_round( dct_orig, dct, dequant_mf, chroma422 ) )
            {
                nz = 1;
                dct[coeff] = level;
                break;
            }
            level -= sign;
        }
    }

    return nz;
}

static int optimize_chroma_2x2_dc( dctcoef dct[4], int dequant_mf )
{
    return optimize_chroma_dc_internal( dct, dequant_mf, 0 );
}

static int optimize_chroma_2x4_dc( dctcoef dct[8], int dequant_mf )
{
    return optimize_chroma_dc_internal( dct, dequant_mf, 1 );
}

static void denoise_dct( dctcoef *dct, uint32_t *sum, udctcoef *offset, int size )
{
    for( int i = 0; i < size; i++ )
    {
        int level = dct[i];
        int sign = level>>31;
        level = (level+sign)^sign;
        sum[i] += level;
        level -= offset[i];
        dct[i] = level<0 ? 0 : (level^sign)-sign;
    }
}

/* (ref: JVT-B118)
 * x264_mb_decimate_score: given dct coeffs it returns a score to see if we could empty this dct coeffs
 * to 0 (low score means set it to null)
 * Used in inter macroblock (luma and chroma)
 *  luma: for a 8x8 block: if score < 4 -> null
 *        for the complete mb: if score < 6 -> null
 *  chroma: for the complete mb: if score < 7 -> null
 */

static ALWAYS_INLINE int decimate_score_internal( dctcoef *dct, int i_max )
{
    const uint8_t *ds_table = (i_max == 64) ? x264_decimate_table8 : x264_decimate_table4;
    int i_score = 0;
    int idx = i_max - 1;

    while( idx >= 0 && dct[idx] == 0 )
        idx--;
    while( idx >= 0 )
    {
        int i_run;

        if( (unsigned)(dct[idx--] + 1) > 2 )
            return 9;

        i_run = 0;
        while( idx >= 0 && dct[idx] == 0 )
        {
            idx--;
            i_run++;
        }
        i_score += ds_table[i_run];
    }

    return i_score;
}

static int decimate_score15( dctcoef *dct )
{
    return decimate_score_internal( dct+1, 15 );
}
static int decimate_score16( dctcoef *dct )
{
    return decimate_score_internal( dct, 16 );
}
static int decimate_score64( dctcoef *dct )
{
    return decimate_score_internal( dct, 64 );
}

#define last(num)\
static int coeff_last##num( dctcoef *l )\
{\
    int i_last = num-1;\
    while( i_last >= 0 && l[i_last] == 0 )\
        i_last--;\
    return i_last;\
}

last(4)
last(8)
last(15)
last(16)
last(64)

#define level_run(num)\
static int coeff_level_run##num( dctcoef *dct, x264_run_level_t *runlevel )\
{\
    int i_last = runlevel->last = coeff_last##num(dct);\
    int i_total = 0;\
    int mask = 0;\
    do\
    {\
        runlevel->level[i_total++] = dct[i_last];\
        mask |= 1 << (i_last);\
        while( --i_last >= 0 && dct[i_last] == 0 );\
    } while( i_last >= 0 );\
    runlevel->mask = mask;\
    return i_total;\
}

level_run(4)
level_run(8)
level_run(15)
level_run(16)


#define INIT_TRELLIS(...)


void x264_quant_init( x264_t *h, uint32_t cpu, x264_quant_function_t *pf )
{
    pf->quant_8x8 = quant_8x8;
    pf->quant_4x4 = quant_4x4;
    pf->quant_4x4x4 = quant_4x4x4;
    pf->quant_4x4_dc = quant_4x4_dc;
    pf->quant_2x2_dc = quant_2x2_dc;

    pf->dequant_4x4 = dequant_4x4;
    pf->dequant_4x4_dc = dequant_4x4_dc;
    pf->dequant_8x8 = dequant_8x8;

    pf->idct_dequant_2x4_dc = idct_dequant_2x4_dc;
    pf->idct_dequant_2x4_dconly = idct_dequant_2x4_dconly;

    pf->optimize_chroma_2x2_dc = optimize_chroma_2x2_dc;
    pf->optimize_chroma_2x4_dc = optimize_chroma_2x4_dc;

    pf->denoise_dct = denoise_dct;
    pf->decimate_score15 = decimate_score15;
    pf->decimate_score16 = decimate_score16;
    pf->decimate_score64 = decimate_score64;

    pf->coeff_last4 = coeff_last4;
    pf->coeff_last8 = coeff_last8;
    pf->coeff_last[  DCT_LUMA_AC] = coeff_last15;
    pf->coeff_last[ DCT_LUMA_4x4] = coeff_last16;
    pf->coeff_last[ DCT_LUMA_8x8] = coeff_last64;
    pf->coeff_level_run4 = coeff_level_run4;
    pf->coeff_level_run8 = coeff_level_run8;
    pf->coeff_level_run[  DCT_LUMA_AC] = coeff_level_run15;
    pf->coeff_level_run[ DCT_LUMA_4x4] = coeff_level_run16;

    pf->coeff_last[DCT_LUMA_DC]     = pf->coeff_last[DCT_CHROMAU_DC]  = pf->coeff_last[DCT_CHROMAV_DC] =
    pf->coeff_last[DCT_CHROMAU_4x4] = pf->coeff_last[DCT_CHROMAV_4x4] = pf->coeff_last[DCT_LUMA_4x4];
    pf->coeff_last[DCT_CHROMA_AC]   = pf->coeff_last[DCT_CHROMAU_AC]  =
    pf->coeff_last[DCT_CHROMAV_AC]  = pf->coeff_last[DCT_LUMA_AC];
    pf->coeff_last[DCT_CHROMAU_8x8] = pf->coeff_last[DCT_CHROMAV_8x8] = pf->coeff_last[DCT_LUMA_8x8];

    pf->coeff_level_run[DCT_LUMA_DC]     = pf->coeff_level_run[DCT_CHROMAU_DC]  = pf->coeff_level_run[DCT_CHROMAV_DC] =
    pf->coeff_level_run[DCT_CHROMAU_4x4] = pf->coeff_level_run[DCT_CHROMAV_4x4] = pf->coeff_level_run[DCT_LUMA_4x4];
    pf->coeff_level_run[DCT_CHROMA_AC]   = pf->coeff_level_run[DCT_CHROMAU_AC]  =
    pf->coeff_level_run[DCT_CHROMAV_AC]  = pf->coeff_level_run[DCT_LUMA_AC];
}
