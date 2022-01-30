#include <iostream>

struct Point {
    double x;
    double y;
    Point(double x = 0, double y = 0): x(x), y(y) {}
};

double coefK(const Point &start, const Point &end)
{
    return (end.x != start.x)? (end.y - start.y) / (end.x - start.x) : 0;
}

double coefN(const Point &start, const double k)
{
    return start.y - k * start.x;
}

bool inBetween(const Point &start, const Point &end, const Point &target)
{
    double xmin = (start.x < end.x)? start.x : end.x;
    double xmax = (start.x < end.x)? end.x : start.x;
    double ymin = (start.y < end.y)? start.y : end.y;
    double ymax = (start.y < end.y)? end.y : start.y;
    return (target.x > xmin && target.x < xmax 
         && target.y > ymin && target.y < ymax)? true : false;
}

std::pair<Point, bool> findIntersect(const Point &start1, const Point &end1,
                                     const Point &start2, const Point &end2)
{
    auto nointersect = std::pair<Point, bool> (Point(), false);
    double k1 = coefK(start1, end1), n1 = coefN(start1, k1);
    double k2 = coefK(start2, end2), n2 = coefN(start2, k2);
    if (k1 == k2) return nointersect;
    double x = (n2-n1) / (k1-k2);
    Point isect(x, k1*x + n1);
    return (inBetween(start1,end1,isect) && inBetween(start2,end2,isect))?
           std::pair<Point, bool>(isect, true) : nointersect;   
}

int main()
{
    Point start1(1,2), end1(3,3),start2(1,5),end2(3,1);
    auto res = findIntersect(start1, end1, start2, end2);
    if (res.second) std::cout << "x=" << res.first.x <<
                     ", y=" << res.first.y << std::endl; 
    else std::cout << "No intersection!" << std::endl;
}