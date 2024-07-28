#include <iostream>
#include <string>
#include <vector>

// Enums for product properties
enum class Color
{
	red, green, blue
};
enum class Size
{
	small, medium, large
};

// Product structure
struct Product
{
	std::string name;
	Color color;
	Size size;
};

// Basic filter using standard functions
struct ProductFilter
{
	std::vector<Product *> by_color(const std::vector<Product *> &items, Color color)
	{
		std::vector<Product *> result;
		for (Product* const &i: items)
		{
			if (i->color == color)
			{
				result.push_back(i);
			}
		}
		return result;
	}

	std::vector<Product *> by_size(const std::vector<Product *> &items, Size size)
	{
		std::vector<Product *> result;
		for (Product* const &i: items)
		{
			if (i->size == size)
			{
				result.push_back(i);
			}
		}
		return result;
	}
};

// Specification interface
template<typename T>
struct Specification
{
	virtual bool is_satisfied(T *item) = 0;

	::Specification<T> operator&&(Specification<T> &other)
	{
		return AndSpecification<T>(*this, other);
	}
};

// Filter interface
template<typename T>
struct Filter
{
	virtual std::vector<T *> filter(std::vector<T *> items, Specification<T> &spec) = 0;
};

// Better filter implementing the filter interface
struct BetterFilter : Filter<Product>
{
	std::vector<Product *> filter(std::vector<Product *> items, Specification<Product> &spec) override
	{
		std::vector<Product *> result;
		for (Product* const &i: items)
		{
			if (spec.is_satisfied(i))
			{
				result.push_back(i);
			}
		}
		return result;
	}
};

// Color specification implementing the specification interface
struct ColorSpecification : Specification<Product>
{
	Color color;

	ColorSpecification(Color color) : color(color)
	{
	}

	bool is_satisfied(Product *item) override
	{
		return item->color == color;
	}
};

// Size specification implementing the specification interface
struct SizeSpecification : Specification<Product>
{
	Size size;

	SizeSpecification(Size size) : size(size)
	{
	}

	bool is_satisfied(Product *item) override
	{
		return item->size == size;
	}
};

// And specification combining two specifications
template<typename T>
struct AndSpecification : Specification<T>
{
	Specification<T> &first;
	Specification<T> &second;

	AndSpecification(Specification<T> &first, Specification<T> &second) : first(first), second(second)
	{
	}

	bool is_satisfied(T *item) override
	{
		return first.is_satisfied(item) && second.is_satisfied(item);
	}
};

int main()
{
	Product apple {"Apple", Color::green, Size::small};
	Product tree {"Tree", Color::green, Size::large};
	Product house {"House", Color::blue, Size::large};

	std::vector<Product *> items {&apple, &tree, &house};

	ProductFilter pf;
	std::vector<Product *> green_things = pf.by_color(items, Color::green);

	BetterFilter bf;
	ColorSpecification green(Color::green);

	for (Product* const &item: bf.filter(items, green))
	{
		std::cout << item->name << " is green\n";
	}

	SizeSpecification large(Size::large);
	AndSpecification<Product> green_and_large(green, large);

	for (Product *&item: bf.filter(items, green_and_large))
	{
		std::cout << item->name << " is green and large\n";
	}

	return 0;
}
