#include <iostream>
#include <string>

int main()
{
    std::string str; int chars[128] = {0}; int cnt_odd = 0;
    std::cout << "Program proverava da li je string permutacija palindroma." << std::endl;
    std::cout << "Unesite string:" << std::endl;
    std::getline(std::cin, str);

    //pretpostavicemo da je u pitanju ascii tabela
    for (std::string::iterator it = str.begin(); it != str.end(); it++) chars[*it]++;
    for (int i = 0; i < 128; i++) cnt_odd += chars[i] & 1;
    if (cnt_odd > 1) std::cout << "String nije permutacija palindroma!" << std::endl;
    else std::cout << "String jeste permutacija palindroma!" << std::endl;
}