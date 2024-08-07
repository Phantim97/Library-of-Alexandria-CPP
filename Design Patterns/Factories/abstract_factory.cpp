#include <iostream>
#include <map>
#include <functional>

// Forward declarations of Tea and Coffee
struct Tea;
struct Coffee;

struct HotDrink
{
	virtual ~HotDrink() = default;
	virtual void prepare(int volume) = 0;
};

struct HotDrinkFactory //abstract factory
{
	virtual ~HotDrinkFactory() = default; // Add virtual destructor
	[[nodiscard]] virtual std::unique_ptr<HotDrink> make() const = 0;
};

struct Tea : HotDrink
{
	void prepare(int volume) override
	{
		std::cout << "Take tea bag, boil water, pour " << volume << " ml. add some lemon\n";
	}
};

struct Coffee : HotDrink
{
	void prepare(int volume) override
	{
		std::cout << "Grind some beans, boil water, pour " << volume << " ml. add some cream\n";
	}
};

struct TeaFactory : HotDrinkFactory
{
	[[nodiscard]] std::unique_ptr<HotDrink> make() const override
	{
		return std::make_unique<Tea>();
	}
};

struct CoffeeFactory : HotDrinkFactory
{
	[[nodiscard]] std::unique_ptr<HotDrink> make() const override
	{
		return std::make_unique<Coffee>();
	}
};

class DrinkFactory
{
private:
	std::map<std::string, std::unique_ptr<HotDrinkFactory>> hot_factories;

public:
	DrinkFactory()
	{
		hot_factories["Coffee"] = std::make_unique<CoffeeFactory>();
		hot_factories["Tea"] = std::make_unique<TeaFactory>();
	}

	std::unique_ptr<HotDrink> make_drink(const std::string &name)
	{
		std::unique_ptr<HotDrink> drink = hot_factories[name]->make();
		drink->prepare(200);
		return drink;
	}
};

//functional factory
class DrinkWithVolumeFactory
{
	std::map<std::string, std::function<std::unique_ptr<HotDrink>()>> factories;
public:
	DrinkWithVolumeFactory()
	{
		factories["tea"] = []() -> std::unique_ptr<HotDrink>
		{
			std::unique_ptr<Tea> tea = std::make_unique<Tea>();
			tea->prepare(5);
			return tea;
		};

		factories["coffee"] = []() -> std::unique_ptr<HotDrink>
		{
			std::unique_ptr<Coffee> coffee = std::make_unique<Coffee>();
			coffee->prepare(5);
			return coffee;
		};
	}

	std::unique_ptr<HotDrink> make_drink(const std::string &name)
	{
		return factories[name](); //functional by invoking constructor
	}
};

int main()
{
	DrinkFactory df;
	std::unique_ptr<HotDrink> c = df.make_drink("Coffee");

	DrinkWithVolumeFactory dvf;
	std::unique_ptr<HotDrink> t = dvf.make_drink("tea");

	return 0;
}
