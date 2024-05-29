.section .data
.global ramdisk_start, ramdisk_end
ramdisk_start:
.incbin "videos/video1.yuv"
.incbin "videos/out.h264"
ramdisk_end:


