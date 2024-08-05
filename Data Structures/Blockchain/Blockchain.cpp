#include "Blockchain.h"

Blockchain::Blockchain(const uint32_t difficulty)
{
	_chain.emplace_back(Block(0, "Genesis Block")); //Initial block of the chain
	_difficulty = difficulty;
}

void Blockchain::add_block(Block b)
{
	b.prev_hash = _get_last_block().get_hash();
	b.mine_block(_difficulty);
	_chain.push_back(b);
}

Block Blockchain::_get_last_block() const
{
	return _chain.back();
}
