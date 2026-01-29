/* Small application used to test teh h264bsd library on a posix compatible syste */

#include "h264bsd_decoder.h"
#include "h264bsd_util.h"
#include <bench.h>
#include <stdio.h>

static FILE *outputFile;
static u8 *contentBuffer;
static size_t contentSize;
static storage_t dec;
static int numPics;

u8 *loadContent(const char *contentPath, size_t *pContentSize) {
  FILE *input = fopen(contentPath, "r");
  assert(input != NULL);

  fseek(input, 0, SEEK_END);
  size_t size = ftell(input);
  fseek(input, 0, SEEK_SET);

  u8 *contentBuffer = (u8 *)malloc(size);
  assert(contentBuffer != NULL);

  off_t offset = 0;
  while (offset < size) {
    offset += fread(contentBuffer + offset, sizeof(u8), size - offset, input);
  }

  fclose(input);

  *pContentSize = size;
  return contentBuffer;
}

void savePic(u8 *picData, int width, int height, int picNum) {
  size_t picSize = width * height * 3 / 2;
  off_t offset = 0;
  while (offset < picSize) {
    offset += fwrite(picData + offset, sizeof(u8), picSize - offset, outputFile);
  }
}

void bench_init(int setting) {
  contentBuffer = loadContent("input/test.h264", &contentSize);
  outputFile = fopen("build/output.yuv", "w");
  numPics = 0;

  u32 status = h264bsdInit(&dec, HANTRO_FALSE);
  if (status != HANTRO_OK) {
    fprintf(stderr, "h264bsdInit failed\n");
    bench_exit(1);
  }
}

uint64_t bench_run() {
  u8 *byteStrm = contentBuffer;
  u32 readBytes;
  u32 len = contentSize;
  u8 *pic;
  u32 picId, isIdrPic, numErrMbs;
  u32 top, left, width, height, croppingFlag;

  while (len > 0) {
    u32 result = h264bsdDecode(&dec, byteStrm, len, 0, &readBytes);
    len -= readBytes;
    byteStrm += readBytes;

    switch (result) {
      case H264BSD_PIC_RDY:
        pic = h264bsdNextOutputPicture(&dec, &picId, &isIdrPic, &numErrMbs);
        ++numPics;
        savePic(pic, width, height, numPics);
        break;
      case H264BSD_HDRS_RDY:
        h264bsdCroppingParams(&dec, &croppingFlag, &left, &width, &top, &height);
        if (!croppingFlag) {
          width = h264bsdPicWidth(&dec) * 16;
          height = h264bsdPicHeight(&dec) * 16;
        }

        char *cropped = croppingFlag ? "(cropped) " : "";
        printf("Decoded headers. Image size %s%dx%d.\n", cropped, width, height);
        break;
      case H264BSD_RDY: break;
      case H264BSD_ERROR: printf("Error\n"); bench_exit(1);
      case H264BSD_PARAM_SET_ERROR: printf("Param set error\n"); bench_exit(1);
    }
  }
  return 0;
}

int bench_validate() {
  h264bsdShutdown(&dec);
  printf("Test file complete. %d pictures decoded.\n", numPics);

  free(contentBuffer);
  if (outputFile)
    fclose(outputFile);
  return 0;
}
