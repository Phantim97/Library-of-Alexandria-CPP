//Needs to resolve xinput1_X.dll
#include "XboxProfile.h"
#include <iostream>

CXBOXController* Player1;
int main(int argc, char* argv[])
{
	Player1 = new CXBOXController(1);

	std::cout << "Instructions:\n";
	std::cout << "[A] Vibrate Left Only\n";
	std::cout << "[B] Vibrate Right Only\n";
	std::cout << "[X] Vibrate Both\n";
	std::cout << "[Y] Vibrate Neither\n";
	std::cout << "[BACK] Exit\n";

	while (true)
	{
		if (Player1->IsConnected())
		{
			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A)
			{
				Player1->Vibrate(65535, 0);
			}

			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_B)
			{
				Player1->Vibrate(0, 65535);
			}

			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_X)
			{
				Player1->Vibrate(65535, 65535);
			}

			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_Y)
			{
				Player1->Vibrate();
			}

			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
			{
				break;
			}
		}
		else
		{
			std::cout << "\n\tERROR! PLAYER 1 - XBOX 360 Controller Not Found!\n";
			std::cout << "Press Any Key To Exit.";
			std::cin.get();
			break;
		}
	}

	delete(Player1);

	return(0);
}
