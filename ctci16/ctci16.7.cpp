#include <iostream>

//maximum without comparison operators
int maxof2(int a, int b)
{
    return (1 && (a/b)) * a + (1 && (b/a)) * b;    
}

int main()
{
    std::cout << "Max of 2: " << maxof2(20, 5) << std::endl;
}