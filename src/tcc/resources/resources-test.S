.section .data
.global ramdisk_start, ramdisk_end
ramdisk_start:
.incbin "input/test.c"
.incbin "input/test"
.incbin "input/trm.c"
ramdisk_end:
