#pragma once
#include <cstdint>
#include <iostream>

class Block
{
private:
	uint32_t _index;
	int64_t _nonce;
	std::string _data;
	std::string _hash;
	time_t _time;
	std::string _calculate_hash() const;
public:
	std::string prevHash;
	Block(uint32_t index_in, const std::string& data_in);
	std::string get_hash();
	void mine_block(uint32_t difficulty);
};
