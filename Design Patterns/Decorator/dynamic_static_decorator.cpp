#include <iostream>
#include <string>
#include <sstream>

struct Shape
{
    virtual std::string str() const  = 0;
};

struct Circle : Shape
{
    float radius;

    Circle() {}

    Circle(float radius) : radius(radius) {}

    void resize(float factor)
    {
        radius *= factor;
    }

    std::string str() const override
    {
        std::ostringstream oss;
        oss << "A circle of radius: " << radius;
        return oss.str();
    }
};

struct Square : Shape
{
    float side;

    Square() {}
    Square(float side) : side(side) {}

    std::string str() const override
    {
        std::ostringstream oss;
        oss << "A square with side: " << side;
        return oss.str();
    }
};

struct ColoredShape : Shape //Dynamic decorator
{
    Shape& shape;
    std::string color;

    ColoredShape(Shape &shape, const std::string &color) : shape(shape), color(color) {}

    std::string str() const override
    {
        std::ostringstream oss;
        oss << shape.str() << " has the color " << color;
        return oss.str();
    }
};

struct TransparentShape : Shape
{
    Shape& shape;
    uint8_t transparency;

    TransparentShape(Shape& shape, uint8_t transparency) : shape(shape), transparency(transparency) {}

    std::string str() const override
    {
        std::ostringstream oss;
        oss << shape.str() << " has " << static_cast<float>(transparency) / 255.0f * 100.0f << "% transparency";
        return oss.str();
    }
};

//static decorators
template<typename T> struct ColoredShape2 : T
{
    _Static_assert(std::is_base_of<Shape, T>::value, "Template argument must be a shape");

    std::string color;

    ColoredShape2() {}

    //TransparentShape2<ColoredShape2<Square>> sq {10, "red", 44}
    //variadic templates (...) rolls out args
    template <typename...Args>
    ColoredShape2(const std::string color, Args ...args) : T(std::forward<Args>(args)...), color(color) {}

    std::string str() const override //since T will always have a base of shape this is valid
    {
        std::ostringstream oss;
        oss << T::str() << " has the color " << color;
        return oss.str();
    }
};

//transparent shape is very similar

int main()
{
    Square sq{5};

    ColoredShape red_sq{sq, "red"};

    std::cout << sq.str() << '\n' << red_sq.str();

    TransparentShape my_sq{red_sq, 51};
    std::cout << my_sq.str();

    //ColoredShape{ColoredShape{ColoredShape{Square}}};

    //static
    ColoredShape2<Circle> green_circle{"green", 5};
    green_circle.resize(50.f);
    std::cout << green_circle.str() << '\n';

    //TransparentShape2<ColoredShape2<Square>> square {51, "blue", 10};
    //std::cout << square.str() << '\n';

    return 0;
}