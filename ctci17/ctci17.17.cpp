#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>


//designing an algorithm for searching big string long_str, for bunch of smaller ones in a vector

std::unordered_set<std::string> mapSubstr(const std::string &str)
{
    std::unordered_set<std::string> substrings;
    for (int i = 0; i < str.length(); i++)
        for(int j = i+1; j <= str.length(); j++)
            substrings.insert(str.substr(i, j-i));
    return substrings;
}

bool isSubstr(const std::string &str, const std::string &sub)
{
    int j = 0;
    for (int i = 0; i < str.length(); i++) {
        if (j == sub.length()) return true;
        if (str[i] == sub[j]) j++;
        else j = 0;
    }
    if (j == sub.length()) return true;
    return false;
}

void printSubstrs(const std::string long_str, std::vector<std::string> words)
{
    if (long_str.length() > words.size()) {
        for (auto word : words) //this works in O(N*K) where N is length of longstr, and K is words.size
            if (isSubstr(long_str, word))
                std::cout << word << std::endl;
    }
    else {
        auto substrings = mapSubstr(long_str);
        for (auto word : words) //this works in O(N^2 + K) where N is long_str length, and K words.size
            if (substrings.find(word) != substrings.end())
                std::cout << word << std::endl;
    }
}

int main()
{
    std::string long_str1 = "globglogabgalab";
    std::string long_str2 = "gabulk";
    std::vector<std::string> words = {"glob","dar","gab","lab","swivel","bulk","hulk","long"};
    printSubstrs(long_str1, words);
    std::cout << std::endl;
    printSubstrs(long_str2, words);
}