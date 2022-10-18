#define _USE_MATH_DEFINES_
#include <iostream>
#include <cmath>
#include <ostream>

enum class PointType
{
    cartesian,
    polar
};

class Point
{
    //friend class PointFactory; //Open-closed principle violation can be removed by making constructor public
    Point(float x, float y) : x(x), y(y) {} 
    float x;
    float y;

    class PointFactory //granted the open closed principle close principle
    {
        PointFactory() {}
    public:
        static Point NewCartesian(float x, float y)
        {
            return {x, y};
        }

        static Point NewPolar(float r, float theta)
        {
            return { r * cos(theta), r * sin(theta)};
        }
    };

public:
    static PointFactory Factory;

    //Factory methods
    // static Point NewCartesian(float x, float y)
    // {
    //     return {x, y};
    // }

    // static Point NewPolar(float r, float theta)
    // {
    //     return { r * cos(theta), r * sin(theta)};
    // }
    
    friend std::ostream &operator<<(std::ostream &os, const Point &point)
    {
        os << "x: " << point.x << " || y: " << point.y << '\n';

        return os;
    }
};


/*
class PointFactory //granted the open closed principle close principle
{
    PointFactory() {}
public:
    static Point NewCartesian(float x, float y)
    {
        return {x, y};
    }

    static Point NewPolar(float r, float theta)
    {
        return { r * cos(theta), r * sin(theta)};
    }
};
*/

int main()
{
    //Point p = PointFactory::NewPolar(5, M_PI_4); //with outer point factory
    //Point p = Point::PointFactory::NewPolar(5, M_PI_4); //Factory where inner class is public
    Point p = Point::Factory.NewPolar(5, M_PI_4); //Inner Factory where inner class is exposed as a field
    std::cout << p << '\n';

    return 0;
}