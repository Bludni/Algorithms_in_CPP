#include <iostream>

int addNoPlus(int num1, int num2)
{
    if (!num2) return num1;
    return addNoPlus(num1 ^ num2, (num1 & num2) << 1);
}

int main()
{
    std::cout << addNoPlus(-1023, -250) << std::endl;
}