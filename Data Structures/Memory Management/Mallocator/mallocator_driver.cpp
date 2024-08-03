#include "Mallocator.h"
#include "FixedSizeAlloc.h"

#include <set>

void mallocator_ex()
{
	std::cout << "Mallocator Example: \n";
	using MallocSet = std::set<int, std::less<>, Mallocator<int>>;
	MallocSet unique_numbers;

	//Read numbers from stdin
	int n = 0;
	constexpr size_t input_sz = 10;
	for (size_t i = 0; i < input_sz; i++)
	{
		try
		{
			std::cin >> n;
			if (std::cin.fail())
			{
				throw std::exception();
			}
		}
		catch (std::exception& e)
		{
			std::cerr << "Error Invalid input\n";
			std::cin.clear();
			std::cin.ignore(999999, '\n');
			i -= 1; //Give an extra iteration
		}

		unique_numbers.insert(n);
	}

	//Print unique numbers
	for (const int& number : unique_numbers)
	{
		std::cout << number << '\n';
	}
}

void fixed_sz_alloc_ex()
{
	std::cout << "Fixed Size Allocator Example: \n";
	using SmallSet = std::set<int, std::less<>, FixedSizeAlloc<int, 512>>;

	FixedSizeAlloc<int, 512>::arena_type stack_arena = SmallSet::allocator_type::arena_type{};
	SmallSet unique_numbers{ stack_arena };

	int n = 0;
	constexpr size_t input_sz = 10;
	for (size_t i = 0; i < input_sz; i++)
	{
		try
		{
			std::cin >> n;
			if (std::cin.fail())
			{
				throw std::exception();
			}
		}
		catch (std::exception& e)
		{
			std::cerr << "Error Invalid input\n";
			std::cin.clear();
			std::cin.ignore(999999, '\n');
			i -= 1; //Give an extra iteration
			continue;
		}

		unique_numbers.insert(n);
	}

	//Print unique numbers
	for (const int& number : unique_numbers)
	{
		std::cout << number << '\n';
	}
}

int main()
{
	mallocator_ex();
	fixed_sz_alloc_ex();

	return 0;
}
