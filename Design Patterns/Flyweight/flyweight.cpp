#include <iostream>
#include <string>
#include <boost/bimap.hpp>
#include <cstdint>

typedef uint16_t key;

struct User
{
	User(const std::string& first_name, const std::string& last_name)
			: first_name{add(first_name)}, last_name{add(last_name)} {}

	[[nodiscard]] const std::string& get_first_name() const
	{
		return names.left.find(first_name)->second;
	}

	[[nodiscard]] const std::string& get_last_name() const
	{
		return names.left.find(last_name)->second;
	}

protected:
	key first_name;
	key last_name;
	static boost::bimap<key, std::string> names; // bimap allows you to search for key by value and value by key
	static key seed;

	static key add(const std::string &name)
	{
		auto it = names.right.find(name); // search for the string in values
		if (it == names.right.end()) // key not found
		{
			key id = ++seed;
			names.insert({id, name});
			return id;
		}

		return it->second; // gets the key
	}
};

key User::seed{0};
boost::bimap<key, std::string> User::names{};

std::ostream &operator<<(std::ostream &os, const User &user)
{
	os << "first_name: " << user.get_first_name() << " last name: " << user.get_last_name() << '\n';
	return os;
}

// boost also has its own flyweight implementation

int main()
{
	User u1{"John", "Smith"};
	User u2{"Jane", "Smith"};

	std::cout << u1 << '\n';
	std::cout << u2 << '\n';

	// last name has an identical index in the map
	return 0;
}
