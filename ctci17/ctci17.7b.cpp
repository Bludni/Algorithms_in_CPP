#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <deque>

//alternative solution with a true graph construction, compared to first

struct BabyGraphNode {
    int number;
    bool visited;
    std::vector<std::string> synonims;
    BabyGraphNode(int n = 0, bool v = 0): number(n), visited(v) {}
};

std::vector<std::string> parseWords(std::string &str)
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

std::unordered_map<std::string, BabyGraphNode>
createNodes(std::vector<std::string> &names, std::vector<int> &nums)
{
    std::unordered_map<std::string, BabyGraphNode> babies;
    for (int i = 0; i < names.size(); i++)
        babies[names[i]] = BabyGraphNode(nums[i],false);
    return babies;
}

void connectGraph(std::vector<std::string> &syn,
                  std::unordered_map<std::string, BabyGraphNode> &babies)
{
    for (int i = 0; i < syn.size(); i+=2) {
        babies[syn[i]].synonims.push_back(syn[i+1]);
        babies[syn[i+1]].synonims.push_back(syn[i]);
    }
}

std::unordered_map<std::string, BabyGraphNode> graphSearch(
        std::unordered_map<std::string, BabyGraphNode> babies)
{
    std::unordered_map<std::string, BabyGraphNode> true_names;
    std::deque<BabyGraphNode> search_que;

    for (auto it = babies.begin(); it != babies.end(); it++) {
        if (it->second.visited) continue;
        search_que.push_front(it->second);
        it->second.visited = true;
        int name_total = 0;
        while (!search_que.empty()) {
            auto el = search_que.back();
            search_que.pop_back();
            name_total += el.number;
            for (auto mem : el.synonims)
                if (!babies[mem].visited) {
                    search_que.push_front(babies[mem]);
                    babies[mem].visited = true;
                }
        }
        true_names.insert({it->first, BabyGraphNode(name_total)});
    }
    return true_names;
}

int main(int argc, char **argv)
{
    std::string line;
    std::ifstream input(argv[1]);
    if (!input) {
        std::cout << "Error opening the file!\n";
        return EXIT_FAILURE;
    }

    std::getline(input, line);
    auto names = parseWords(line);
    auto nums = numParser(line, 0);
    std::unordered_map<std::string, BabyGraphNode> babies = 
    createNodes(names, nums);

    std::getline(input, line);
    auto synonyms = parseWords(line);
    connectGraph(synonyms, babies); 
    std::unordered_map<std::string, BabyGraphNode> 
        true_names = graphSearch(babies);
    for (auto mem : true_names)
        std::cout << "(" << mem.first << "," << mem.second.number << ")\n";
}