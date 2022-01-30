#include "linked_list.h"
#include <unordered_map>

int main()
{
    linked_list<int> lista = {1,1,2,1,3,4,4,4,5,6,5,7};
    std::cout << "Program uklanja duplikate iz\
    jednostruko ulancane liste" << std::endl;
    std::unordered_map<int,int> umap;
    auto *pok = lista.head;
    umap[pok->data] = 1;
    //prolaz kroz listu, pravljenje mape duplikata i izbacivanje\
    kasnijih pojava istih.
    while (pok->next != NULL) {
        if (umap.find(pok->next->data) != umap.end()) {
            umap[pok->next->data]++;
            auto *temp = pok->next;
            pok->next = pok->next->next;
            delete temp;
            continue;
        }
        else umap[pok->next->data] = 1;
        pok = pok->next;
    }
    pok = lista.head;
    //izbacivanje preostalih kopija duplikata novim prolaskom.
    while (pok != NULL) {
        if (pok == lista.head && umap[pok->data] > 1) {
            auto *temp = pok;
            pok = pok->next;
            lista.head = pok;
            delete temp;
            continue;
        }
        if (pok->next != NULL && umap[pok->next->data] > 1) {
            auto *temp = pok->next;
            pok->next = pok->next->next;
            delete temp;
            continue;        
        }
        pok = pok->next;
    }
    std::cout << lista;
}