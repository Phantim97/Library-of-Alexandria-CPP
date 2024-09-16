#include <cmath>
#include <random>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <chrono>

double integrate(int n)
{
	std::mt19937 generator;
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	double sum = 0;
	
	for (int i = 0; i < n; i++)
	{
		sum += pow(cos(dist(generator)), 2);
	}

	
	return sum / n;
}

int main()
{
	for (int i = 0; i <= 6; i++)
	{
		std::cout << pow(10, i) << ":" << integrate(pow(10, i)) << '\n';
	}

	return 0;
}