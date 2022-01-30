#include <iostream>
#include <string>
#include <unordered_map>

void mapPut(const std::string &word, 
            std::unordered_map<std::string, int> &words_map)
{
    if (words_map.find(word) == words_map.end())
        words_map[word] = 1;
    else words_map[word]++;
}

void wordFreq(std::string &book, std::unordered_map<std::string, int> &words_map)
{
    int pos;
    for (int i = 0; i < book.length(); i++) {
        if (isalpha(book[i])) {
            pos = i;
            while(i < book.length() && !isspace(book[i]) && 
                                        !ispunct(book[i])) i++;
            mapPut(book.substr(pos, i - pos), words_map);
        }
    }
}

int main()
{
    std::string str = "baba deda baba.roga koga smoga, dedica-koga.koga";
    std::unordered_map<std::string, int> words_map;
    wordFreq(str, words_map);
    for (auto mem : words_map)
        std::cout << mem.first << ": " << mem.second << std::endl;
}