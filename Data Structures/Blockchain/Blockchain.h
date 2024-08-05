#pragma once
#include <cstdint>
#include <vector>
#include "Block.h"

class Blockchain
{
private:
	uint32_t _difficulty;
	std::vector<Block> _chain;
	Block _get_last_block() const;
public:
	explicit Blockchain(const uint32_t difficulty);
	void add_block(Block b);
};
