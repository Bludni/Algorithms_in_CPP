#include <iostream>
#include <stack>

std::ostream& operator<<(std::ostream &out, std::stack<int> s)
{
    std::cout << "[";
    while (!s.empty()) {
        std::cout << s.top();
        if (s.size() != 1) std::cout << ", ";
        s.pop(); 
    }
    std::cout << "]";
    return out;
}

void hanoi(int disk, std::stack<int> &source,
           std::stack<int> &dest, std::stack<int> &spare,
           std::stack<int> &a, std::stack<int> &b, std::stack<int> &c)
{
    if (disk == 1) {
        dest.push(source.top());
        source.pop();
        std::cout << "[" << a << "," << b << "," << c << "]" << std::endl;
    }
    else {
        hanoi(disk - 1, source, spare, dest, a, b, c);
        dest.push(source.top());
        source.pop();
        std::cout << "[" << a << "," << b << "," << c << "]" << std::endl;
        hanoi(disk - 1, spare, dest, source, a, b, c);
    }
}

int main()
{
    int num = 4;
    std::stack<int> a, b, c;
    for (int i = num ; i > 0; i--) 
        a.push(i);
    hanoi(num, a, b, c, a, b, c);
}