#include <klib.h>
#include <klib-macros.h>
#include <am.h>
#include <fs.h>
#include <bench_malloc.h>
#include <printf.h>
#include <bench.h>
#include <x264.h>
#include <limits.h>



int main()
{
    int width = 128;
    int height = 40;
    int fps = 24;
    size_t yuv_size = width * height *3/2;
    x264_t *encoder;
    x264_picture_t pic_in,pic_out;
    uint8_t *yuv_buffer;

    x264_param_t m_param;
    x264_param_default_preset(&m_param,"veryfast","zerolatency");
    m_param.i_threads = 1;
    m_param.i_width = width;
    m_param.i_height = height;
    m_param.i_fps_num = fps;
    m_param.i_bframe = 10;
    m_param.i_fps_den = 1;
    m_param.i_keyint_max = 25;
    m_param.b_intra_refresh = 1;
    m_param.b_annexb = 1;
    x264_param_apply_profile(&m_param,"high422");
    encoder = x264_encoder_open(&m_param);
    x264_encoder_parameters( encoder, &m_param );

    x264_picture_alloc(&pic_in, X264_CSP_I420, width, height);

    yuv_buffer = (uint8_t *)bench_malloc(yuv_size);

    pic_in.img.plane[0] = yuv_buffer;
    pic_in.img.plane[1] = pic_in.img.plane[0] + width * height;
    pic_in.img.plane[2] = pic_in.img.plane[1] + width * height / 4;

    int infile = fs_open("/share/video/bad-apple.yuv", 0, 0);
    int outfile = fs_open("/share/video/out.h264", 0, 0);
    assert(infile);
    assert(outfile);

    int64_t i_pts = 0;
    x264_nal_t *nals;
    int nnal;
    uint64_t start_time = uptime(), end_time = ULLONG_MAX;

    while (fs_read(infile, yuv_buffer, yuv_size) > 0) {  
        pic_in.i_pts = i_pts++;
        x264_encoder_encode(encoder, &nals, &nnal, &pic_in, &pic_out);
        x264_nal_t *nal;
        for (nal = nals; nal < nals + nnal; nal++) {
            fs_write(outfile, nal->p_payload, nal->i_payload);
        }
    }
    x264_encoder_close(encoder);
    end_time = uptime();
    bench_free(yuv_buffer);
    printf("time: %s ms \n", format_time(end_time - start_time));
    fs_close(infile);
    fs_close(outfile);
    return 0;
}
