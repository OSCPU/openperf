#include "../config.h"
#include <fs.h>

Finfo file_table[] = {
  {"/share/trm.c", 269, 0, NULL, NULL},
  {"/share/trap.h", 110, 269, NULL, NULL},
  {"/share/ref.c", 1844, 379, NULL, NULL},
  {"/share/ref", 21332, 2223, NULL, NULL}
};

int tcc_argc1 = 10;
char *tcc_argv1[] = {
  "./tcc", "/share/trm.c", "/share/ref.c", "-ffreestanding",
  "-nostdlib", "-o", "/share/ref", "-Wl,-Ttext=0x80000000",
  "-O2", "-static"
};

bench_tcc_config config = {.file_count = 4};
