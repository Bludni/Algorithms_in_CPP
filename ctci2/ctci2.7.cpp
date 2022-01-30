#include "linked_list.h"
#include <stack>

Node<int>* intersection(Node<int> *list1, Node<int> *list2)
{
    std::stack<Node<int>*> s1, s2;
    Node<int> *pok = NULL;
    while (list1 != NULL || list2 != NULL) {
        if (list1 != NULL) {
            s1.push(list1);
            list1 = list1->next;
        }
        if (list2 != NULL) {
            s2.push(list2);
            list2 = list2->next;
        }
    }
    while (s1.top() == s2.top()) {
        pok = s1.top();
        s1.pop(); s2.pop();
        if (s1.empty() || s2.empty()) break;
    }
    return pok;
}


int main()
{
std::cout << "Program vraca cvor od kog se liste\
 preklapaju, ako postoji." << std::endl;
linked_list<int> l1 = {1,2,3,4,5}, l2 = {6,7,8};
auto *pok1 = l1.head, *pok2 = l2.head; 
while (pok2->next != NULL) pok2 = pok2->next;
pok1 = pok1->next->next;
pok2->next = pok1;
std::cout << l1 << l2;
pok1 = intersection(l1.head, l2.head);
if (pok1 == NULL) std::cout << "Nema preseka!" << std::endl;
else std::cout << pok1->data << std::endl;
pok2->next = NULL; /* bez ove linije program pravi problem zbog
dvostrukog brisanja cvorova liste. Naime, problem je u tome sto
se prilikom brisanja l2 ne promeni i pokazivac cvora liste l1 koji 
pokazuje na zajednicki cvor, te umesto da pokazuje NULL, on pocne da
pokazuje na neku proizvoljnu lokaciju posle delete-a zajednickog cvora.
Kada se pokusa njegov delete, program vraca double free gresku.
*/ 
}