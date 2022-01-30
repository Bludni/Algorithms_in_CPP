#include <iostream>
#include <bitset>

int paritySwap(int num)
{
   // int mask = 1;
   // for (int i = 2; i < 32; i += 2) mask = (mask << 2) + 1;
    int mask = 0b01010101010101010101010101010101;
    return (num & mask) << 1 | (num & (mask << 1)) >> 1;
}

int main()
{
    std::cout << std::bitset<5>(paritySwap(0b0101)) << std::endl;
}