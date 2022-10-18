#include <iostream>
#include <vector>
#include <array>
#include <numeric> //std::accumulate
#include <algorithm> //std::max_element

// class Creature
// {
//     int str;
//     int agil;
//     int intl;

// public:

//     void set_strength(int s)
//     {
//         this->str = s;
//     }
    
//     int get_strength() const
//     {
//         return this->str;
//     }

//     void set_agility(int a)
//     {
//         this->agil = a;
//     }

//     int get_agility() const
//     {
//         return this->agil;
//     }

//     void set_intelligence(int i)
//     {
//         this->intl = i;
//     }
    
//     int get_intelligence() const
//     {
//         return this->intl;
//     }

//     //these functions are not well scalable
//     double sum() const
//     {
//         return str + agil + intl;
//     }

//     double average() const
//     {
//         return sum() / 3.0;
//     }

//     int max() const
//     {
//         return std::max(std::max(str, agil), intl);
//     }
// };

class Creature
{
    enum Abilities 
    {
        str,
        agl,
        intl,
        count //the final enum can be used to get the total count of enums here it is 3
    };

    std::array<int, count> abilities; //count = size of array

    public:
    int get_strength() const
    {
        return abilities[str];
    }

    void set_strength(int s)
    {
        abilities[str] = s;
    }

    int sum() const
    {
        return std::accumulate(abilities.begin(), abilities.end(), 0); //accumulate sums a std::array
    }

    double average() const
    {
        return sum() / (double)count;
    }

    int max() const
    {
        return *std::max_element(abilities.begin(), abilities.end());
    }
};

int main()
{
    Creature orc;
    orc.set_strength(16);

    std::cout << orc.sum() << '\n';
    std::cout << orc.average() << '\n';
    std::cout << orc.max() << '\n';

    return 0;
}