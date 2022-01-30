#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

struct MinDif {
    int x;
    int y;
    int dif;
    MinDif(int x = 0, int y = 0, int d = 0): x(x), y(y), dif(d) {}

    MinDif& operator=(const MinDif &smt)
    {
        x = smt.x; y = smt.y; dif = smt.dif;
        return *this;
    }

    void print() 
    {
        std::cout << "x: " << x << " y: " << y << " dif: " << dif << std::endl;
    }
};

MinDif min_differ(std::vector<int> &vec1, std::vector<int> &vec2)
{
    std::sort(vec1.begin(), vec1.end());
    std::sort(vec2.begin(), vec2.end());
    int i = 0, j = 0;
    MinDif temp(0, 0, std::numeric_limits<int>::max());
    while (i < vec1.size() && j < vec2.size())
        if (vec1[i] < vec2[j]) i++;
        else  {
            temp = (temp.dif < (vec1[i] - vec2[j]))? temp :
                 MinDif(vec1[i], vec2[j], vec1[i] - vec2[j]);
            j++; 
        }
    return temp;
}

int main()
{
    std::vector<int> vec1 = {1,3,15,11,2}, vec2 = {23,127,235,19,8,90};
    min_differ(vec1,vec2).print();
}