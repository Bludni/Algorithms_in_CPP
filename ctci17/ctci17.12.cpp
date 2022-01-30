#include <iostream>

struct BiNode {
    int data;
    BiNode *left, *right;
    BiNode(int d = 0, BiNode *l = NULL, BiNode *r = NULL):
    data(d), left(l), right(r) {}
};

struct BinTree {
    BiNode *root;
    BinTree(BiNode *r = NULL): root(r) {}
    BinTree(int arr[], int size)
    {
        root = createTree(arr,size,0,size-1);
    }
    
    BiNode* createTree(int arr[], int size, int beg, int end)
    {
        if (beg > end) return NULL;
        int middle = (beg + end) / 2;
        BiNode *curr = new BiNode(arr[middle]);
        curr->left = createTree(arr, size, beg, middle - 1);
        curr->right = createTree(arr, size, middle + 1, end);
        return curr;
    }

    void treeToDList()
    {
        root = treeToDList_(root).first;
    }

    std::pair<BiNode*, BiNode*> treeToDList_(BiNode *pok)
    {
        if (pok == NULL) return {NULL,NULL};
        auto prev = treeToDList_(pok->left);
        pok->left = prev.second;  
        if (prev.second != NULL) prev.second->right = pok;
        auto next = treeToDList_(pok->right);
        pok->right = next.first;  
        if (next.first != NULL) next.first->left = pok;
        auto *beg = (prev.first != NULL)? prev.first : pok;
        auto *end = (next.first != NULL)? next.second : pok;
        return std::make_pair(beg, end);
    }


    void destroyTree(BiNode *pok)
    {
        if (pok == NULL) return;
        destroyTree(pok->left);
        destroyTree(pok->right);
        delete pok;
    }
    
    ~BinTree()
    {
        destroyTree(root);
    }
};

int main()
{
    int size = 7;
    int arr[] = {1,2,3,4,5,6,7};
    BinTree tree(arr, size);
    tree.treeToDList();
    std::cout << "Bye\n";
}
