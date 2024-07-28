#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>

enum class Relationship
{
    parent,
    child,
    sibling
};

struct Person
{
    std::string name;
};

struct RelationshipBrowser
{
    virtual std::vector<Person> find_all_children_of(const std::string& name) = 0;
};

struct Relationships : RelationshipBrowser//low level
{
    std::vector<std::tuple<Person, Relationship, Person>> relations;

    void add_parent_and_child(const Person& parent, const Person& child)
    {
        relations.push_back({parent, Relationship::parent, child});
        relations.push_back({child, Relationship::child, parent});
    }

    std::vector<Person> find_all_children_of(const std::string& name) override
    {
        std::vector<Person> result;
        
        for (auto&& [first, rel, second] : relations)
        {
            if (first.name == name && rel == Relationship::parent)
            {
                result.push_back(second);
            }
        }

        return result;
    }
    
};

struct Research //high level
{
    // Research(Relationships& rel)
    // {
    //     auto& relations = rel.relations;
    //     for (auto && [first, re, second] : relations)
    //     {
    //         if (first.name == "John" && re == Relationship::parent)
    //         {
    //             std::cout << "John has a child called " << second.name() << '\n';
    //         }
    //     }
    // }

    Research(RelationshipBrowser& browser)
    {
        for (const Person& child : browser.find_all_children_of("John"))
        {
            std::cout << "John has a child called " << child.name << '\n';
        }
    }
};

int main()
{
    Person parent{"John"};
    Person child1{"Chris"}, child2{"Matt"};

    Relationships relationships;
    relationships.add_parent_and_child(parent, child1);
    relationships.add_parent_and_child(parent, child2);

    return 0;
}