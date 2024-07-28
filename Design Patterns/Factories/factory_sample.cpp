#define _USE_MATH_DEFINES_
#include <iostream>
#include <cmath>
#include <ostream>

class Point
{
	friend class PointFactory; // Granting access to PointFactory
	float x, y;

	Point(float x, float y) : x(x), y(y) {} // Private constructor

public:
	class PointFactory // Inner PointFactory class
	{
	public:
		static Point NewCartesian(float x, float y)
		{
			return {x, y};
		}

		static Point NewPolar(float r, float theta)
		{
			return {r * cos(theta), r * sin(theta)};
		}
	};

	static PointFactory Factory; // Expose the inner factory as a field

	// Friend function to allow access to private members
	friend std::ostream &operator<<(std::ostream &os, const Point &point)
	{
		os << "x: " << point.x << " || y: " << point.y;
		return os;
	}
};

// Define the static Factory field
Point::PointFactory Point::Factory;

int main()
{
	Point p1 = Point::PointFactory::NewPolar(5, M_PI_4); // Using the inner class directly
	Point p2 = Point::Factory.NewPolar(5, M_PI_4); // Using the exposed inner factory
	std::cout << p1 << '\n';
	std::cout << p2 << '\n';

	return 0;
}
