#include <iostream>
#include <vector>

class Rectangle
{
protected:
	int width_;
	int height_;

public:
	Rectangle(int width, int height) : width_(width), height_(height)
	{
	}

	virtual void setWidth(int width)
	{
		Rectangle::width_ = width;
	}

	virtual void setHeight(int height)
	{
		Rectangle::height_ = height;
	}

	int getWidth() const
	{
		return width_;
	}

	int getHeight() const
	{
		return height_;
	}

	int area() const
	{
		return width_ * height_;
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
		this->width_ = this->height_ = width;
	}

	void setHeight(int height) override
	{
		this->width_ = this->height_ = height;
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
