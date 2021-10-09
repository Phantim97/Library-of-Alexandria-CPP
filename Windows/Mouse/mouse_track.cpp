#include <Windows.h>
#include <iostream>

int main()
{
	POINT p;

	for (int i = 0; i < 30; i++)
	{
		if (GetCursorPos(&p))
		{
			std::cout << "X: " << p.x << " || Y: " << p.y << '\n';
		}

		Sleep(1000);
	}

	return 0;
}
