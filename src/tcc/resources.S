.section .data
.global ramdisk_start, ramdisk_end
ramdisk_start:
#if defined (__BENCH_TEST__)
.incbin "input/test.c"
.incbin "input/test"
.incbin "input/trm.c"
#elif defined (__BENCH_TRAIN__)
.incbin "input/trm.c"
.incbin "input/trap.h"
.incbin "input/train.c"
.incbin "input/train"
#else //default to ref
#endif
ramdisk_end:


