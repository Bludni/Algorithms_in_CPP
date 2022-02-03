#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <vector>
#include <deque>

struct Touch {
    const std::string *parent;
    bool id;
    Touch(bool id = 0, std::string *p = NULL): id(id), parent(p) {}
};

bool diffBy1(const std::string &s1, const std::string &s2)
{
    if (s1.length() != s2.length()) return false;
    if (s1 == s2) return false;
    int count = 0;
    for (int i = 0; i < s1.length(); i++)
        if (s1[i] != s2[i]) 
            if (count == 1) return false;
            else count++;
    return true;
}

std::vector<std::string> allDiffBy1(const std::string &str, 
              const std::unordered_set<std::string> &words)
{
    std::vector<std::string> temp;
    temp.reserve(words.size());
    for (auto word : words)
        if (diffBy1(str, word)) temp.push_back(word);
    return temp;
}

std::string bidirectSearch(const std::string &word1, const std::string &word2,
                           std::unordered_set<std::string> dict)
{
    std::string ret_val;
    const std::string *isect_left, *isect_right;
    std::unordered_map<std::string, Touch> graph;
    std::deque<std::string> que;
    if (word1.length() != word2.length())
        return "Error! Words of different length.";
    for (auto it = dict.begin(); it != dict.end(); it++) 
        if ((*it).length() > word1.length()) { //we eliminate words we dont need
            auto temp = it++; //for erasing element
            dict.erase(temp);
        }
    graph[word1] = Touch(0); // zero is part that searches from start
    graph[word2] = Touch(1); // 1 is part that searches from end
    que.push_front(word1);
    que.push_front(word2);
    bool cond = false;
    while (!que.empty()) { //we begin the search with start and end in the que
        auto curr = que.back();
        que.pop_back();
        auto vec = allDiffBy1(curr, dict);
        for (auto str : vec)
            if (graph.find(str) == graph.end()) {
                graph[str] = Touch(graph[curr].id);
                graph[str].parent = &(*(dict.find(curr)));
                que.push_front(str);
            }
            else if (graph[str].id != graph[curr].id) { //We found intersection!
                cond = true; //search succesfull
                isect_left = (graph[curr].id == 0)? &curr : &str;
                isect_right = (graph[curr].id == 1)? &curr : &str;
                std::string temp1 = *isect_left, temp2 = *isect_right;
                que.clear(); break;
            }
    }
    if (!cond) return "The dictionary doesnt have that transformation!";

    std::vector<std::string> vec;
    while (graph[*isect_left].parent != NULL) { // going to start
        vec.push_back(*isect_left);
        isect_left = graph[*isect_left].parent;
    }
    ret_val += *isect_left;
    for (int i = vec.size() - 1; i >= 0; i--) //pushing left search path into string
        ret_val += " -> " + vec[i];

    while (graph[*isect_right].parent != NULL) { //pushing right search path into string
        ret_val += " -> " + *isect_right;
        isect_right = graph[*isect_right].parent;
    }
    ret_val += " -> " + *isect_right;
    return ret_val;
}

/*transform word into another word letter by letter but each 
step must be in the dictionary along the way.
My first bidirectional graph search! */
int main()
{
    std::unordered_set<std::string> dict = {"DAMP", "LAMP", "LANE",
                                            "HIKE", "BURN", "BARD",
                                            "LIMP", "LIME", "SAND",
                                            "BARN", "TURN", "HARD",
                                            "HAND", "LIKE", "SANE",
                                            "POPOKATEPETL", "CROPS"};
    std::cout << bidirectSearch("DAMP","LIKE", dict) << std::endl;
    std::cout << bidirectSearch("BURN","LANE", dict) << std::endl;
    std::cout << bidirectSearch("TURN","DAMP", dict) << std::endl;     
}

