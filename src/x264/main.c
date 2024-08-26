#include <am.h>
#include <klib-macros.h>
#include <klib.h>
#include <bench.h>
#include <bench_malloc.h>
#include <bench_printf.h>
#include <fs.h>
#include <limits.h>
#include <x264.h>


typedef struct {
  uint32_t width;
  uint32_t height;
  uint32_t fps;
} bench_x264_config;

#if defined (__BENCH_TEST__)
//Use a macro to do this
static bench_x264_config config = {128, 40, 24};
static Finfo filelist[] = {
  {"/share/video/bad-apple.yuv", 368640, 0, NULL, NULL},
  {"/share/video/out.h264", 4096, 368640, NULL, NULL}
};
#elif defined (__BENCH_TRAIN__)
static bench_x264_config config = {64, 20, 24};
static Finfo filelist[] = {
  {"/share/video/bad-apple.yuv", 138240, 0, NULL, NULL},
  {"/share/video/out.h264", 4096, 138240, NULL, NULL}
};
#elif defined (__BENCH_HUGE__)
#else //default to ref

#endif


int main(const char *args) {
  bench_malloc_init();
  fs_init(filelist, 2);

  uint64_t start_time = uptime(), end_time = ULLONG_MAX;
  int width = config.width;
  int height = config.height;
  int fps = config.fps;

  size_t yuv_size = width * height * 3 / 2;
  x264_t *encoder;
  x264_picture_t pic_in, pic_out;
  uint8_t *yuv_buffer;

  x264_param_t m_param;
  x264_param_default_preset(&m_param, "veryfast", "zerolatency");
  m_param.i_threads = 1;
  m_param.i_width = width;
  m_param.i_height = height;
  m_param.i_fps_num = fps;
  m_param.i_bframe = 10;
  m_param.i_fps_den = 1;
  m_param.i_keyint_max = 25;
  m_param.b_intra_refresh = 1;
  m_param.b_annexb = 1;
  x264_param_apply_profile(&m_param, "high422");

  encoder = x264_encoder_open(&m_param);
  x264_encoder_parameters(encoder, &m_param);

  x264_picture_alloc(&pic_in, X264_CSP_I420, width, height);
  yuv_buffer = (uint8_t *)bench_malloc(yuv_size);

  pic_in.img.plane[0] = yuv_buffer;
  pic_in.img.plane[1] = pic_in.img.plane[0] + width * height;
  pic_in.img.plane[2] = pic_in.img.plane[1] + width * height / 4;

  int input = fs_open("/share/video/bad-apple.yuv", 0, 0);
  int output = fs_open("/share/video/out.h264", 0, 0);

  int64_t i_pts = 0;
  x264_nal_t *nals;
  int nnal;

  while (fs_read(input, yuv_buffer, yuv_size) > 0) {
    pic_in.i_pts = i_pts++;
    x264_encoder_encode(encoder, &nals, &nnal, &pic_in, &pic_out);
    x264_nal_t *nal;
    for (nal = nals; nal < nals + nnal; nal++) {
      fs_write(output, nal->p_payload, nal->i_payload);
    }
  }
  x264_encoder_close(encoder);
  end_time = uptime();
  bench_free(yuv_buffer);
  uint32_t total = fs_lseek(output, 0, SEEK_CUR);

  extern char output_start;
  bench_printf("total: %d\n", total);
  bench_printf("Checksum is %#x\n", checksum(&output_start, (uint8_t *)&output_start + total));
  bench_printf("time: %s ms \n", format_time(end_time - start_time));

  fs_close(input);
  fs_close(output);
 
  return 0;
}
