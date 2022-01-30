#include <vector>
#include "bintree.h"

bool& checkBST(bool &cond, std::vector<int> &vec, bintree::Tree::Node *pok)
{
    if (!cond) return cond;
    if (pok->left != NULL) checkBST(cond, vec, pok->left);
    vec.push_back(pok->get());
    if (vec.size() > 1) 
        cond = (vec[vec.size() - 1] > vec[vec.size() - 2])? cond : false;
    if (pok->right != NULL) checkBST(cond, vec, pok->right);
    return cond;
}

int main()
{
    std::vector<int> vec = {1, 3, 4, 5, 9, 11, 22, 34, 39, 45, 46, 50}; //55, 62};
    bintree::Tree tree = bintree::createTree(0, vec.size() - 1, vec);
    std::vector<int> vec2;
    bool cond = true;
    std::cout << checkBST(cond, vec2, tree.begin()) << std::endl;
}