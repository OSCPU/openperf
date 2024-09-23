#include <fs.h>
#include <x264.h>

bench_x264_config config = {128, 40, 24, 2};
Finfo filelist[] = {
  {"/share/video/bad-apple.yuv", 368640, 0, NULL, NULL},
  {"/share/video/out.h264", 4096, 368640, NULL, NULL}
};
