.section .data
.global ramdisk_start, ramdisk_end
ramdisk_start:
.incbin "resources/linux-NutShell.bin"
ramdisk_end:

