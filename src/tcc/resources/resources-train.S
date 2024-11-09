.section .data
.global ramdisk_start, ramdisk_end
ramdisk_start:
.incbin "input/trm.c"
.incbin "input/trap.h"
.incbin "input/train.c"
.incbin "input/train"
ramdisk_end:
