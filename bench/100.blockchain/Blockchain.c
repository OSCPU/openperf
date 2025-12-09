//
// Created by apr on 2021-03-24.
//

#include "Blockchain.h"

static Block *_GetLastBlock(Blockchain *this) {
  return &(this->_vChain[this->nrBlock - 1]);
}

void initBlockchain(Blockchain *this, int difficulty) {
  initBlock(&this->_vChain[0], 0, "Genesis Block");
  this->nrBlock = 1;
  this->_nDifficulty = difficulty;
}

const char *AddBlock(Blockchain *this, uint32_t nIndexIn, const char *sDataIn) {
  Block *bLast = _GetLastBlock(this);
  Block *bNew = &this->_vChain[this->nrBlock];
  initBlock(bNew, nIndexIn, sDataIn);
  bNew->sPrevHash = GetHash(bLast);
  MineBlock(bNew, this->_nDifficulty);
  this->nrBlock++;
  return GetHash(bNew);
}
