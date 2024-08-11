#include <iostream>

void matrixMultipliacation(double** p0, double** pt, int elements, int transition)
{
	double **tempArray = new double*[elements];
	for (int i = 0; i < elements; i++)
	{
		tempArray[i] = new double[elements];
	}

	for (int i = 0; i < elements; i++)
	{
		for (int k = 0; k < elements; k++)
		{
			for (int j = 0; j < elements; j++)
			{ 
				pt[i][k] += (p0[i][j] * p0[j][k]);
			}
		}
	}

	if (transition > 1)
	{
		for (int i = 0; i < elements; i++)
		{
			for (int k = 0; k < elements; k++)
			{
				for (int j = 0; j < elements; j++)
				{
					pt[i][k] += (p0[i][j] * p0[j][k]);
				}
			}
		}
	}
}

bool rowCheck(double **p0, int elem)
{
	for (int i = 0; i < elem; i++)
	{
		int sum = 0;
		for (int k = 0; k < elem; k++)
		{
			sum += p0[i][k];
		}

		if (sum != 1)
		{
			return false;
		}

	}
}

void printMatrix(double** p, int elem)
{
	for (int i = 0; i < elem; i++)
	{
		for (int k = 0; k < elem; k++)
		{
			std::cout << p[i][k] << " ";
		}

		std::cout << '\n';
	}

}

void chain()
{
	int elements;
	std::cout << "Enter how many stages: ";
	do
	{
		std::cin >> elements;
	} while (elements < 1);

	double **transitionMatrix = new double*[elements];
	for (int i = 0; i < elements; i++)
	{
		transitionMatrix[i] = new double[elements];
	}

	double **finalMatrix = new double*[elements];
	for (int i = 0; i < elements; i++)
	{
		finalMatrix[i] = new double[elements];
	}

	for (int i = 0; i < elements; i++)
	{
		for (int k = 0; k < elements; k++)
		{
			finalMatrix[i][k] = 1;
		}
	}

	for (int i = 0; i < elements; i++)
	{
		for (int k = 0; k < elements; k++)
		{
			std::cout << "Probability of stage " << i + 1 << " to stage " << k + 1 << ": ";
			do
			{
				std::cin >> transitionMatrix[i][k];
			} while (transitionMatrix[i][k] > 1 || transitionMatrix[i][k] < -1);

		}

	}

	printMatrix(transitionMatrix, elements);

	std::cout << "How many transitions would you like to perform: ";
	int transitions;
	do
	{
		std::cin >> transitions;
	} while (transitions < 0);

	for (int i = 0; i < transitions; i++)
	{
		matrixMultipliacation(transitionMatrix, finalMatrix, elements, transitions);
	}

	printMatrix(finalMatrix, elements);

	for (int i = 0; i < elements; i++)
	{
		delete[] transitionMatrix[i];
	}
	delete[] transitionMatrix;

	for (int i = 0; i < elements; i++)
	{
		delete[] finalMatrix[i];
	}
	delete[] finalMatrix;

}
