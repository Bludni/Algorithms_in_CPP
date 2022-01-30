#include <iostream>
#include <string>

std::string compression(std::string& str)
{
    int reps = 1, com_len = 0; std::string comp;
    //count compressed length
    for (int i = 0; i < str.length(); i++) {
        if (i == str.length() - 1) {
            com_len += 1 + std::to_string(reps).length();
            reps = 1;
            continue;
        }
        if (str[i] != str[i+1]) {
            com_len += 1 + std::to_string(reps).length();
            reps = 1;
            continue;
        }
        reps++;
    }
    //compress if meaningful
    if (com_len < str.length()) {
        for (int i = 0; i < str.length(); i++) {
            if (i == str.length() - 1) {
                comp += str[i];
                comp += std::to_string(reps);
                reps = 1;
                continue;
            }
            if (str[i] != str[i+1]) {
                comp += str[i];
                comp += std::to_string(reps);
                reps = 1;
                continue;
            }
            reps++;
        }
        return comp;
    }
    return str;
}

int main()
{
    std::string str;
    std::cout << "Program kompresuje string u format slovo-broj pojavljivanja"\
    << std::endl << "Uneti string:" << std::endl;
    std::getline(std::cin, str);
    str = compression(str);
    std::cout << "String posle kompresije je: " << str << std::endl;
}