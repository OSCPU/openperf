.section .data
.global ramdisk_start, ramdisk_end
ramdisk_start:
.incbin "linpack-riscv64-nutshell.bin"
ramdisk_end:


