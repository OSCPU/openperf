//
// Created by apr on 2021-03-24.
//

#ifndef BLOCKCHAIN_BLOCKCHAIN_H
#define BLOCKCHAIN_BLOCKCHAIN_H
#include "Block.h"
#include <cstdint>
#include <vector>

using namespace std;

class Blockchain {
public:
  Blockchain();

  void AddBlock(Block bNew);

private:
  uint32_t _nDifficulty;
  vector<Block> _vChain;

  Block _GetLastBlock() const;
};

#endif //BLOCKCHAIN_BLOCKCHAIN_H
