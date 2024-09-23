.section .data
.global ramdisk_start, ramdisk_end
ramdisk_start:
.incbin "resources/coremark-rocket-1.bin"
ramdisk_end:

