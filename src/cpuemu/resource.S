.section .data
.global ramdisk_start, ramdisk_end
ramdisk_start:
.incbin "mersenne-riscv32e.bin"
ramdisk_end:

