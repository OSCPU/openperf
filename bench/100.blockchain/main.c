#include "Blockchain.h"
#include <stdio.h>

int main() {
  Blockchain bChain;
  initBlockchain(&bChain);

  printf("Mining block 1...\n");
  AddBlock(&bChain, 1, "Block 1 Data");

  printf("Mining block 2...\n");
  AddBlock(&bChain, 2, "Block 2 Data");

  printf("Mining block 3...\n");
  AddBlock(&bChain, 3, "Block 3 Data");

  return 0;
}
