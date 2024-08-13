#include <iostream>

int main()
{
	double oneD[3] = { 0.6, 0.2, 0.2 };
	double twoD[3][3];

	double ScalarZ0[3][3];
	double ScalarZ1[3][3];
	double ScalarZ2[3][3];

	/*twoD[0][0] = 0.36;
	twoD[0][1] = 0.12;
	twoD[0][2] = 0.12;
	twoD[1][0] = 0.12;
	twoD[1][1] = 0.04;
	twoD[1][2] = 0.04;
	twoD[2][0] = 0.12;
	twoD[2][1] = 0.04;
	twoD[2][2] = 0.04;*/

	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			twoD[i][k] = oneD[i] * oneD[k];
		}

	}

	std::cout << "1D array\n";
	for (int i = 0; i < 3; i++)
	{
		std::cout << oneD[i] << " ";
	}
	std::cout << "\n\n";

	//check 2D array
	std::cout << "2D array: \n";

	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			std::cout << twoD[i][k] << " ";
		}

		std::cout << '\n';
	}
	std::cout << "\n3D Array:";

	//Scale Arrays by Z-Axis
	std::cout << '\n';
	std::cout << "Scalar Z0:\n";

	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			ScalarZ0[i][k] = twoD[i][k] * .6;
			std::cout << ScalarZ0[i][k] << " ";
		}

		std::cout << '\n';
	}

	std::cout << '\n';
	std::cout << "Scalar Z1:\n";

	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			ScalarZ1[i][k] = twoD[i][k] * .2;
			std::cout << ScalarZ1[i][k] << " ";
		}

		std::cout << '\n';
	}

	std::cout << '\n';
	std::cout << "Scalar Z2:\n";

	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			ScalarZ2[i][k] = twoD[i][k] * .2;
			std::cout << ScalarZ2[i][k] << " ";
		}

		std::cout << '\n';
	}

	std::cout << '\n';

	double sum = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			sum += ScalarZ0[i][k];
			sum += ScalarZ1[i][k];
			sum += ScalarZ2[i][k];
		}
	}

	std::cout << sum << '\n';
	std::cout << '\n';

	std::cout << "3D array.\n";

	double Scale1[3][3][3];
	double Scale2[3][3][3];
	double Scale3[3][3][3];

	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			Scale1[0][i][k] = ScalarZ0[i][k];
			Scale1[1][i][k] = ScalarZ1[i][k];
			Scale1[2][i][k] = ScalarZ2[i][k];
			
			Scale2[0][i][k] = ScalarZ0[i][k];
			Scale2[1][i][k] = ScalarZ1[i][k];
			Scale2[2][i][k] = ScalarZ2[i][k];

			Scale3[0][i][k] = ScalarZ0[i][k];
			Scale3[1][i][k] = ScalarZ1[i][k];
			Scale3[2][i][k] = ScalarZ2[i][k];
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			for (int j = 0; j < 3; j++)
			{
				std::cout << Scale1[i][k][j] << " ";
			
			}

			std::cout << '\n';
		}

		std::cout << '\n';
	}

	std::cout << "Visualizing 4D array.\n";

	for (int z = 0; z < 3; z++)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int k = 0; k < 3; k++)
			{
				std::cout << Scale1[z][i][k] << " ";
			}

			std::cout << "         ";

			for (int j = 0; j < 3; j++)
			{
				std::cout << Scale2[z][i][j] << " ";
			}

			std::cout << "         ";

			for (int m = 0; m < 3; m++)
			{
				std::cout << Scale3[z][i][m] << " ";
			}

			std::cout << '\n';
		}
		std::cout << '\n';
	}

	std::cout << "Scaled by new dimension.\n";

	for (int z = 0; z < 3; z++)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int k = 0; k < 3; k++)
			{
				Scale1[z][i][k] *= .6;
			}

			for (int j = 0; j < 3; j++)
			{
				Scale2[z][i][j] *= .2;
			}

			for (int m = 0; m < 3; m++)
			{
				Scale3[z][i][m] *= .2;
			}
		}
	}

	double sum4D = 0;

	for (int z = 0; z < 3; z++)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int k = 0; k < 3; k++)
			{
				sum4D += Scale1[z][i][k];
			}

			for (int j = 0; j < 3; j++)
			{
				sum4D += Scale2[z][i][j];
			}

			for (int m = 0; m < 3; m++)
			{
				sum4D += Scale3[z][i][m];
			}

		}
		
	}

	for (int z = 0; z < 3; z++)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int k = 0; k < 3; k++)
			{
				std::cout << Scale1[z][i][k] << " ";
			}

			std::cout << "         ";

			for (int j = 0; j < 3; j++)
			{
				std::cout << Scale2[z][i][j] << " ";
			}

			std::cout << "         ";

			for (int m = 0; m < 3; m++)
			{
				std::cout << Scale3[z][i][m] << " ";
			}

			std::cout << '\n';
		}
		std::cout << '\n';
	}

	std::cout << sum4D << '\n';

	return 0;
}