#include <iostream>
#include <vector>
#include <memory>

struct Point
{
    int x;
    int y;
};

struct Line
{
    Point start;
    Point end;
};

struct VectorObject
{
    virtual std::vector<Line>::iterator begin();
    virtual std::vector<Line::iterator end();
};

struct VectorRectangle : VectorObject
{
  VectorRectangle(int x, int y, int width, int height)
  {
      lines.emplace_back(Line{ Point{x, y}, Point{x + width, y}});
      lines.emplace_back(Line{ Point{x + width, y}, Point{x + width, y}});
      lines.emplace_back(Line{ Point{x, y}, Point{x, y + height}});
      lines.emplace_back(Line{ Point{x, y + height}, Point{x + width, y + height}});
  }  
};

std::vector<std::shared_ptr<VectorObject>> vectorObjects { 
    std::make_shared<VectorRectangle>(10,10, 100, 100),
    std::make_shared<VectorRectangle>(30,30, 60, 60),}

struct LineToPointAdapter
{
    typedef std::vector<Point> points;

    LineToPointAdapter(Line &line)
    {

    }

    virtual Points::iterator begin() { return points.begin();}
    virtual Points::iterator end() {return points.end();}
    private:
    Point points;
}

int main()
{
    return 0;
}