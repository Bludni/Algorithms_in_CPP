#include <iostream>
#include <string>
#include <unordered_set>

//initial index is zero
bool wordFromOthWords(std::string &word, int index,
                      std::unordered_set<std::string> &words)
{
    if (index > 0 && words.find(word.substr(index)) != words.end())  
        return true;
    std::string temp;
    for (int i = index; i < word.length() - 1; i++) {
        temp.push_back(word[i]);
        if (words.find(temp) != words.end()) 
            if (wordFromOthWords(word, i + 1, words))
                return true;
    }
    return false; //if it comes to this, cond stayed false
}

int longWordFromOthWords(std::unordered_set<std::string> &words)
{
    int max_len = 0;
    std::string long_str;
    for (auto word : words)
        if (wordFromOthWords(word,0,words)) {
            max_len = (max_len < word.length())? word.length() : max_len;
            long_str = word;
        }
    std::cout << "Longest word from other words: " << long_str << std::endl;
    return max_len;
}

int main()
{
    std::unordered_set<std::string> words = {"cat", "banana", "dog", "semi", 
    "all", "owing", "semiallowing","nana", "walk", "walker", "dogwalker"};
    int len = longWordFromOthWords(words);
    std::cout << "it's length is: " << len << std::endl;
}