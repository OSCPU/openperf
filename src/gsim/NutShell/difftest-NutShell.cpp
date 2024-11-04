
#include <SimTop.h>
SSimTop mod;

extern uint8_t ramdisk_start;
extern uint8_t ramdisk_end;

void mod_reset() {
  mod.set_reset(1);
  mod.step();
  mod.set_reset(0);
}

int main(int argc, char** argv) {
  size_t program_size = &ramdisk_end - &ramdisk_start;
  printf("load program of size 0x%lx\n", program_size);
  memcpy(&mod.mem$rdata_mem$mem, &ramdisk_start, program_size);
  mod.set_io_logCtrl_log_begin(0);
  mod.set_io_logCtrl_log_end(0);
  mod.set_io_uart_in_ch(-1);
  mod_reset();
  mod.step();
  printf("%lx\n", *(uint64_t*)mod.mem$rdata_mem$mem);
  printf("start testing.....\n");
  uint64_t cycles = 0;
  while(cycles <= 250000000) {
    if (cycles % 100000 == 0) {
      printf("cycles = %ld\n", cycles);
    }
    cycles ++;
    mod.step();
    if (mod.get_io_uart_out_valid()) {
      printf("%c", mod.get_io_uart_out_ch());
    }

  }
  return 0;
}