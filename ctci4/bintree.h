#ifndef BINTREE_H
#define BINTREE_H
#include <iostream>
#include <vector>

namespace bintree {
    struct Tree {
    public:
        struct Node {
            int data;
            Node *left;
            Node *right;
            Node(int d):data(d) 
            {
                left = nullptr; right = nullptr;
            }
            int get()
            {
                return data;
            }
        };
    private: 
        Node *head;
    public:
        Tree(int d) 
        {
            head = new Node(d);
        }

        Node* begin()
        {
            return head;
        }
        
        void destSubTree(Node *pok)
        {
            Node *l = pok->left;
            Node *r = pok->right;
            pok->left = NULL; pok->right == NULL;
            delete pok;
            if (l != NULL) destSubTree(l);
            if (r != NULL) destSubTree(r);
        }

        void createNode(Node *pok, int d)
        {
            if (pok != NULL) destSubTree(pok);
            pok = new Node(d);
        }

        void putLeft(Node *pok, int d)
        {
            if (pok->left) destSubTree(pok->left);    
            pok->left = new Node(d);
        }

        void putRight(Node *pok, int d)
        {
            if (pok->right) destSubTree(pok->right);
            pok->right = new Node(d);
        }

        ~Tree()
        {
            destSubTree(head);
        }
    };

    void createSubtree(int beg, int middle, int end, 
                        std::vector<int> vec, Tree &tree, 
                        Tree::Node* pok)
    {
        if (end == beg) return;

        int middle_left = (beg + middle) / 2;
        int middle_right = (middle + end + 1) / 2;

        if (middle_left != middle) {
            tree.putLeft(pok, vec[middle_left]);
            createSubtree(beg, middle_left, middle - 1,
                        vec, tree, pok->left);
        }
        if (middle_right != middle) {
            tree.putRight(pok, vec[middle_right]);
            createSubtree(middle + 1, middle_right, end,
                        vec, tree, pok->right);
        }

    }

    Tree createTree(int beg, int end, std::vector<int> vec)
    {
        int middle = (end + beg + 1) / 2;
        Tree tree = Tree(vec[middle]);
        if (beg == end) return tree;
        int middle_left = (middle - 1 + beg + 1) / 2,
            middle_right = (end + middle + 1) / 2;
        tree.putLeft(tree.begin(), vec[middle_left]);
        tree.putRight(tree.begin(), vec[middle_right]);
        createSubtree(beg, middle_left, middle - 1, 
                    vec, tree, tree.begin()->left);
        createSubtree(middle + 1, middle_right, end,
                    vec, tree, tree.begin()->right);
        return tree;
    }

    void printInOrder(Tree::Node *tree)
    {
        if (tree == NULL) return;
        printInOrder(tree->left);
        std::cout << tree->data << " ";
        printInOrder(tree->right);
    }

}/* end namespace bintree */
#endif /* BINTREE_H*/