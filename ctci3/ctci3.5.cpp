#include <iostream>
#include <stack>
#include <deque>


void stack_sort(std::stack<int>& s1)
{
    std::stack<int> ts;
    while (!s1.empty()) {
        int temp = s1.top();
        s1.pop();
        if (ts.empty()) ts.push(temp);
        else {
            while (!ts.empty() && temp < ts.top()) {
                s1.push(ts.top());
                ts.pop();
            }
            ts.push(temp);
        }        
    }
    while (!ts.empty())
    {
        s1.push(ts.top());
        ts.pop();
    }
}

int main()
{
    std:: cout << "Program sortira\
 stek pomocu dodatnog steka." << std::endl;
    std::deque<int> q = {3,4,2,8,6,1,9,7,5};
    std::stack<int> s(q);
    stack_sort(s);
    while (!s.empty()) {
        std::cout << s.top() << " ";
        s.pop();
        if (s.empty()) std::cout << std::endl;
    }     
}


