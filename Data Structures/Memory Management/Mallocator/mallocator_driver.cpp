#include "Mallocator.h"

#include <set>

void mem_main()
{
	using SmallSet = std::set<int, std::less<>, ShortAlloc<int, 512>>;

	ShortAlloc<int, 512>::arena_type stack_arena = SmallSet::allocator_type::arena_type{};
	SmallSet unique_numbers{ stack_arena };

	//Read numbers from stdin
	int n = 0;
	while (std::cin >> n)
	{
		unique_numbers.insert(n);
	}

	//Print unique numbers
	for (const int& number : unique_numbers)
	{
		std::cout << number << '\n';
	}
}
