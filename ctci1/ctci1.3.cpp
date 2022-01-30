#include <iostream>
#include <string>

int main()
{
    std::string str(50, ' '), rep("%20");
    std::cout << "Program menja praznine sa %20." << std::endl << "Uneti string: " << std::endl;
    std::getline(std::cin, str);
    for (int i = 0; i < str.length(); i++) {
       // if (str[i] == ' ') str.replace(i,1,"%20");  // prvi nacin
       if (str[i] == ' ') {
           int duzina = str.length();
           str.append(rep.length() - 1, ' ');
           for (int j = duzina - 1; j > i; j--) { 
               str[j + rep.length() - 1] = str[j];
           }
           for (int k = 0; k < rep.length(); k++) {
               str[i+k] = rep[k];
           }
       }
    }
    std::cout << str << std::endl << rep.length() << std::endl;
     std::cout << str[str.length() - 1] << std::endl;
}