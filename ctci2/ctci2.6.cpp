#include "linked_list.h"


bool palindrom(Node<char> *right, Node<char> **left)
{
    bool val = true;
    if (right->next != NULL) val = palindrom (right->next, left);
    if (!val) return false;
    val = (right->data == (*left)->data);
    *left = (*left)->next;
    return val;
}

//posto sam se zbunio otvorivsi program posle nekog vremena, stavljam napomenu.
//imamo pokazivac na pokazivac u funkciji koji je,s obzirom da se prolazi rekurzivno kroz
//nju i da se tek nakon dolaska do kraja pocinje sa uvecavanjem drugog pokazivaca, neophodan.
//Ovo proistice iz cinjenice da rekurzivni pozivi kreiraju nove pokazivacke promenljive na steku
//te ukoliko se ne cuva left kao pokazivac na pokazivac, svaka od promena pokazivaca left biva zanemarena.
int main()
{
    std::cout << "Program proverava da li je\
 lista palindrom." << std::endl;
    linked_list<char> lista = {'n','a','v','a','t','a','v','a','n'};
    Node<char> **left = new Node<char>*; 
    *left = lista.head; 
    if (palindrom(lista.head, left)) std::cout <<\
    "Jeste palindrom!" << std::endl;
    else std::cout << "Nije palindrom!" << std::endl;
    std::cout << lista;
    delete left;
}