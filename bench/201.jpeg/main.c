#include "stb.h"
#include <am.h>
#include <klib.h>
#include <stdio.h>

typedef struct {
  unsigned char *data;
  int w;
  int h;
  int format; // 3: RGB, 4: RGBA
} STBIMG__image;

int main() {
  ioe_init();

  const char *filename = "a.jpg";

  FILE *fp = fopen(filename, "r");
  assert(fp);
  fseek(fp, 0, SEEK_END);
  size_t length = ftell(fp);
  rewind(fp);
  uint8_t *buffer = malloc(length);
  assert(buffer);
  int ret = fread(buffer, length, 1, fp);
  assert(ret == 1);
  fclose(fp);

  STBIMG__image img = {0};
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

  free(buffer);

  io_write(AM_GPU_FBDRAW, 0, 0, img.data, img.w, img.h, true);

  while (1)
    ;

  return 0;
}
