#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <limits>

std::vector<std::string> parseWords(const std::string &str)
{
    int i = 0;
    std::vector<std::string> words;
    while (i < str.length()) {
        while (!isalpha(str[i]) && i < str.length()) i++;
        int j = i;
        while (isalpha(str[i]) && i < str.length()) i++;
        if (i != j) words.push_back(str.substr(j, i-j));
        i++;
    }
    return words;
}

std::unordered_map<std::string, std::vector<int>>
     createMap(const std::string &s)
{
    std::unordered_map<std::string, std::vector<int>> hmap;
    auto words = parseWords(s);
    for (int i = 0; i < words.size(); i++) 
        hmap[words[i]].push_back(i);
    return hmap;
}

int shortDiff(const std::string &s1, const std::string &s2,
              std::unordered_map<std::string,std::vector<int>> words_map)
{
    int i = 0, j = 0, mindif = std::numeric_limits<int>::max();
    while (i < words_map[s1].size() && j < words_map[s2].size()) {
        if (mindif == 1) return mindif;
        if (words_map[s1][i] < words_map[s2][j] && i < words_map[s1].size()) {
            mindif = (abs(words_map[s1][i] - words_map[s2][j]) < mindif)? 
                      abs(words_map[s1][i] - words_map[s2][j]) : mindif;
            i++;
            continue;
        }
        if (words_map[s1][i] > words_map[s2][j] && j < words_map[s2].size()) {
            mindif = (abs(words_map[s1][i] - words_map[s2][j]) < mindif)? 
                      abs(words_map[s1][i] - words_map[s2][j]) : mindif;
            j++;
            continue;
        }
    }
    return mindif;
}

int main()
{
    std::string s = "I was always a person going through life head against a wall";
    auto word_map = createMap(s);
    std::cout << shortDiff("a", "life", word_map) << std::endl;
}