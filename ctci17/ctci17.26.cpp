#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <vector>
#include <fstream>

struct Pair {
    int first, second;
    Pair(int f = 0, int s = 0): first(f), second(s) {}
    
    bool operator<(const Pair &p) const
    {
        if (first == p.second && second == p.first)
            return false;
        return first < p.first || (first == p.first && second < p.second);
    }
};


std::vector<int> numParser(std::string &str, bool negative)
{
    std::vector<int> temp;
    int i = 0, j = 0;
    for ( ; i < str.length(); i++)
        if (isdigit(str[i]) || str[i] == '-' && negative) {
            j = i;
            while (isdigit(str[++i]));
            if ((str[j] == '-') && (i - j == 1)) continue;
            temp.push_back(std::stoi(str.substr(j, i - j)));
            if (str[i] == '-') i--;
        }
    return temp;
}

double similarity(std::unordered_set<int> &doc1,
                  std::unordered_set<int> &doc2)
{
    int isect = 0;
    for (auto &mem : doc1)
        if (doc2.find(mem) != doc2.end())
            isect++;
    return (double) isect / (double) (doc1.size() + doc2.size() - isect);
}


int main(int argc, char **argv) {
    std::string line;
    std::ifstream input(argv[1]);
    if (!input) {
        std::cout << "Error opening the file!" << std::endl;
        return EXIT_FAILURE;
    }
    std::unordered_map<int, std::unordered_set<int>> docs;
    std::unordered_map<int, std::vector<int>> word_doc;
    while (std::getline(input, line)) {
        auto vec = numParser(line, 0);
        for (int i = 1; i < vec.size(); i++) //vec[0] is the document, rest are the elements
            word_doc[vec[i]].push_back(vec[0]);
        auto temp = vec[0];
        vec.erase(vec.begin());
        docs[temp].insert(vec.begin(),vec.end());
    }

    std::set<Pair> doc_pairs;
    for (auto &mem : word_doc)
        for (auto it1 = mem.second.begin(); it1 != mem.second.end(); it1++)
            for (auto it2 = std::next(it1); it2 != mem.second.end(); it2++) 
                doc_pairs.insert(Pair(*it1, *it2));

    std::cout << "ID1,ID2 : SIMILARITY\n";
    for (auto &mem : doc_pairs) {
        std::cout << "(" << mem.first << "," << mem.second << ") : ";
        std::cout << similarity(docs[mem.first], docs[mem.second]) <<std::endl;
    }
// somewhat improved method is to have a hashmap of doc pairs to their intersections.
// that way, for each pair we touch only similar elements, which makes it faster than touching
// every element of each pair like in a previous solution.
// I will use std map, since i dont have option to not redefine hash function for user structs.

    std::map<Pair, int> doc_pairs_alt;
    for (auto &mem : word_doc)
        for (auto it1 = mem.second.begin(); it1 != mem.second.end(); it1++)
            for (auto it2 = std::next(it1); it2 != mem.second.end(); it2++) 
                if (doc_pairs_alt.find(Pair(*it1,*it2)) != doc_pairs_alt.end())
                    doc_pairs_alt[Pair(*it1,*it2)]++;
                else 
                    doc_pairs_alt[Pair(*it1,*it2)] = 1;

    std::cout << std::endl << "ID1,ID2 : SIMILARITY\n";
    for (auto &mem : doc_pairs_alt) {
        std::cout << "(" << mem.first.first << "," << mem.first.second
         << ") : " << (double) (mem.second) / 
                     (double) (docs[mem.first.first].size() + 
                               docs[mem.first.second].size() - mem.second) 
                     << std::endl;
    }
}