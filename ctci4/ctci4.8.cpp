#include "bintree.h"

void findNodePath(std::vector<bintree::Tree::Node*> &path,
                  bintree::Tree::Node *beg,
                  bintree::Tree::Node *ref, bool &cond)
{
    if (cond) return;
    if (ref->data == beg->data) {
        cond = true;
        return;
    }
    path.push_back(beg);    
    if (beg->left != NULL) findNodePath(path, beg->left, ref, cond);
    if (beg->right != NULL) findNodePath(path, beg->right, ref, cond);
    if (!cond) path.pop_back();
}

bintree::Tree::Node* findComAncestor(bintree::Tree::Node *beg,
                                     bintree::Tree::Node *pok1,
                                     bintree::Tree::Node *pok2)
{
    std::vector<bintree::Tree::Node*> path1, path2;
    bool cond = false;
    findNodePath(path1, beg, pok1, cond);
    cond = false;
    findNodePath(path2, beg, pok2, cond);
    auto it1 = path1.begin(), it2 = path2.begin();
    if (path1.size() == 1 || path2.size() == 1) return beg;
    while (*(std::next(it1)) == *(std::next(it2))) { 
            //going through list of pointers to ancestors until they diverge
        it1++; it2++;
    }
    return *it1; //same as it2
}

int main()
{
    std::vector<int> vec = {1, 3, 4, 5, 9, 11, 22, 34, 39, 45, 46, 50, 55, 62};
    bintree::Tree tree = bintree::createTree(0, vec.size() - 1, vec);
    bintree::Tree::Node *pok1 = tree.begin();
    pok1 = pok1->left;
    auto *pok2 = pok1;
    while (pok1->left != NULL) pok1 = pok1->left;
    while (pok2->right != NULL) pok2 = pok2->right;
   // std::cout << pok1->data << " " << pok2->data << std::endl;

    std::cout << findComAncestor(tree.begin(), pok1, pok2)->get() << std::endl;
}