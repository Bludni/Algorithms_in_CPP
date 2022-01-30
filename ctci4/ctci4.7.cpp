#include <iostream>
#include <initializer_list>
#include <unordered_map>
#include <vector>
#include <string>
#include <set>

struct Node {
    bool visited;
    std::vector<char> next;
    Node(bool visited = false): visited(visited) {}
};

bool& buildOrder(bool &cond, std::set<char> &projects, 
                 std::unordered_map<char, Node> &graph,
                 std::unordered_map<char, Node>::iterator target,
                 std::string &build)
{
    if (!cond) return cond;
    if (target->second.next.empty()) { // if no dependencies, set it as next to build
        target->second.visited = true;
        build.push_back(target->first);
        return cond;
    }
    if (projects.find(target->first) == projects.end())
        projects.insert(target->first); // insert to stack(not really, but kind of) so we can follow if graph forms a loop
    else {
        cond = false; // if node is in stack, there is a loop, build not possible
        return cond;
    } 

    for (auto mem : target->second.next) { // go through list of dependencies
        if (graph[mem].visited) continue;
        auto target2 = graph.find(mem);
        if (buildOrder(cond, projects, graph, target2, build)) { // build the dependency
            if (!target2->second.visited) { // if its not already built, put it in build string
                build.push_back(target2->first);
                target2->second.visited = true;
            }
        }
        else return cond;
    }
    projects.erase(target->first); // erase the value from stack
    build.push_back(target->first); // put the value in build string, since all of its dependencies are there
    target->second.visited = true;
    return cond;
}

int main()
{
    std::string projects("abcdef");
    std::unordered_map<char, Node> graph;
    for (auto mem : projects)
        graph.insert({mem, Node()});       
    std::initializer_list<std::initializer_list<char>> 
        inlist = {{'a', 'd'}, {'f', 'b'}, {'b', 'd'}, {'f','a'}, {'d','c'}};
 
    for (auto mem : inlist) {
        auto it = mem.begin();
        graph[*std::next(it)].next.push_back(*it); 
    }

    std::set<char> stack;
    bool cond = true;
    std::string build;
    for (auto it = graph.begin(); it != graph.end(); it++) {
        if (it->second.visited) continue;
        if (!buildOrder(cond, stack, graph, it, build)) {
            std::cout << "Build not possible!!" << std::endl;
            break;
        }
    }
   if (cond) std::cout << build << std::endl;
}