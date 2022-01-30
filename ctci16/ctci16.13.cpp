#include <iostream>

//two squares parallel to x, find their halving line

struct Square {
    struct Point {
        double x;
        double y;
        Point(double x = 0, double y = 0): x(x), y(y) {}
    };
    Point *topl;
    Point *botr;

    Square(const Point &p1, const Point &p2)
    {
        topl = new struct Point(p1.x, p1.y);
        botr = new struct Point(p2.x, p2.y);
    }

    Point middle()
    {
        return Point((topl->x + botr->x) / 2, (topl->y + botr->y) / 2);
    }

    ~Square()
    {
        delete topl; topl == NULL;
        delete botr; botr == NULL;
    }
};

double coefK(const Square::Point &start, const Square::Point &end)
{
    return (end.x != start.x)? (end.y - start.y) / (end.x - start.x) : 0;
}

double coefN(const Square::Point &start, const double k)
{
    return start.y - k * start.x;
}

using Point = Square::Point;

int main()
{
    Square s1(Point(-1,-1),Point(0,0)),
           s2(Point(2,2), Point(4,0));
    double k = coefK(s1.middle(), s2.middle());
    double n = coefN(s1.middle(), k);
    std::cout << "y = " << k << " * x ";
    if (n < 0) std::cout << "- " << std::abs(n) << std::endl;
    else std::cout << "+ " << n << std::endl; 
}