//
// Created by apr on 2021-03-24.
//

#include "Block.h"
#include "sha256.h"
#include <bench.h>

static void _CalculateHash(Block *this) {
  static char str[1024];
  sprintf(str, "%d%d%s%lld%s", this->_nIndex, this->_tTime, this->_sData, this->_nNonce, this->sPrevHash);
  sha256(this->_sHash, str);
}

void initBlock(Block *this, uint32_t nIndexIn, const char *sDataIn) {
  this->_nIndex = nIndexIn;
  this->_sData = sDataIn;
  this->_nNonce = -1;
  this->_tTime = bench_rand();
  this->_sHash[0] = '\0';
}

const char *GetHash(Block *this) {
  return this->_sHash;
}

void MineBlock(Block *this, uint32_t nDifficulty) {
  char *cstr = malloc(nDifficulty + 1);
  memset(cstr, '0', nDifficulty);
  cstr[nDifficulty] = '\0';

  do {
    this->_nNonce++;
    _CalculateHash(this);
  } while (memcmp(this->_sHash, cstr, nDifficulty) != 0);

  printf("Block mined: %s\n", this->_sHash);
  free(cstr);
}
