.section .data
.global ramdisk_start, ramdisk_end
ramdisk_start:
.incbin "tests/dummy.c"
.incbin "tests/ex1"
.incbin "tests/trm.c"
ramdisk_end:


