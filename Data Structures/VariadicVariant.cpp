#include <variant>
#include <optional>
#include <iostream>
#include <string>

/* Motivation:
 * The purpose of this is to show off the innate power of SFINAE in variants to allow for an ease of use access/modify
 * different types in a single structure. Variant is a type safe union, so we can leverage this to achieve optimal
 * structure in which the data can be represented in one location without need for wasted memory. Overloads for = and
 * the cast operator for std::optional<U> for seamless =. Only downside here is the necessary use of optional. This is
 * because if you perform std::get on a variant it will throw an exception. Here by using optional we can dodge this by
 * doing a has_value check to circumvent this.
 */

template <typename... Types>
class VariadicVariant
{
private:
	std::variant<std::optional<Types>...> res = {};
public:
	VariadicVariant() = default;

	template <typename T>
	void set(const T& in)
	{
		res = std::optional<T>(in);
	}

	void set(const char* in)
	{
		set<std::string>(std::move(std::string(in)));
	}

	template<typename T>
	VariadicVariant& operator=(const T& in)
	{
		set(in);
		return *this;
	}

	template <typename U>
	operator std::optional<U>() const
	{
		return this->get<U>();
	}

	template <typename U>
	std::optional<U> get() const
	{
		if (std::holds_alternative<std::optional<U>>(res))
		{
			const std::optional<U>& opt = std::get<std::optional<U>>(res);

			if (opt)
			{
				return *opt;
			}
		}
		return std::nullopt;
	}
};

int main()
{
	VariadicVariant<double, std::string, int, bool> r;
	typedef std::optional<std::string> StringOption;
	typedef std::optional<double> DoubleOption;

	r = 543643.0;
	r = "Testing";

	const DoubleOption& x = r;
	if (x.has_value())
	{
		std::cout << x.value() << '\n';
	}
	else
	{
		std::cout << "No value\n";
	}

	const StringOption& s = r;
	if (s.has_value())
	{
		std::cout << s.value() << '\n';
	}

	//Compile Error
	//typedef std::optional<char> CharOption;
	//r = 'a';
	//const std::optional<char> c = r;

	return 0;
}