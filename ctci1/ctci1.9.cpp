#include <iostream>
#include <string>


int main()
{
    std::string str1,str2;
    std::cout << "Program proverava da li se string dobija rotacijom \
    drugog pomocu jednog koriscenja is_substring komande" << std::endl;
    std:: cout << "Uneti stringove:" << std::endl;
    std::getline(std::cin, str1);   std::getline(std::cin, str2);

    if (str1.length() != str2.length()) {
        std::cout << "Nije rotacija!" << std::endl;
        exit(EXIT_SUCCESS);
    }

    str2 += str2;  //konkatenacija omogucava da u \
    jednom prolasku proverimo sve rotacije
    if (str2.find(str1) != std::string::npos)
        std::cout << "Jeste rotacija!" << std::endl;
    else std::cout << "Nije rotacija!" << std::endl;
}