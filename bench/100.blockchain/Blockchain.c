//
// Created by apr on 2021-03-24.
//

#include "Blockchain.h"

Blockchain::Blockchain() {
  _vChain.emplace_back(Block(0, "Genesis Block"));
  _nDifficulty = 6;
}

void Blockchain::AddBlock(Block bNew) {
  bNew.sPrevHash = _GetLastBlock().GetHash();
  bNew.MineBlock(_nDifficulty);
  _vChain.push_back(bNew);
}

Block Blockchain::_GetLastBlock() const {
  return _vChain.back();
}
