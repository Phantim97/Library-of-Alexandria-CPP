#include <iostream>
#include <string>
#include <vector>

class Rectangle
{
protected:
	int width;
	int height;

public:
	Rectangle(int width, int height) : width(width), height(height)
	{
	}

	virtual void setWidth(int width)
	{
		Rectangle::width = width;
	}

	virtual void setHeight(int height)
	{
		Rectangle::height = height;
	}

	int getWidth() const
	{
		return width;
	}

	int getHeight() const
	{
		return height;
	}

	int area() const
	{
		return width * height;
	}

};

class Square : public Rectangle
{
public:
	Square(int size) : Rectangle(size, size)
	{
	}

	void setWidth(int width) override
	{
		this->width = this->height = width;
	}

	void setHeight(int height) override
	{
		this->width = this->height = height;
	}
};

void process(Rectangle &r)
{
	int w = r.getWidth();
	r.setHeight(10);

	std::cout << "Expected Area: " << (w * 10) << ", got " << r.area() << '\n';
}

int main()
{
	Rectangle r(3, 4);
	process(r);

	Square sq(5); //violates the Liskov substitution principle based on process' output
	process(sq);
	return 0;
}
