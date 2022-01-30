#include <fstream>
#include <forward_list>
#include <deque>
#include "luka_string.h"

template <typename T>
struct Node {
    T data;
    std::forward_list<T> next;
    bool visited;
    Node(T data, bool visited = false): data(data), visited(visited){}
    friend bool operator==(const Node<T> &node1, const Node<T> &node2)
    {
        return node1.data == node2.data &&
               node1.next == node2.next;
    }
};

void ispis(std::forward_list<int>::iterator curr, 
std::forward_list<int>::iterator end) 
{
    if (curr != end) {
        auto it = curr;
        ispis(++it, end);
        std::cout << *curr << " ";
    }
}

template <typename T>
void resetTree(std::vector<Node<T>> &tree)
{
    for (auto &node : tree) 
        node.visited = false;
}

bool pathExist(int node1, int node2, std::vector<Node<int>> &vec)
{
    std::deque<int> que;
    if (vec[node1] == vec[node2]) return true;
    que.push_front(node1);
    vec[node1].visited = true;
    do {
        auto temp = que.back();
        if (temp == node2) return true;
        que.pop_back();
        for (auto mem : vec[temp].next)
            if (!vec[mem].visited) {
                que.push_front(mem);
                vec[mem].visited = true;
            }
    } while (!que.empty());

    return false;
}

int main(int argc, char** argv)
{
    std::ifstream input(argv[1]);
    if (!input) {
        std::cout << "Error opening file!" << std::endl;
        return EXIT_FAILURE;
    }
 
    std::string line;
    std::vector<Node<int>> nodes;
    while (std::getline(input, line)) {
        std::vector<int> temp;
        temp = luka_string::num_parser(line);
        nodes.push_back(Node<int>(temp[0]));
        for (auto it = temp.begin() + 1; it != temp.end(); it++)
            nodes[nodes.size() - 1].next.push_front(*it);     
    }
    std::cout << pathExist(0,4, nodes) << std::endl;

}