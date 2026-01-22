/* ***** BEGIN LICENSE BLOCK ***** 
 * Version: RCSL 1.0/RPSL 1.0 
 *  
 * Portions Copyright (c) 1995-2002 RealNetworks, Inc. All Rights Reserved. 
 *      
 * The contents of this file, and the files included with this file, are 
 * subject to the current version of the RealNetworks Public Source License 
 * Version 1.0 (the "RPSL") available at 
 * http://www.helixcommunity.org/content/rpsl unless you have licensed 
 * the file under the RealNetworks Community Source License Version 1.0 
 * (the "RCSL") available at http://www.helixcommunity.org/content/rcsl, 
 * in which case the RCSL will apply. You may also obtain the license terms 
 * directly from RealNetworks.  You may not use this file except in 
 * compliance with the RPSL or, if you have a valid RCSL with RealNetworks 
 * applicable to this file, the RCSL.  Please see the applicable RPSL or 
 * RCSL for the rights, obligations and limitations governing use of the 
 * contents of the file.  
 *  
 * This file is part of the Helix DNA Technology. RealNetworks is the 
 * developer of the Original Code and owns the copyrights in the portions 
 * it created. 
 *  
 * This file, and the files included with this file, is distributed and made 
 * available on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER 
 * EXPRESS OR IMPLIED, AND REALNETWORKS HEREBY DISCLAIMS ALL SUCH WARRANTIES, 
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS 
 * FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT. 
 * 
 * Technology Compatibility Kit Test Suite(s) Location: 
 *    http://www.helixcommunity.org/content/tck 
 * 
 * Contributor(s): 
 *  
 * ***** END LICENSE BLOCK ***** */

/**************************************************************************************
 * Fixed-point MP3 decoder
 * Jon Recker (jrecker@real.com), Ken Cooke (kenc@real.com)
 * June 2003
 *
 * main.c - command-line test app that uses C interface to MP3 decoder
 **************************************************************************************/

#include "mp3dec.h"
#include <bench.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define READBUF_SIZE (1024 * 16) /* feel free to change this, but keep big enough for >= one frame at high bitrates */

static int FillReadBuffer(unsigned char *readBuf, unsigned char *readPtr, int bufSize, int bytesLeft, FILE *infile) {
  int nRead;

  /* move last, small chunk from end of buffer to start, then fill with new data */
  memmove(readBuf, readPtr, bytesLeft);
  nRead = fread(readBuf + bytesLeft, 1, bufSize - bytesLeft, infile);
  /* zero-pad to avoid finding false sync word after last frame (from old data in readBuf) */
  if (nRead < bufSize - bytesLeft)
    memset(readBuf + bytesLeft + nRead, 0, bufSize - bytesLeft - nRead);

  return nRead;
}

static HMP3Decoder hMP3Decoder;
static MP3FrameInfo mp3FrameInfo;
static unsigned nFrames;
static uint64_t totalDecTime;
static FILE *infile, *outfile;
static unsigned char readBuf[READBUF_SIZE];
static short outBuf[MAX_NCHAN * MAX_NGRAN * MAX_NSAMP];

void bench_init(int setting) {
  char *argv[] = {"mp3", "input/test.mp3", "build/test.pcm", NULL};

  infile = fopen(argv[1], "rb");
  if (!infile) {
    printf("file open error\n");
    bench_exit(1);
  }

  outfile = fopen(argv[2], "wb");
  if (!outfile) {
    printf("file open error\n");
    bench_exit(1);
  }

  if ((hMP3Decoder = MP3InitDecoder()) == 0) {
    bench_exit(2);
  }
}

uint64_t bench_run() {
  int bytesLeft, nRead, err, offset, outOfData, eofReached;
  unsigned char *readPtr;
  uint64_t startTime, endTime, diffTime;
  bytesLeft = 0;
  outOfData = 0;
  eofReached = 0;
  readPtr = readBuf;
  nRead = 0;
  totalDecTime = 0;
  nFrames = 0;
  do {
    /* somewhat arbitrary trigger to refill buffer - should always be enough for a full frame */
    if (bytesLeft < 2 * MAINBUF_SIZE && !eofReached) {
      nRead = FillReadBuffer(readBuf, readPtr, READBUF_SIZE, bytesLeft, infile);
      bytesLeft += nRead;
      readPtr = readBuf;
      if (nRead == 0)
        eofReached = 1;
    }

    /* find start of next MP3 frame - assume EOF if no sync found */
    offset = MP3FindSyncWord(readPtr, bytesLeft);
    if (offset < 0) {
      outOfData = 1;
      break;
    }
    readPtr += offset;
    bytesLeft -= offset;

    /* decode one MP3 frame - if offset < 0 then bytesLeft was less than a full frame */
    startTime = bench_uptime();
    err = MP3Decode(hMP3Decoder, &readPtr, &bytesLeft, outBuf, 0);
    nFrames++;

    endTime = bench_uptime();
    diffTime = endTime - startTime;
    totalDecTime += diffTime;
    //printf("frame %5d  start = %lld us, end = %lld us, elapsed = %lld us\n", nFrames, startTime, endTime, diffTime);

    if (err) {
      /* error occurred */
      switch (err) {
        case ERR_MP3_INDATA_UNDERFLOW: outOfData = 1; break;
        case ERR_MP3_MAINDATA_UNDERFLOW:
          /* do nothing - next call to decode will provide more mainData */
          break;
        case ERR_MP3_FREE_BITRATE_SYNC:
        default: outOfData = 1; break;
      }
    } else {
      /* no error */
      MP3GetLastFrameInfo(hMP3Decoder, &mp3FrameInfo);
      if (outfile)
        fwrite(outBuf, mp3FrameInfo.bitsPerSample / 8, mp3FrameInfo.outputSamps, outfile);
    }
  } while (!outOfData);

  return 0;
}

int bench_validate() {
  MP3GetLastFrameInfo(hMP3Decoder, &mp3FrameInfo);
  printf("nFrames = %d, output samps = %d, sampRate = %d, nChans = %d\n", nFrames, mp3FrameInfo.outputSamps,
         mp3FrameInfo.samprate, mp3FrameInfo.nChans);
  uint64_t audioTime =
      (nFrames * mp3FrameInfo.outputSamps) * 1000000ull / (mp3FrameInfo.samprate * mp3FrameInfo.nChans);
  printf("Audio time = %lld us\n", audioTime * 1ull);
  printf("Decode time = %lld us\n", totalDecTime * 1ull);
  printf("Decode frequency = %d%%\n", (unsigned)(audioTime * 100ull / totalDecTime));

  MP3FreeDecoder(hMP3Decoder);

  fclose(infile);
  if (outfile)
    fclose(outfile);

  return 0;
}
