// #define npc_trap(code) asm volatile("mv a0, %0; ebreak" : :"r"(code))

int main(const char *args);

static const char mainargs[] = "";

// void halt(int code) {
//   npc_trap(code);
//   while (1);
// }

void _start() {
  int ret = main(mainargs);
    // halt(ret);
}


