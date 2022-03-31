#include <iostream>

#include "ScopedTimer.h"

#include <omp.h>

constexpr int n = 10000000;

double sum()
{
	ScopedTimer t;

	long double sum = 0.0;
	for (int i = 0; i < n; i++)
	{
		sum += i * 43.879;
	}

	return sum;
}

double parallel_sum()
{
	ScopedTimer t;
	long double sum = 0.0;

	#pragma omp parallel for reduction(+ : sum)
	for (int i = 0; i < n; i++)
	{
		sum += i * 43.879;
	}

	return sum;
}

int main()
{
  std::cout << "Single threaded:\n";
	sum();
  
  std::cout << "Multi threaded:\n";
	parallel_sum();

	return 0;
}
