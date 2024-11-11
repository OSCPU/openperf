#include "../config.h"
#include <fs.h>

Finfo file_table[] = {
    {"/share/trm.c", 269, 0, NULL, NULL},
    {"/share/trap.h", 110, 269, NULL, NULL},
    {"/share/train.c", 1731, 379, NULL, NULL},
    {"/share/train", 21332, 2110, NULL, NULL},
};
int tcc_argc1 = 10;
char *tcc_argv1[] = {
    "./tcc",     "/share/trm.c", "/share/train.c", "-ffreestanding",
    "-nostdlib", "-o",           "/share/train",   "-Wl,-Ttext=0x80000000",
    "-O2",       "-static"};

bench_tcc_config config = {4};
