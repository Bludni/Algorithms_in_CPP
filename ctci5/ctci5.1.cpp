#include <iostream>
#include <bitset>

// function inserts number m on positions from j to i from the right end
int insert(int n, int m, int i, int j)
{
   return ((-1 << j) + ((1 << i) - 1)) & n | (m << i);  
}

int main()
{
    int n = 0b1100011001, m = 0b11001;
    std::cout << std::bitset<10>(insert(n, m, 2, 7)) << std::endl;
}