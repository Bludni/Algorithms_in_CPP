#include "linked_list.h"

template <typename T>
void find_k(linked_list<T>& lista, int k)
{
    auto *pok = lista.head, *run = lista.head;
    int n = k;
    while (pok->next != NULL) {
        if (n != 0) n--;
        else run = run->next;
        pok = pok->next;
    } 
    if (n > 0) std::cout << "Preveliko k za listu" << std::endl;
    else std::cout << run->data << std::endl;
}

int main()
{
    linked_list<int> l = {1,2,3,4,5,6,7,8,9};
    int k = 7;
    std::cout << "Program vraca k-ti element\
 liste od kraja." << std::endl;
    find_k(l, k);
}