#include <klib.h>
#include <fs.h>
#include <my_malloc.h>
#include "x264.h"


int main()
{
    int width = 320;
    int height = 160;
    int fps = 25;
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

    yuv_buffer = (uint8_t *)my_malloc(yuv_size);

    pic_in.img.plane[0] = yuv_buffer;
    pic_in.img.plane[1] = pic_in.img.plane[0] + width * height;
    pic_in.img.plane[2] = pic_in.img.plane[1] + width * height / 4;

    // FILE* infile = fopen("/share/viedo/video1.yuv","rb");
    // FILE* outfile = fopen("/share/viedo/out.h264","ab");
    int infile = fs_open("/share/viedo/video1.yuv", 0, 0);
    int outfile = fs_open("/share/viedo/out.h264", 0, 0);

    if(!infile || !outfile)
    {
        my_printf("open file error\n");
        return 0;
    }
    int64_t i_pts = 0;
 
    x264_nal_t *nals;
    int nnal;
    // while (fread(yuv_buffer, 1,yuv_size, infile) > 0) {  
    while (fs_read(infile, yuv_buffer, yuv_size) > 0) {  
        pic_in.i_pts = i_pts++;
        x264_encoder_encode(encoder, &nals, &nnal, &pic_in, &pic_out);
        x264_nal_t *nal;
        for (nal = nals; nal < nals + nnal; nal++) {
            // fwrite(nal->p_payload, 1,nal->i_payload,outfile);
            fs_write(outfile, nal->p_payload, nal->i_payload);
        }
    }
    my_printf("encode end\n");
    x264_encoder_close(encoder);
    fs_close(infile);
    fs_close(outfile);
    free(yuv_buffer);
    my_all_free();
    return 0;
}
