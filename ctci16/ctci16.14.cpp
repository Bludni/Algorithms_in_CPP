#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <iomanip>

struct Point {
    double x;
    double y;
    Point(double x = 0, double y = 0): x(x), y(y) {}

    bool operator<(const Point &p) const
    {
        return x < p.x || (x == p.x && y < p.y);
    }
};

class Line {
    private:
        double k;
        double n;
        bool vert;
    public:
        Line(double k = 0, double n = 0, bool v = false): 
                                    k(k), n(n), vert(v) {}
        Line(const Point &p1, const Point &p2)
        {
            if (p2.x != p1.x) {
                k = (p2.y - p1.y) / (p2.x - p1.x);
                n = p1.y - k * p1.x;
                vert = false;
            }
            else {
                k = 0;
                n = p1.x;
                vert = true;
            }
        }
        double getk() const { return k; } 
        double getn() const { return n; }
        bool isVert() const { return vert; }
        Line& operator=(const Line &p)
        {
            k = p.k;
            n = p.n;
            vert = p.vert;
            return *this;
        }

};

std::string double2string(const double& x) 
{
    std::ostringstream strs;
    strs << x;
    return strs.str();
}

std::string keyPrep(const Line &key)
{
    double k = (double) ((long) ((key.getk() + 0.005) * 100)) / 100;
    double n = (double) ((long) ((key.getn() + 0.005) * 100)) / 100;
    std::string temp = double2string(k) + "+" + double2string(n);
    return (key.isVert())? temp + "v" : temp; //if line is vertical, add v on the end 
    //turning two doubles into unique string to be key of the hashmap
}

void findLines(const std::vector<Point> &points,
               std::unordered_map<std::string, std::set<Point>> &lines)
{
    for (int i = 0; i < points.size(); i++) 
        for (int j = i + 1; j < points.size(); j++) 
            lines[keyPrep(Line(points[i], points[j]))].
            insert({points[i],points[j]});
}

int main()
{
    std::unordered_map<std::string, std::set<Point>> lines;
    std::vector<Point> points = {{1,1},{3,1},{6,2},{2,2},{1,4},{0.5,-1},{9,3}};
    findLines(points, lines); // putting all lines and their points in a map
    int max_points = 0; std::string max_line;
    for (auto mem : lines) //finding line with maxpoints
        if (mem.second.size() > max_points) {
            max_points = mem.second.size();
            max_line = mem.first;
        }
    double k, n;
    sscanf(max_line.c_str(), "%lf+%lf", &k, &n);
    if (max_line.back() == 'v') 
        std::cout << std::setprecision(2) << 
        "Line with max points: vertical x=" << n << " has " 
        << max_points << " points" << std::endl;   
    else
        std::cout << std::setprecision(2) << "Line with max points:" << k 
        << " * x + " << n << " has " << max_points << " points" << std::endl;   
}


