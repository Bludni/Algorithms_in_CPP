#include <iostream>
#include <iomanip>
#include <random>

void genFamily(int &girls, int &boys)
{   
    int child;
    do {
        child = rand();
        if (child > (RAND_MAX / 2)) {
            girls++; break;
        }
        else boys++;
    } while(true);
}

void Apocalypse(int steps)
{
    int boys = 0, girls = 0;
    for (int i = 0; i < steps; i++) 
        genFamily(girls, boys);
    std::cout << "Boys: " << boys << std::endl <<
    "Girls: " << girls << std::endl << "Girls/Boys: "
    << (double) girls / boys << std::endl;
}

int main()
{
    srand(time(0));
    Apocalypse(10000);
}