#include <iostream>
#include <string>

//prints all valid combinations of parentheses.
// begins with same left and right
void parens(int left, int right, std::string &str)
{
    if (!left && !right) {
        std::cout << str << std::endl;
        return;
    }
    if (left) {
        str.push_back('(');
        parens(left - 1, right, str);
        str.pop_back();
    }
    if (right > left) {
        str.push_back(')');
        parens(left, right - 1, str);
        str.pop_back();
    }
}

int main()
{
    std::string str;
    int num = 4;
    parens(num, num, str);
}