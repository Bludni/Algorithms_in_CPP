#include <iostream>
#include <string>



int main()
{
    std::string a,b; int sum1 = 0, sum2 = 0; long prod1 = 1, prod2 = 1;
    std::cout << "Program proverava da li je string a permutacija stringa b." << std::endl;
    std::cout << "Unesite stringove a i b:" << std::endl;
    std::getline(std::cin, a); std::getline(std::cin, b);

    if (a.length() != b.length()) {
        std::cout << "Nisu permutacije!" << std::endl;
        exit(EXIT_SUCCESS);
    }

    for (int i=0; i<a.length(); i++){
        sum1 += a[i]; sum2 += b[i];
        prod1 *= a[i]; prod2 *= b[i];
    }

    if (sum1 == sum2 && prod1 == prod2) std::cout << "Jesu permutacije!" << std::endl;
    else std::cout << "Nisu permutacije!" << std::endl;
}