//
// Created by apr on 2021-03-24.
//

#ifndef BLOCKCHAIN_BLOCKCHAIN_H
#define BLOCKCHAIN_BLOCKCHAIN_H
#include "Block.h"
#include <stdint.h>

typedef struct Blockchain {
  uint32_t _nDifficulty;
  Block _vChain[8];
  int nrBlock;
} Blockchain;

void initBlockchain(Blockchain *this, int difficulty);
const char *AddBlock(Blockchain *this, uint32_t nIndexIn, const char *sDataIn);

#endif //BLOCKCHAIN_BLOCKCHAIN_H
