#include <iostream>

//swap with no additional memory
void swapper(int *x, int *y)
{
    *x = *x ^ *y; 
    *y = *y ^ *x;
    *x = *x ^ *y;
}

int main()
{
    int num1 = 20, num2 = 5;
    std::cout << "Before swap num1 is " << num1 << 
                 " and num2 is " << num2 <<std::endl;
    swapper(&num1, &num2);
    std::cout << "After swap num1 is " << num1 << 
                 " and num2 is " << num2 <<std::endl;
}