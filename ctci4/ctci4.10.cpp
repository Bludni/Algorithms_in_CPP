#include "bintree.h"

bool& checkIfSubtree(bool &cond, bintree::Tree::Node *pok1,
                     bintree::Tree::Node *pok2)
{
    if (!cond) return cond;
    if (pok1 == NULL) {
        cond = (pok2 == NULL)? cond : false;
        return cond;
    }
    if (pok2 == NULL) {
        cond = (pok1 == NULL)? cond : false;
        return cond;
    }
    if (pok1->get() != pok2->get()) {
        cond = false;
        return cond;
    }
    checkIfSubtree(cond, pok1->left, pok2->left);
    checkIfSubtree(cond, pok1->right, pok2->right);
    return cond;
}

//pok1 is for big tree, and pok2 for small
bool& isSubtree(bool &cond, bintree::Tree::Node *pok1,
                     bintree::Tree::Node *pok2)
{
    if (cond) return cond;  // function is invoked with cond = false on start
    if (pok1 == NULL) return cond;
    if (pok1->get() == pok2->get()) {
        bool cond_temp = true;
        if (checkIfSubtree(cond_temp, pok1, pok2)) {
            cond = true;
            return cond;
        }
    }
    isSubtree(cond, pok1->left, pok2);
    isSubtree(cond, pok1->right, pok2);
    return cond;
}

int main()
{
    std::vector<int> vec1 = {1, 3, 4, 5, 9, 11, 22, 34, 39, 45, 46, 50, 55, 62, 70};
    std::vector<int> vec2 = {39, 45, 46, 50, 55, 62, 70};
    bintree::Tree tree1 = bintree::createTree(0, vec1.size() - 1, vec1);
    bintree::Tree tree2 = bintree::createTree(0, vec2.size() - 1, vec2);
    bool cond = false;
    std::cout << isSubtree(cond, tree1.begin(), tree2.begin()) << std::endl;
}