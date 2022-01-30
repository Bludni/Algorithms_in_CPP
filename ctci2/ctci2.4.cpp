#include "linked_list.h"

template <class T>
void partition(linked_list<T>& lista, int x)
{
    auto *pok = lista.head;
    auto *temp = pok;

    while (pok->next != NULL) {
        if (pok->next->data < x) {
            temp = pok->next;
            pok->next = pok->next->next;
            temp->next = lista.head;
            lista.head = temp;
        }
        else pok = pok->next;
    }
}

int main()
{
    std::cout << "Program deli listu na veci i\
 manji deo od zadatog broja" << std::endl;
    linked_list<int> l = {1,5,7,2,1,3,8,9,3};
    partition(l, 8);
    std::cout << l;
}