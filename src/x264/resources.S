.section .data
.global ramdisk_start, ramdisk_end
.global output_start, output_end
ramdisk_start:
#if defined(__BENCH_TEST__)
.incbin "videos/test.yuv"
output_start:
.space 4096, 0
output_end:
#elif defined(__BENCH_TRAIN__)
.incbin "videos/train.yuv"
output_start:
.space 4096, 0
output_end:
#elif defined(__BENCH_HUGE__)
.incbin "videos/huge.yuv"
output_start:
.space 4096, 0
output_end:
#else
.incbin "videos/ref.yuv"
output_start:
.space 409600, 0
output_end:
#endif
ramdisk_end:



