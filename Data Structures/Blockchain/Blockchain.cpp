#include "Blockchain.h"

Blockchain::Blockchain()
{
	_chain.emplace_back(Block(0, "Genesis Block")); //Initial block of the chain

	_difficulty = 6;
}

void Blockchain::addBlock(Block bNew)
{
	bNew.prevHash = _get_last_block().get_hash();
	bNew.mine_block(_difficulty);
	_chain.push_back(bNew);
}

Block Blockchain::_get_last_block() const
{
	return _chain.back();
}
