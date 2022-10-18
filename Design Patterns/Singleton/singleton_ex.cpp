#include <iostream>
#include <string>
#include <fstream>
#include <map>

#include <boost/lexical_cast.hpp>

using namespace boost;

class SingletonDatabase
{
    SingletonDatabase()
    {
        std::cout << "Initializing Database";
        std::ifstream ifs("capitals.txt");

        std::string s, s2;

        while (std::getline(ifs, s))
        {
            std::getline(ifs, s2);
            int pop = boost::lexical_cast<int>(s2);
            capitals[s] = pop;
        }
    }
    std::map<std::string, int> capitals;
    
    public:
    SingletonDatabase(SingletonDatabase const&) = delete;
    void operator=(SingletonDatabase const&) = delete;

    static SingletonDatabase& get()
    {
        static SingletonDatabase db;
        return db;
    }

    int get_population(const std::string& name)
    {
        return capitals[name];
    }
};

int main()
{
    SingletonDatabase::get().get_population("Tokyo");

    return 0;
}