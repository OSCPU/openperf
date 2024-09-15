#include <cpuemu.h>
#include <SimTop.h>
#undef assert
#include <am.h>
#include <klib.h>

extern uint8_t ramdisk_start;
extern uint8_t ramdisk_end;

#define MAX_PROGRAM_SIZE ((&ramdisk_start) - (&ramdisk_end))
void *program;
int program_sz = 0;
SimTop cpu;

void load_program() {

  program = malloc(MAX_PROGRAM_SIZE);

  memset(&program, 0, sizeof(program));
  // move the program to the memory
  memcpy(&program, &ramdisk_start, &ramdisk_end - &ramdisk_start);
  program_sz = &ramdisk_end - &ramdisk_start;

  return;
}

void nutshell() {
  load_program();

  memcpy(cpu.mem.rdata_mem.mem, &program, program_sz);
  cpu.reset = UInt<1>(1);
  cpu.eval(false, false, false);
  for (int i = 0; i < 5; i++) {
    cpu.eval(true, false, false);
    cpu.reset = UInt<1>(0);
    cpu.eval(false, false, false);
  }

  // std::cout << "start testing.....\n";
  printf("start testing.....\n");

  bool dut_end = false;
  // uint64_t cycles = 0;
  while (!dut_end) {
    cpu.eval(true, true, true);

    if (cpu.io_uart_out_valid) {
      break;
      printf("%c", cpu.io_uart_out_ch);
      // fflush(stdout);
    }

  }

  return;
}
