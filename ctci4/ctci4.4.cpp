#include <vector>
#include "bintree.h"

int& findDepth(int depth, int &max, bintree::Tree::Node *pok)
{
    max = (depth > max)? depth : max;
    if (pok->left != NULL)
        findDepth(depth + 1, max, pok->left);
    if (pok->right != NULL)
        findDepth(depth + 1, max, pok->right);
    return max;
}

bool& checkBalanced(bool &cond, bintree::Tree::Node *pok)
{
    if (!cond) return cond;
    int depth_left = 0, depth_right = 0;
    depth_left = (pok->left != NULL)? 
                  findDepth(1, depth_left, pok->left) : depth_left;
    depth_right = (pok->right != NULL)? 
                  findDepth(1, depth_right, pok->right) : depth_right;    
    if (abs(depth_left - depth_right) <= 1) {    
        if (pok->left != NULL) checkBalanced(cond, pok->left);
        if (pok->right != NULL) checkBalanced(cond, pok->right);
        return cond;
    }
    cond = false;
    return cond;
}

int main()
{
    std::vector<int> vec = {1, 3, 4, 5, 9, 11, 22, 34, 39, 45, 46, 50}; //55, 62};
    bintree::Tree tree = bintree::createTree(0, vec.size() - 1, vec);
    auto *pok = tree.begin();
    while (pok->right != NULL)
        pok = pok->right;
    tree.putRight(pok, 66);
    bool cond = true;
    std::cout << checkBalanced(cond, tree.begin()) << std::endl;
}