#include <vector>
#include "bintree.h"

int main()
{
    std::vector<int> vec = {1, 3, 4, 5, 9, 11, 22, 34, 39, 45, 46, 50}; //55, 62};
    bintree::Tree tree = bintree::createTree(0, vec.size() - 1, vec);   
    bintree::printInOrder(tree.begin()); 
    std::cout << std::endl;
}