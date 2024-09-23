#include <fs.h>
#include <x264.h>


bench_x264_config config = {64, 20, 24, 2};
Finfo filelist[] = {
  {"/share/video/bad-apple.yuv", 23040, 0, NULL, NULL},
  {"/share/video/out.h264", 4096, 23040, NULL, NULL}
};
