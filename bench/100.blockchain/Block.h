//
// Created by apr on 2021-03-24.
//

#ifndef BLOCKCHAIN_BLOCK_H
#define BLOCKCHAIN_BLOCK_H

#include <cstdint>
#include <iostream>

using namespace std;

class Block {
public:
  string sPrevHash;

  Block(uint32_t nIndexIn, const string &sDataIn);

  string GetHash();

  void MineBlock(uint32_t nDifficulty);

private:
  uint32_t _nIndex;
  int64_t _nNonce;
  string _sData;
  string _sHash;
  time_t _tTime;

  string _CalculateHash() const;
};

#endif //BLOCKCHAIN_BLOCK_H
