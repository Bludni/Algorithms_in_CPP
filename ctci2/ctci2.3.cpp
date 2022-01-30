#include "linked_list.h"

template <typename T>
void rem_middle(Node<T>* lista)
{
    Node<T> *pok = lista, *temp;
    while (pok->next != NULL) {
        pok->data = pok->next->data;
        if (pok->next->next == NULL) temp = pok;
        pok = pok->next;
    }
    temp->next = NULL;
    delete pok;
}

int main()
{
    std::cout << "Izbacuje cvor iz sredine sa zadatim pokazivacem\
 na njega ali bez pocetka liste" << std::endl;
    linked_list<int> l = {2,1,2,2,3,4,5,2,1,3};
    auto *pok = l.head;
    for (int i = 0; i < 5; i++) pok = pok->next;
    rem_middle(pok);
    std::cout << l;
}