#include <iostream>
#include <conio.h>

int factorial(int x)
{
	if (x < 1) //base case
		return 1;
	else
		return factorial(x-1) * x;
}

void setParams(int *n, int *r)
{
	int numT = 0;
	std::cout << "Enter Total Number of elements: ";
	do
	{
		std::cin >> numT;
	} while (n < 0);

	*n = numT;
	
	int numR = 0;
	std::cout << "How many from the set you are selecting: ";
	do
	{
		std::cin >> numR;
	} while (n < 0 || numR > numT);

	*r = numR;
}

int main()
{
	char probChoice;
	std::cout << "Are you p.) picking(order matters) or c.)choosing(order doesn't matter)\n";
	do
	{
		probChoice = _getch();
	} while ((probChoice != 'p' && probChoice != 'P') && (probChoice != 'c' && probChoice != 'C'));

	std::cout << "Current mode: " << probChoice << '\n';

	int *n = new int;
	int *r = new int;
	setParams(n, r);

	int totalOutcomes;

	if (probChoice == 'p' || probChoice == 'P')
	{
		totalOutcomes = (factorial(*n) / factorial(*n - *r));
		std::cout << *n << "P" << *r << " = " << totalOutcomes << '\n';
	}
	else if (probChoice == 'c' || probChoice == 'C')
	{
		totalOutcomes = factorial(*n) / (factorial(*r)*(factorial(*n - *r)));
		std::cout << *n << "P" << *r << " = " << totalOutcomes << '\n';
	}

	delete n;
	delete r;
	return 0;
}