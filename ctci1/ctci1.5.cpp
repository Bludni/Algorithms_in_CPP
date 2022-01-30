#include <iostream>
#include <string>

#define     swap(T,x,y)   {T z; z = x; x = y; y = z; } 
int main() 
{
    std::string str1, str2;   int count_diff = 0;
    std::cout << "Program proverava da li primenom jedne operacije \
    dobijamo jedan string od drugog." << std::endl;
    std::cout << "Uneti stringove:" << std::endl;
    std::getline(std::cin, str1); std::getline(std::cin, str2);

    if (abs(str1.length() - str2.length()) > 1) {
        std::cout << "Nije moguce!" << std::endl;
        exit(EXIT_SUCCESS);
    }

    if (str1.length() == str2.length()) {
        for (int i = 0; i < str1.length(); i++) {
            count_diff += (str1[i] != str2[i]);
            if (count_diff > 1) {
                std::cout << "Nije moguce!" << std::endl;
                exit(EXIT_SUCCESS);
            }
        }
        std::cout << "Moguce je!" << std::endl;
        exit(EXIT_SUCCESS);
    }

    if (str1.length() > str2.length()) swap(std::string,str1,str2); 
    // str1 da bude sigurno kraci
    for (int i = 0, j=0; i < str1.length(); i++,j++) {
        if (str1[i] != str2[j]) {
            count_diff++; 
            i--;
        }
        if (count_diff > 1) {
            std::cout << "Nije moguce!" << std::endl;
            exit(EXIT_SUCCESS);
        }
    }
    std::cout << "Moguce je!" << std::endl;
}