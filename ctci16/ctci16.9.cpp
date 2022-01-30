#include <iostream>

int minus(const int &num1, const int &num2)
{
    return num1 + (~num2 + 1);
}

int mul(int num1, int num2, int res = 0)
{
    return (num2 != 0) ? mul(num1 << 1, num2 >> 1, //tail recursion
                         res + num1 * (num2 & 1)) : res; 
}

int binLen(int num)
{
    int len = 0;
    while (num) {
        num >>= 1;
        len++;
    }
    return len;
}

int divide(int num1, int num2, int res = 0)
{
    if (num1 < num2) return res;
    int len2 = binLen(num2);
    int len1 = binLen(num1);
    int shift = len1 - len2 + 1;

    while (--shift >= 0) {
        int num1_seg = num1 >> shift;
        if (num1_seg < num2) {
            res <<= 1;
            continue;
        }
        num1_seg = minus(num1_seg, num2);
        res <<= 1; res++; 
        num1 = (~(-1 << shift) & num1) + (num1_seg << shift); //first is right part and second left 
    }
    return res;
}

int main()
{
    std::cout << minus(1205,121) << std::endl;
    std::cout << mul(92, 11) << std::endl;
    std::cout << divide(936, 13) << std::endl;  
}