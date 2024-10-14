#include "../config.h"
#include <fs.h>

Finfo file_table[] = {
    {"/share/test.c", 336, 0, NULL, NULL},
    {"/share/test", 752, 336, NULL, NULL},
    {"/share/trm.c", 273, 1088, NULL, NULL},
};
int tcc_argc1 = 10;
char *tcc_argv1[] = {
    "./tcc",     "/share/trm.c", "/share/test.c", "-ffreestanding",
    "-nostdlib", "-o",           "/share/test",   "-Wl,-Ttext=0x80000000",
    "-O2",       "-static"};

bench_tcc_config config = {3};
