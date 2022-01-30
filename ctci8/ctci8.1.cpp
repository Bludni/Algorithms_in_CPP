#include <iostream>

long climbStairs(int num)
{
    switch (num) {
        case 1 : return 1;
        case 2 : return 2;
        case 3 : return 4;
    }
    long prev = 1, prev2 = 2, prev3 = 4;
    for (int i = num - 4; i >= 0; i--) {
        long temp = prev3 + prev2 + prev;
        prev = prev2;
        prev2 = prev3;
        prev3 = temp;
    }
    return prev3;
}

int main()
{
    std::cout << climbStairs(50) << std::endl;
}