#include "bintree.h"
#include <random>

void chooseNode(bintree::Tree::Node *pok,
                unsigned int &some_node,
                bintree::Tree::Node &ret_val)
{
    if (pok == NULL || some_node < 0) return;
    if (some_node == 0) {
        ret_val = *pok;
        some_node--;
        return;
    }
    some_node--;
    chooseNode(pok->left, some_node, ret_val);
    chooseNode(pok->right, some_node, ret_val);
} // odlican update ovog algoritma je ukoliko cvorovi drveta imaju informaciju o
// velicini svog poddrveta. U tom slucaju, moze direktno da se odredi putanja do 
// random cvora proverom da li je razlika dobijenog randoma i levog poddrveta veca od 0
// i ako jeste, ide se desno, u suprotnom levo, i tako dok se ne dodje do 0. 

int main()
{
    std::vector<int> vec = {1, 3, 4, 5, 9, 11, 22, 34, 39, 45, 46, 50, 55, 62, 70};
    bintree::Tree tree = bintree::createTree(0, vec.size() - 1, vec);
    std::srand(time(0));
    unsigned int max_num = vec.size() * (RAND_MAX / vec.size());
    unsigned int some_node;
    while (true) {
        some_node = rand();
        if (some_node < max_num) break;
    }
    some_node = (some_node * vec.size()) / max_num;
    bintree::Tree::Node ret_val(-1);
    chooseNode(tree.begin(), some_node, ret_val);
    std::cout << ret_val.get() << std::endl;
}