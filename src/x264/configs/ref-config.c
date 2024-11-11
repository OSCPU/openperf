#include <fs.h>
#include <x264.h>

bench_x264_config config = {256, 80, 24, 2};
Finfo filelist[] = {{"/share/video/bad-apple.yuv", 1843200, 0, NULL, NULL},
                    {"/share/video/out.h264", 409600, 1843200, NULL, NULL}};
