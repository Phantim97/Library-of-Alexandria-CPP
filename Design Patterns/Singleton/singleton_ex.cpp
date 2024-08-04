#include <iostream>
#include <string>
#include <fstream>
#include <map>

#include <boost/lexical_cast.hpp>

class SingletonDatabase
{
    SingletonDatabase()
    {
        std::cout << "Initializing Database\n";
        std::ifstream ifs("capitals.txt");

        std::string s;
		std::string s2;

        while (std::getline(ifs, s))
        {
            std::getline(ifs, s2);
            int pop = boost::lexical_cast<int>(s2);

			if (pop > 0) //Negative population is invalid
			{
				capitals[s] = static_cast<size_t>(pop);
			}
        }
    }

    std::map<std::string, size_t> capitals;
    
    public:
    SingletonDatabase(SingletonDatabase const&) = delete;
    void operator=(SingletonDatabase const&) = delete;

    static SingletonDatabase& get()
    {
        static SingletonDatabase db;
        return db;
    }

    size_t get_population(const std::string& name)
    {
        return capitals[name];
    }

	void print_city_info(const std::string& name)
	{
		if (capitals.find(name) != capitals.end())
		{
			std::cout << "Population of " << name << " is " << capitals[name] << '\n';
		}
		else
		{
			std::cerr << "Error: City not found\n";
		}
	}
};

void generate_database()
{
	std::ofstream capital_db("capitals.txt");

	//Populate file with info
	if (capital_db.is_open())
	{
		capital_db << "Tokyo\n37435191\nNew York\n8175133\nLos Angeles\n3792621\nParis\n2148327\nLondon\n8982000\nBerlin\n3769495";
		capital_db.close();
	}
	else
	{
		std::cerr << "Error opening file\n";
	}
}

int main()
{
	generate_database();

	SingletonDatabase* sdb = &SingletonDatabase::get();
	sdb->print_city_info("Tokyo");

	SingletonDatabase::get().print_city_info("New York"); //Alternative calling method
    return 0;
}