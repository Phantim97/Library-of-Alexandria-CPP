#include <iostream>
#include <array>
#include <numeric> //std::accumulate

enum Stats
{
	str,
	agl,
	intl
};

class Creature
{
private:
	static const int stat_sz = intl + 1;
	std::array<int, stat_sz> abilities{}; //count = size of array

public:
	int operator[](const Stats stat) const
	{
		return abilities[stat];
	}

	int& operator[](const Stats stat)
	{
		return abilities[stat];
	}

    [[nodiscard]] int sum() const
    {
        return std::accumulate(abilities.begin(), abilities.end(), 0); //accumulate sums a std::array
    }

	[[nodiscard]] double average() const
    {
        return sum() / (double)stat_sz;
    }

	[[nodiscard]] int max() const
    {
        return *std::max_element(abilities.begin(), abilities.end());
    }
};

int main()
{
    Creature orc;
    orc[str] = 16;
	orc[intl] = 2;
	orc[agl] = 5;

	std::cout << orc[str] << '\n';
    std::cout << orc.sum() << '\n';
    std::cout << orc.average() << '\n';
    std::cout << orc.max() << '\n';

    return 0;
}