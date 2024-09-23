.section .data
.global ramdisk_start, ramdisk_end
ramdisk_start:
.incbin "resources/linux-xiangshan.bin"
ramdisk_end:

