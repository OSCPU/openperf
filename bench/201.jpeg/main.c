#include "stb.h"
#include <bench.h>
#include <stdio.h>

static const struct {
  char *file;
  uint32_t cs;
  uint64_t ref_time;
} *ps, settings[BENCH_NR_SETTING] = {
         {"input/test.jpg", 0xebcdd051, 0},
         {"input/train.jpg", 0xdabb6a5f, 83},
         {"input/ref.jpg", 0x5dfead79, 74920},
         {"input/huge.jpg", 0x9ce56e61, 1951833},
};

typedef struct {
  unsigned char *data;
  int w;
  int h;
  int format; // 3: RGB, 4: RGBA
} STBIMG__image;

#define bppToUse STBI_rgb_alpha

static size_t length;
static uint8_t *buffer;
static STBIMG__image img;

void bench_init(int setting) {
  ps = &settings[setting];
  FILE *fp = fopen(ps->file, "r");
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
  int inforet = stbi_info_from_memory(buffer, length, &img.w, &img.h, &img.format);
  if (!inforet) {
    printf("Couldn't get image info: %s!\n", stbi_failure_reason());
    assert(0);
  }

  printf("Image size = %d x %d\n", img.w, img.h);

  img.data = stbi_load_from_memory(buffer, length, &img.w, &img.h, &img.format, bppToUse);
  if (img.data == NULL) {
    printf("Couldn't load image: %s!\n", stbi_failure_reason());
    assert(0);
  }
  img.format = bppToUse;
  return ps->ref_time;
}

int bench_validate() {
  uint32_t cs = bench_checksum(img.data, img.data + (img.w * img.h) * bppToUse);
  printf("checksum = 0x%08x\n", cs);
  free(img.data);
  free(buffer);
  int is_right = cs == ps->cs;
  return !is_right;
}
