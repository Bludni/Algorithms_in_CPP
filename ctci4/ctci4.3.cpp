#include <vector>
#include "bintree.h"

void levelVectors(int level, std::vector<std::vector<int>> &vec, 
                  bintree::Tree::Node *pok)
{
    if (level == vec.size())
        vec.push_back(std::vector<int>(1, pok->get()));
    else
        vec[level].push_back(pok->get());
    if (pok->left != NULL)
        levelVectors(level + 1, vec, pok->left);
    if (pok->right != NULL)
        levelVectors(level + 1, vec, pok->right);
}

int main()
{
    std::vector<int> vec = {1, 3, 4, 5, 9, 11, 22, 34, 39, 45, 46, 50}; //55, 62};
    bintree::Tree tree = bintree::createTree(0, vec.size() - 1, vec);
    std::vector<std::vector<int>> vec_levels;
    levelVectors(0, vec_levels, tree.begin());
    for (auto i : vec_levels) {
        for (auto j : i)
            std:: cout << j << " ";
        std::cout << std::endl;
    }
}