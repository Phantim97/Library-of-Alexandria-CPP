#include <iostream>
#include <vector>
#include "Embedded.h"

std::vector<std::string> cmds {"EXEC", "DO", "SOMETHING", "BEEP", "BOOP"};

int main()
{
	Embedded e("COM6");

	Embedded e2;
	e2.open("COM7");
	
	e.send(cmds[0]);
	std::string res = e.get_data();

	if (strstr(res.c_str(), "result") != nullptr)
	{
		std::cout << "Found result\n";
	}
	
	return 0;
}
