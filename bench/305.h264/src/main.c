/* Small application used to test teh h264bsd library on a posix compatible syste */

#include "h264bsd_decoder.h"
#include "h264bsd_util.h"
#include <klib.h>
#include <stdio.h>

static char *outputPath = NULL;
static char *comparePath = NULL;

u8 *loadContent(char *contentPath, size_t *pContentSize) {
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

static FILE *outputFile = NULL;

void savePic(u8 *picData, int width, int height, int picNum) {
  if (outputFile == NULL) {
    outputFile = fopen(outputPath, "w");
    if (outputFile == NULL) {
      return;
    }
  }

  size_t picSize = width * height * 3 / 2;
  off_t offset = 0;
  while (offset < picSize) {
    offset += fwrite(picData + offset, sizeof(u8), picSize - offset, outputFile);
  }
}

void decodeContent(u8 *contentBuffer, size_t contentSize) {
  u32 status;
  storage_t dec;
  status = h264bsdInit(&dec, HANTRO_FALSE);

  if (status != HANTRO_OK) {
    fprintf(stderr, "h264bsdInit failed\n");
    exit(1);
  }

  u8 *byteStrm = contentBuffer;
  u32 readBytes;
  u32 len = contentSize;
  int numPics = 0;
  u8 *pic;
  u32 picId, isIdrPic, numErrMbs;
  u32 top, left, width, height, croppingFlag;
  int totalErrors = 0;

  while (len > 0) {
    u32 result = h264bsdDecode(&dec, byteStrm, len, 0, &readBytes);
    len -= readBytes;
    byteStrm += readBytes;

    switch (result) {
      case H264BSD_PIC_RDY:
        pic = h264bsdNextOutputPicture(&dec, &picId, &isIdrPic, &numErrMbs);
        ++numPics;
        if (outputPath)
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
      case H264BSD_ERROR: printf("Error\n"); exit(1);
      case H264BSD_PARAM_SET_ERROR: printf("Param set error\n"); exit(1);
    }
  }

  h264bsdShutdown(&dec);

  printf("Test file complete. %d pictures decoded.\n", numPics);
  if (comparePath)
    printf("%d errors found.\n", totalErrors);
}

int main(int argc, char *argv[]) {
  char *contentPath = "input/test.h264";
  outputPath = "build/output.yuv";

  size_t contentSize;
  u8 *contentBuffer = loadContent(contentPath, &contentSize);
  decodeContent(contentBuffer, contentSize);
  free(contentBuffer);

  if (outputFile)
    fclose(outputFile);
}
