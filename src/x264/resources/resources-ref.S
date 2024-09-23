.section .data
.global ramdisk_start, ramdisk_end
.global output_start, output_end
ramdisk_start:
.incbin "videos/ref.yuv"
output_start:
.space 409600, 0
output_end:
ramdisk_end:



