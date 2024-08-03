#include "Blockchain.h"

int main()
{
	Blockchain chain = Blockchain(6);

	std::cout << "Mining block 1...\n";
	chain.add_block(Block(1, "Block 1 Data"));

	std::cout << "Mining block 2...\n";
	chain.add_block(Block(2, "Block 2 Data"));

	std::cout << "Mining block 3...\n";
	chain.add_block(Block(3, "Block 3 Data"));
	
	return 0;
}
