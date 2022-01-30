#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <unordered_set>

struct BabyGraphNode {
    bool visited;
    std::string parent;
    std::unordered_set<std::string> synonims;
    BabyGraphNode(bool v = 0, std::string s = ""): 
        visited(v), parent(s) {}
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
createGraph(std::vector<std::string> &names)
{
    std::unordered_map<std::string, BabyGraphNode> baby_map;
    //the graph will look like a set of parameciums. Around each element that doesnt have
    //a parent will be a set of elements pointing to it. Every other element will only point
    //to its parent, which keeps a set with all of its children.
    for (int i = 0; i < names.size(); i=i+2) { // the name pairs are put on odd and even positions so for increments by two
        bool cond1 = (baby_map.find(names[i]) == baby_map.end()); 
        bool cond2 = (baby_map.find(names[i+1]) == baby_map.end());
        if (cond1 && cond2) { //none in the map
            baby_map[names[i]] = BabyGraphNode();
            baby_map[names[i+1]] = BabyGraphNode(false, names[i]);
            baby_map[names[i]].synonims.insert(names[i+1]);
            continue;
        }
        if (cond1) { //second one in the map
            auto &ref = (baby_map[names[i+1]].parent != "")? //if second has a parent 
                        baby_map[names[i+1]].parent : names[i+1];
            baby_map[names[i]] = BabyGraphNode(false, ref);
            baby_map[ref].synonims.insert(names[i]);
            continue;          
        }
        if (cond2) { // first one in the map
            auto &ref = (baby_map[names[i]].parent != "")? //if second has a parent 
                         baby_map[names[i]].parent : names[i];
            baby_map[names[i+1]] = BabyGraphNode(false, ref);
            baby_map[ref].synonims.insert(names[i+1]);
            continue;              
        }
        // neither cond1 nor cond2 are true, which means both elements already in the graph
        auto *key1 = (baby_map[names[i]].parent != "")? //if first has a parent, go to it 
                  &(baby_map[names[i]].parent) : &names[i];
        auto *key2 = (baby_map[names[i+1]].parent != "")? //if second has a parent 
                  &(baby_map[names[i+1]].parent) : &names[i+1];
        if (*key1 == *key2) continue; //already within graph and with the same parent
        if (baby_map[*key1].synonims.size() < baby_map[*key2].synonims.size()) 
             std::swap(key1, key2); // shorten code to do union to a bigger set of synonims
        auto temp = *key2; //save key2 for later cleanup of its hash set
        baby_map[*key2].parent = *key1;
        baby_map[*key1].synonims.insert(*key2);
        for (auto mem : baby_map[*key2].synonims) { // do a set union inside an element with more synonims
            baby_map[mem].parent = *key1; //change the parent
            baby_map[*key1].synonims.insert(mem); //insert into parent hashset
        }
        baby_map[temp].synonims.clear(); // empty the second set synonims because of transfer to first            
    }
    return baby_map;
}

int main(int argc, char **argv)
{
       //{{"John", 15}, {"Jon",12}, {"Chris", 13}, {"Kris", 4}, {"Christopher", 19}};
    std::string line;
    std::ifstream input(argv[1]);
    if (!input) {
        std::cout << "Error opening the file!\n";
        return EXIT_FAILURE;
    }

    std::getline(input, line);
    auto names = parseWords(line);
    auto nums = numParser(line, 0);
    std::unordered_map<std::string, int> babies;
    babies.reserve(names.size());
    for (int i = 0; i < names.size(); i++)
        babies[names[i]] = nums[i];

    std::getline(input, line);
    auto synonyms = parseWords(line);
    std::unordered_map<std::string, BabyGraphNode> 
        baby_map = createGraph(synonyms); 
    
    // here we sum all synonims babies into their parent. If there are synonims not in the baby list,
    // they will be ignored since we go only through original list of names, not synonims list
    for (auto mem : babies) 
        if (baby_map[mem.first].parent != "") 
            babies[baby_map[mem.first].parent] += babies[mem.first];
 
    std::unordered_map<std::string, int> new_babies;  
    for(auto mem : babies) // here we reduce the map to have only parents
        if (baby_map[mem.first].parent == "")
            new_babies.insert(mem);

    for (auto mem : new_babies) 
        std::cout << "(" << mem.first << "," << mem.second << ")\n";
}