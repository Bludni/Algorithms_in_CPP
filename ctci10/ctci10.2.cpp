#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using Hmap = std::unordered_map<std::string, std::vector<std::string>>;

void anagList(std::vector<std::string> &vec, Hmap &hmap)
{
    for (auto str : vec) {
        std::string temp = str;
        std::sort(temp.begin(), temp.end());
        hmap[temp].push_back(str);
    }
}

void sortAnag(std::vector<std::string> &vec, Hmap &hmap)
{
    int i = 0;
    for (auto mem : hmap)
        for (auto str : mem.second)
            vec[i++] = str;
}

int main()
{
    std::vector<std::string> vec = {"art", "katarakta", "rat", "listen", 
                                    "rododendron", "silent"};
    Hmap hmap;
    anagList(vec, hmap);
    sortAnag(vec, hmap);
    for (auto str : vec) std::cout << str << std::endl;
            
}