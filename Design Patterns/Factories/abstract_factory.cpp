#include <iostream>
#include <memory>
#include <map>
#include <functional>

struct HotDrink
{
    virtual ~HotDrink() = default;
    virtual void perpare(int volume) = 0;
};

struct HotDrinkFactory //abstract factory
{
    virtual std::unique_ptr<HotDrink> make() const = 0;
};

struct TeaFactory : HotDrinkFactory
{
    std::unique_ptr<HotDrink> make() const override
    {
        return std::make_unique<Tea>();
    }
};

struct CoffeeFactory : HotDrinkFactory
{
    std::unique_ptr<HotDrink> make() const override
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
            std::unique_ptr<HotDrink> = hot_factories[name]->make();
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
        factories["tea"] = [] { std::unique_ptr<Tea> tea = std::make_unique<Tea>();
        tea->perpare();
        return tea;
    }

    std::unique_ptr<HotDrink> make_drink(const std::string &name)
    {
        return factories[name](); //functional by invoking constructor
    }
}

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

// std::unique_ptr<HotDrink> make_drink(std::string type)
// {
//     std::unique_ptr<HotDrink> drink;
//     if (type == "Tea")
//     {
//         drink = std::make_unique<Tea>();
//         drink->perpare();
//     }
//     else
//     {
//         drink = std::make_unique<Coffee>();
//         drink->perpare();
//     }

//     return drink;
    
// }

int main()
{
    DrinkFactory df;
    std::unique_ptr<HotDrink> c = df.make_drink("Coffee");

    return 0;
}