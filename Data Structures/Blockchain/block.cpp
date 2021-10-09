#include "Block.h"
#include <ctime>
#include <sstream>
#include "sha256.h"

Block::Block(uint32_t index_in, const std::string& data_in)
{
	_nonce = -1;
	_time = time(0);
}

std::string Block::get_hash()
{
	return _hash;
}

void Block::mine_block(uint32_t difficulty)
{
	char *cstr = new char[difficulty + 1];

	for (uint32_t i = 0; i < difficulty; i++)
	{
		cstr[i] = '0';
	}

	cstr[difficulty] = '\0';

	std::string str(cstr);

	delete cstr;
	
	do
	{
		_nonce++;
		_hash = _calculate_hash();
	} while (_hash.substr(0, difficulty) != str);

	std::cout << "Block mined: " << _hash << '\n';
}

std::string Block::_calculate_hash() const
{
	std::stringstream ss;
	ss << _index << _time << _data << _nonce << prevHash;

	return sha256(ss.str());
}
