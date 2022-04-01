#include "ScopedTimer.h"

void f1()
{
	ScopedTimer<std::chrono::milliseconds> st;

	long double sum = 0.0;

	for (int i = 0; i < 10000000; i++)
	{
		sum += i * 65.463;
	}
}

void f2()
{
	ScopedTimer<std::chrono::nanoseconds> st;

	long double sum = 0.0;

	for (int i = 0; i < 10000000; i++)
	{
		sum += i * 65.463;
	}
}

int main()
{
	f1();
	f2();
  
  return 0;
}
