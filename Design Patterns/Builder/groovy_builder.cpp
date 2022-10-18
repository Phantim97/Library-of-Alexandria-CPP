#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include <tuple>
#include <fstream>

struct Tag
{
    std::string name;
    std::string text;
    std::vector<Tag> children;
    std::vector<std::pair<std::string, std::string>> attributes;

    friend std::ostream& operator<<(std::ostream& os, const Tag& tag)
    {
        os << "<" << tag.name;

        for (const std::pair<std::string, std::string> att : tag.attributes)
        {
            os << " " << att.first << "=\"" << att.second << "\'";
        }

        if (tag.children.size() == 0 && tag.text.length() == 0)
        {
            os << "/>\n"; 
        }
        else
        {
            os << ">\n";

            if (tag.text.length())
            {
                os << tag.text << '\n';
            }

            for (const auto& child : tag.children)
            {
                os << child;
            }

            os << "</" << tag.name << ">\n";
        }

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