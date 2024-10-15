#include "../config.h"
#include <fs.h>

Finfo file_table[] = {
    {"/share/trm.c", 273, 0, NULL, NULL},
    {"/share/trap.h", 106, 273, NULL, NULL},
    {"/share/train.c", 1521, 379, NULL, NULL},
    {"/share/train", 106, 1900, NULL, NULL},
};
int tcc_argc1 = 10;
char *tcc_argv1[] = {
    "./tcc",     "/share/trm.c", "/share/train.c", "-ffreestanding",
    "-nostdlib", "-o",           "/share/train",   "-Wl,-Ttext=0x80000000",
    "-O2",       "-static"};

bench_tcc_config config = {4};
