#include <iostream>

long recMul(long num1, long num2)
{
    if (num2 == 0) return 0;
    return (num2 & 1)? num1 + recMul(num1 << 1, num2 >> 1) : 
                              recMul(num1 << 1, num2 >> 1);
}

int main()
{
    long n1 = 25, n2 = 125;
    if (n1 < n2) std::swap(n1, n2);
    std::cout << recMul(n1, n2) << std::endl;
}