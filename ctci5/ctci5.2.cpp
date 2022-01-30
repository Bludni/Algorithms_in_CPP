#include <iostream>

// real number from 0 to 1, check if can be represented with 32 bit binary number
double binRep(double num)
{
    double w = 0.5, acc = 0;
    for (int i = 0; i < 32; i++) {
        acc = (acc + w > num)? acc : acc + w;
        if (acc == num) i = 32;
        w /= 2;
    }
    return acc;
}

int main()
{
    double num = 0.625; 
    if (num == binRep(num)) std::cout << "Possible!" << std::endl;
    else std::cout << "ERROR!" << std::endl; 
}