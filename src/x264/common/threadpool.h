/*****************************************************************************
 * threadpool.h: thread pooling
 *****************************************************************************
 * Copyright (C) 2010-2024 x264 project
 *
 * Authors: Steven Walters <kemuri9@gmail.com>
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

#ifndef X264_THREADPOOL_H
#define X264_THREADPOOL_H

typedef struct x264_threadpool_t x264_threadpool_t;


#define x264_threadpool_init(p,t) -1
#define x264_threadpool_run(p,f,a)
#define x264_threadpool_wait(p,a)     NULL
#define x264_threadpool_delete(p)


#endif
