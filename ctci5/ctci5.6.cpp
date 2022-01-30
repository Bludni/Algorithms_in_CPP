#include <iostream>
#include <bitset>
#include <type_traits>

int convert(int a, int b)
{
    int count = 0;
    unsigned int ua = static_cast<typename std::make_unsigned<int>::type>(a);
    unsigned int ub = static_cast<typename std::make_unsigned<int>::type>(b);
    if (a == b) return 0;
    while (a > 0 || b > 0) {
        count = ((a & 1) == (b & 1)) ? count : count + 1;
        a >>= 1; b >>= 1;
    }
    return count;
}

int main()
{
    std::cout << convert(0b11111001101, 0b110001110) << std::endl;
}