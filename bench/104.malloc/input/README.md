test - ls -l
train - python -c "print(1+2)"
ref - qemu-system-i386 -serial mon:stdio -machine accel=tcg  -drive format=raw,file=fceux-am/build/fceux-x86-qemu
huge - mousepad
