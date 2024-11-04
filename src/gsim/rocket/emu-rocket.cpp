#include <TestHarness.h>

extern uint8_t ramdisk_start;
extern uint8_t ramdisk_end;

STestHarness mod = STestHarness();

void mod_reset() {
  mod.set_reset(1);
  mod.step();
  mod.set_reset(0);
}

int main(int argc, char** argv) {
  mod.initAll();
  size_t program_size = &ramdisk_end - &ramdisk_start;
  printf("load program of size 0x%lx\n", program_size);
  memcpy(&mod.mem$srams$mem, &ramdisk_start, program_size);
  mod_reset();
  mod.step();
  printf("start testing.....\n");
  uint64_t cycles = 0;
  while (cycles <= 70000000) {
    cycles ++;
    mod.step();
  }
  return 0;
}