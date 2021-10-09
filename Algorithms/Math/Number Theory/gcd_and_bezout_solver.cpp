#include <functional>
#include <iostream>
#include <optional>

namespace nt
{
	class Divisibility
	{
	public:
		static int gcd(int a, int b)
		{
			if (a > b)
			{
				const int temp = a;
				a = b;
				b = temp;
			}

			int r = 0;

			while (true)
			{
				r = b % a;

				if (r == 0)
				{
					break;
				}
				
				b = a;
				a = r;
			}

			std::cout << "GCD: " << a << '\n';
			return a;
		}

		static void bezout_solver(const int a, const int b, const int c)
		{
			int x = 1;
			int y = 1;
			int k = 0;
			const int d = gcd(a, b);

			if (c != d)
			{
				if (c % d != 0)
				{
					std::cout << "No Solution\n";
					return;
				}
			
				k = c / d;
			}

			std::function<std::tuple<int,int>(int, int)> bez_vars = [&](int a1, int b1)
			{
				if (a1 == 0)
				{
					return std::make_tuple(0, 1);
				}
				
				int x1, y1;

				std::tie(x1, y1) = bez_vars(b1 % a1, a1); //multiple std::get<>() in a single capture with tie

				return std::make_tuple((y1 - (b1 / a1) * x1), x1);
			};
			
			std::tuple<int, int> t = bez_vars(a, b);

			x = std::get<0>(t);
			y = std::get<1>(t);
			
			if (k > 0)
			{
				x *= k;
				y *= k;
			}
			else
			{
				k = 1;
			}

			std::cout << "Solution: " << a << " * " << x << "  +  " << b << " * " << y << "  =  " << c << " * " << k << '\n';
		}
	};
};

int main()
{
	nt::Divisibility::gcd(153, 216);
	nt::Divisibility::bezout_solver(216, 153, 171);
	return 0;
}
