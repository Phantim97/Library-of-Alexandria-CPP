#include <iostream>

template <typename T>
struct Property
{
    T value{};

    Property(T value)
    {
        *this = value;
    }

    operator T()
    {
        return value;
    }

    T operator=(T new_value) //this is where assignment happens
    {
        std::cout << "Assignment\n";
        return value = new_value;
    }
};

struct Creature
{  
    Property<int> strength{10};
    Property<int> agility{10};
};

int main()
{
	Creature c;
    c.strength = 11;
	c.agility = 50;

    return 0;
}