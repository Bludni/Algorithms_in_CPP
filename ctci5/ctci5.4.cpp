#include <iostream>
#include <bitset>

int getPrev(const int num)
{
    int i = -1, j = 0;
    while ((1 << ++i) & num); // first zero pos on i
    while (!((1 << ++i) & num)) j++; // first 1 left of first zero pos on i
    return num & (-1 << (i+1)) | (~(-1 << (i-j)) << j);  
}

int getNext(const int num)
{
    int i = -1, j = 0;
    while (!((1 << ++i) & num)); // first 1 pos on  i
    while ((1 << ++i) & num) j++; // first zero left of first 1 on i
    return num & (-1 << i) | ~(-1 << j) | (1 << i);    
}

int main()
{
    std::cout << std::bitset<9>(getNext(0b111000111)) << std::endl;
    std::cout << std::bitset<9>(getPrev(0b111000111)) << std::endl;
}