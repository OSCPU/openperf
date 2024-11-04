#include <SimTop.h>

extern uint8_t ramdisk_start;
extern uint8_t ramdisk_end;

SSimTop mod;

void mod_reset() {
  mod.set_reset(1);
  for (int i = 0; i < 10; i ++)
    mod.step();
  mod.set_reset(0);
  mod.cycles = 0;
}

int main(int argc, char** argv) {
  mod.init();
  size_t program_size = &ramdisk_end - &ramdisk_start;
  memcpy(&mod.memory$ram$rdata_mem$mem, &ramdisk_start, program_size);
  mod.set_difftest$$perfCtrl$$clean(0);
  mod.set_difftest$$perfCtrl$$dump(0);
  mod.set_difftest$$logCtrl$$begin(0);
  mod.set_difftest$$logCtrl$$end(0);
  mod.set_difftest$$logCtrl$$level(0);
  mod.set_difftest$$uart$$in$$ch(-1);
  mod_reset();
  mod.step();

  printf("start testing.....\n");

  uint64_t cycles = 0;
  uint64_t max_cycles = 6400000;

  while(cycles <= max_cycles) {

    cycles ++;
    mod.step();
    if (mod.get_difftest$$uart$$out$$valid()) {
      printf("%c", mod.get_difftest$$uart$$out$$ch());
    }
  }
  return 0;
}
