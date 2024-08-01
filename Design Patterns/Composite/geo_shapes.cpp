#include <iostream>
#include <vector>
#include <memory>
#include <string>

struct GraphicObject
{
	virtual void draw() = 0;
	virtual ~GraphicObject() = default; // Virtual destructor for proper cleanup
};

struct Circle : GraphicObject
{
	void draw() override
	{
		std::cout << "Circle\n";
	}
};

struct Square : GraphicObject
{
	void draw() override
	{
		std::cout << "Square\n";
	}
};

struct Group : GraphicObject
{
	std::string name;
	std::vector<std::shared_ptr<GraphicObject>> objects;

	explicit Group(const std::string& name) : name(name) {}

	void draw() override
	{
		std::cout << "Group: " << name << " contains:\n";
		for (const auto& o : objects)
		{
			o->draw();
		}
	}
};

int main()
{
	std::shared_ptr<Group> root = std::make_shared<Group>("root");
	std::shared_ptr<Circle> c1 = std::make_shared<Circle>();
	std::shared_ptr<Circle> c2 = std::make_shared<Circle>();
	std::shared_ptr<Square> c3 = std::make_shared<Square>();

	root->objects.push_back(c1);

	std::shared_ptr<Group> subgroup = std::make_shared<Group>("sub");
	subgroup->objects.push_back(c2);
	subgroup->objects.push_back(c3);

	root->objects.push_back(subgroup);

	root->draw();

	return 0;
}
