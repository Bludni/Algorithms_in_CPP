#include "linked_list.h"

Node<char>* loop_detect(Node<char> *lista)
{
    auto *zec = lista, *kornjaca = lista;
    do {
        kornjaca = kornjaca->next;
        zec = zec->next->next;
    } while (zec != kornjaca);
    zec = lista;
    while (zec != kornjaca) {
        kornjaca = kornjaca->next;
        zec = zec->next;
    }
    return kornjaca;
}

int main()
{
    std::cout << "Program otkriva\
 petlju u listi." << std::endl;
    linked_list<char> lista = {'a','b','c','d','e','f','g','h'};
    auto *pok1 = lista.head, *pok2 = lista.head;
    while (pok1->next != NULL){
        pok1 = pok1->next;
        if (pok2->data != 'e') pok2 = pok2->next;
    }
    pok1->next = pok2;
    pok2 = loop_detect(lista.head);
    std::cout << "Petlja pocinje u: " << pok2->data << std::endl;
    pok1->next = NULL;
}

/*
2k - put zeca
k - put kornjace
T - period petlje
m - put do petlje
vazi: 1. (2k - m) mod T = (k - m) mod T = x
treba dokazati: (x + m) mod T = 0.
Na osnovu distributivnosti modula prema sabiranju i oduzimanju imamo:
2k mod T - m mod T = k mod T - m mod T =>
2k mod T = k mod T => 
2k mod T - k mod T = 0 =>
(k + k) mod T - k mod T =>
k mod T + k mod T - k mod T = 0 =>
2. k mod T = 0
na osnovu 2. imamo da vazi:
(k - m) mod T = (T - m) mod T = x
odavde sledi
(x + m) mod T = x mod T + m mod T =>
= (T - m) mod T + m mod T =>
= T mod T - m mod T + m mod T =>
= T mod T = 0
cime je pocetna hipoteza dokazana.
*/