#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <vector>

struct HtmlBuilder;

class HtmlElement //Models HTML element
{
    friend class HtmlBuilder; //allows Html Builder to use constructors, builder controls HTML element access
    std::string name;
    std::string text;
    std::vector<HtmlElement> elements;

    const size_t indent_size = 2;

    HtmlElement() {}

    HtmlElement(const std::string &name, const std::string &text) : name(name), text(text) {}

public:
    std::string str(int indent=0) const //recursive invokation, formats string structure
    {
        std::ostringstream oss;
        std::string i(indent_size * indent, ' ');
        oss << i << "<" << name << ">" << '\n';
        if (text.size() > 0)
        {
            oss << std::string(indent_size * (indent + 1), ' ') << text << '\n';
        }

        for (const HtmlElement& e : elements)
        {
            oss << e.str(indent + 1);
        }

        oss << i << "</" << name << ">" << '\n';
        
        return oss.str();
    }

    static HtmlBuilder build(const std::string& root_name)
    {
        return {root_name}; // the use of {} is used to infer the type
    }

};

struct HtmlBuilder
{
    HtmlElement root;

    HtmlBuilder(std::string root_name)
    {
        root.name = root_name;
    }

    HtmlBuilder& add_child(std::string child_name, std::string child_text)
    {
        HtmlElement e(child_name, child_text);
        root.elements.emplace_back(e);
        return *this;
    }

    HtmlBuilder* add_child_2(std::string child_name, std::string child_text)
    {
        HtmlElement e(child_name, child_text);
        root.elements.emplace_back(e);
        return this;
    }

    operator HtmlElement() const {return root;} //used to convert 

    std::string str() const { return root.str();}
};

int main()
{
    //W/O builders
    const char* text = "hello";
    std::string output;
    output += "<p>";
    output += text;
    output += "<p>";
    std::cout << output << '\n';

    std::string words[] = { "hello",  "world"};
    std::ostringstream oss;
    oss << "<ul>\n";
    for (std::string w : words)
    {
        oss << "   <li>\n" << w << "\n    </li>\n";
    }
    oss << "</ul>\n";
    std::cout << oss.str() << '\n';
    //----------------------

    HtmlBuilder builder("ul");
    builder.add_child("li", "hello");
    builder.add_child("li", "world");
    builder.add_child("li", "fluent").add_child("li", "interface");

    std::cout << builder.str();

    HtmlBuilder builder2 = HtmlElement::build("ul").add_child("li", "test");

    std::cout << '\n' << builder2.str();

    HtmlElement elem = HtmlElement::build("ul").add_child("li", "e");

    return 0;
}