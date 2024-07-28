#include <map>
#include <memory>
#include <iostream>

enum class Importance
{
    primary,
    secondary,
    tertiary
};

template <typename T, typename Key = std::string>
class Multiton
{
    public:
        static std::shared_ptr<T> get(const Key& key)
        {
            const auto it = instances.find(key);
			if (it != instances.end())
			{
                    return it->second;
			}
			else
			{
                    auto instance = std::make_shared<T>();
                    instances[key] = instance;
					return instance;
			}
        }
    protected:
    Multiton() = default;

    private:
        static std::map<Key, std::shared_ptr<T>> instances;
};

template <typename T, typename Key>
std::map<Key, std::shared_ptr<T>> Multiton<T, Key>::instances;

class Printer
{
    public:
	static int totalInstanceCount;

    Printer()
    {
        ++Printer::totalInstanceCount;
        std::cout << "A total of " << Printer::totalInstanceCount << " instances created so far\n";
    }
};

int Printer::totalInstanceCount = 0;

int main()
{
    typedef Multiton<Printer, Importance> mt;
    //only one of each enum created
    std::shared_ptr<Printer> main1 = mt::get(Importance::primary);
	std::shared_ptr<Printer> aux = mt::get(Importance::secondary);
	std::shared_ptr<Printer> aux2 = mt::get(Importance::tertiary);

    return 0;
}