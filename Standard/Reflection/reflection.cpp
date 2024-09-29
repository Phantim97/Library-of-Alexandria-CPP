#include <variant>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <string>

// Reflection based headers
#include <typeinfo>
#include <cxxabi.h>

class A1
{
private:
	const int id_ = 1;
public:
	void execute() const
	{
		std::cout << "Hello from A" << id_ << "\n\n";
	}
};

class A2
{
private:
	const int id_ = 2;
public:
	void execute() const
	{
		std::cout << "Hello from A" << id_ << "\n\n";
	}
};

class A3
{
private:
	const int id_ = 3;
public:
	void execute() const
	{
		std::cout << "Hello from A" << id_ << "\n\n";
	}
};

// Reflection based logic to demangle the name of the type that the compiler mangled the signature with
// These two functions will provide a string back of the type name
std::string inline demangle(std::string type_name)
{
	int status = 0;
	std::string res = type_name;

	// Use the ABI to demangle the type name
	char* demangled = abi::__cxa_demangle(type_name.c_str(), nullptr, nullptr, &status);

	if (status == 0)
	{
		std::cout << "Demangled Successfully\n";
		res = demangled;
	}
	else
	{
		std::cout << "Failed to demangle\n";
	}

	free(demangled);

	return res;
}

std::string inline get_type(const auto& obj)
{
	const std::type_info& type = typeid(obj);
	const std::string result = demangle(type.name());
	return result;
}

int main()
{
	// Demonstration of variant deducing type with reflection
	using A = std::variant<A1, A2, A3>;

	// Demonstrating a map can be made based on the demangled name derived
	std::unordered_map<std::string, int> a_map =
	{
		{"A1", 1},
		{"A2", 2},
		{"A3", 3}
	};

	const std::vector<A> v =
	{
		A1(),
		A2(),
		A3(),
		A2(),
		A1()
	};

	for (const A& instance: v)
	{
		// Despite being a variant as we can see with lambda we do automatic type deduction
		// We can see it successfully demangled the type
		std::visit([&a_map](const auto& obj)
		{
			std::string type = get_type(obj);
			std::cout << "Type: " << type << " mapped to " << a_map[type] << '\n';
			obj.execute();
		}, instance);
	}

	return 0;
}