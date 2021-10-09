#include <iostream>
#include <stdio.h>
#include <cassert>
#include <string>

int main()
{
	std::cout << "Original: ";
	std::string cap;
	char buffer[256];
	memset(buffer, 0, 256);

	FILE* pipe = _popen("ipconfig", "r");
	if (!pipe)
	{
		std::cout << "Failed to open pipe\n";
		assert(false);
	}

	while (fgets(buffer, sizeof(buffer), pipe) != NULL)
	{
		cap.append(buffer);
	}

	system("cls");
	std::cout << "Captured: ";
	std::cout << cap << '\n';
	system("pause");

	return 0;
}
