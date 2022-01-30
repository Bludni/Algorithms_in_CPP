#include <iostream>
#include <random>

//rand7 through rand 5
int rand5()
{
    int divider = RAND_MAX / 5;
    int max_num = divider * 5;
    int val = rand();
    while (val >= max_num)
        val = rand();
    return val / divider;
}

int rand7()
{
    int val = 5*rand5() + rand5();
    while (val > 20) // we cutt of on 20 so it's three values for each
        val = 5*rand5() + rand5();
    return val / 3;
}

int main()
{
    srand(time(0));
    for (int i = 0 ; i < 100; i++)
        std::cout << rand7() << std::endl;
}