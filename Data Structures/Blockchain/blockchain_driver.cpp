#include "Blockchain.h"

int main()
{
	Blockchain bChain = Blockchain();

	std::cout << "Mining block 1...\n";
	bChain.addBlock(Block(1, "Block 1 Data"));

	std::cout << "Mining block 2...\n";
	bChain.addBlock(Block(2, "Block 2 Data"));

	std::cout << "Mining block 3...\n";
	bChain.addBlock(Block(3, "Block 3 Data"));
	
	return 0;
}
