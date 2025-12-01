#include "stb.h"
#include <bench.h>
#include <stdio.h>

typedef struct {
  unsigned char *data;
  int w;
  int h;
  int format; // 3: RGB, 4: RGBA
} STBIMG__image;

static size_t length;
static uint8_t *buffer;
static STBIMG__image img;

void bench_init(int setting) {
  const char *filename = "input/a.jpg";

  FILE *fp = fopen(filename, "r");
  assert(fp);
  fseek(fp, 0, SEEK_END);
  length = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  buffer = malloc(length);
  assert(buffer);
  int ret = fread(buffer, length, 1, fp);
  assert(ret == 1);
  fclose(fp);
}

uint64_t bench_run() {
  int bppToUse = 0;
  int inforet = 0;
  //int origin_has_alpha;

  inforet = stbi_info_from_memory(buffer, length, &img.w, &img.h, &img.format);
  if (!inforet) {
    printf("Couldn't get image info: %s!\n", stbi_failure_reason());
    assert(0);
  }

  // no alpha => use RGB, else use RGBA
  //origin_has_alpha = !(img.format == STBI_grey || img.format == STBI_rgb);
  bppToUse = STBI_rgb_alpha;

  img.data = stbi_load_from_memory(buffer, length, &img.w, &img.h, &img.format, bppToUse);
  if (img.data == NULL) {
    printf("Couldn't load image: %s!\n", stbi_failure_reason());
    assert(0);
  }
  img.format = bppToUse;
  return 0;
}

int bench_validate() {
  free(buffer);

  io_write(AM_GPU_FBDRAW, 0, 0, img.data, img.w, img.h, true);

  while (1)
    ;

  return 0;
}
