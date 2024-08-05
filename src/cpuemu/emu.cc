#define ETL_NO_SMALL_CHAR_SUPPORT 0
#include <SimTop.h>
#include <am.h>
#include <bench.h>
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

int main(int argc, char **argv) {
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

  uint64_t totaltime = uptime() - 2800000000;
  printf("time: %s ms\n", format_time(totaltime));

  return 0;
}
