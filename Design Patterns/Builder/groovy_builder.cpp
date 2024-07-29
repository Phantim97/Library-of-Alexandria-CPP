#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <tuple>

struct Tag
{
    std::string name;
    std::string text;
    std::vector<Tag> children;
    std::vector<std::pair<std::string, std::string>> attributes;

	[[nodiscard]] std::string to_string() const
	{
		std::ostringstream os;
		os << "<" << name;

		for (const std::pair<std::string, std::string>& att : attributes)
		{
			os << " " << att.first << "=\"" << att.second << "\"";
		}

		if (children.empty() && text.empty())
		{
			os << "/>\n";
		}
		else
		{
			os << ">\n";

			if (!text.empty())
			{
				os << text << '\n';
			}

			for (const Tag& child : children)
			{
				os << child.to_string();
			}

			os << "</" << name << ">\n";
		}

		return os.str();
	}

	friend std::ostream& operator<<(std::ostream& os, const Tag& tag)
	{
		os << tag.to_string();
		return os;
	}

protected:
public:
    Tag(const std::string &name, const std::string &text) : name(name), text(text) {}
    Tag(const std::string &name, const std::vector<Tag> &children) : name(name), children(children) {}

};

struct P : Tag
{
    P(const std::string &text) : Tag("p", text) {}
    P(std::initializer_list<Tag> children) : Tag("p", children) {}
};

struct IMG : Tag
{
    explicit IMG(const std::string url) : Tag("img", "") 
    {
        attributes.emplace_back(std::make_pair("src", url));
    }
};

int main()
{
    std::cout << 

        P{
            IMG { "https://pokemon.com/pikachu.png" }
        }

        << '\n';
    return 0;
}