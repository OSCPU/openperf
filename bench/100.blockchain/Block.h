//
// Created by apr on 2021-03-24.
//

#ifndef BLOCKCHAIN_BLOCK_H
#define BLOCKCHAIN_BLOCK_H

#include "sha256.h"
#include <stdint.h>

typedef struct Block {
  long long _nNonce;
  const char *_sData;
  const char *sPrevHash;
  uint32_t _nIndex;
  uint32_t _tTime;
  char _sHash[2 * DIGEST_SIZE + 1];
} Block;

void initBlock(Block *this, uint32_t nIndexIn, const char *sDataIn);
const char *GetHash(Block *this);
void MineBlock(Block *this, uint32_t nDifficulty);

#endif //BLOCKCHAIN_BLOCK_H
