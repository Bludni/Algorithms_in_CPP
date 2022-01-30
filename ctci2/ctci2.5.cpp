#include "linked_list.h"
#include <memory>
/*
Node<int>* sum1(Node<int> *list1, Node<int> *list2)
{
    int zbir,carry = 0; Node<int> *temp, *pok = NULL; linked_list<int> res;
    if (list1 == NULL && list2 != NULL) {
        res.head = list2;
        return res.head;
    }
    if (list2 == NULL && list1 != NULL) {
        res.head = list1;
        return res.head;
    }
    while (list1 != NULL || list2 != NULL) {
        if (list1 == NULL) zbir = list2->data + carry;
        else if (list2 == NULL) zbir = list1->data + carry;
        else zbir = list1->data + list2->data + carry;
        carry = (zbir >= 10);
        if (carry) zbir -= 10;
        temp = new Node<int>(zbir);
        if (pok == NULL) {
            res.head = temp;
            pok = temp;
        }
        else {
            pok->next = temp;
            pok = pok->next;
        }
        if (list1 != NULL) list1 = list1->next;
        if (list2 != NULL) list2 = list2->next; 
    }
    if (carry > 0) {
        temp = new Node<int>(carry);
        pok->next = temp;
        pok = pok->next;
    }
    std::cout << res;
    pok = res.head;
    res.head = NULL;
    return pok;
}
*/


linked_list<int> sum1(Node<int> *list1, Node<int> *list2)
{
    int zbir,carry = 0; Node<int> *temp, *pok = NULL; linked_list<int> res;
    if (list1 == NULL && list2 != NULL) {
        res.head = list2;
        return res;
    }
    if (list2 == NULL && list1 != NULL) {
        res.head = list1;
        return res;
    }
    while (list1 != NULL || list2 != NULL) {
        if (list1 == NULL) zbir = list2->data + carry;
        else if (list2 == NULL) zbir = list1->data + carry;
        else zbir = list1->data + list2->data + carry;
        carry = (zbir >= 10);
        if (carry) zbir -= 10;
        temp = new Node<int>(zbir);
        if (pok == NULL) {
            res.head = temp;
            pok = temp;
        }
        else {
            pok->next = temp;
            pok = pok->next;
        }
        if (list1 != NULL) list1 = list1->next;
        if (list2 != NULL) list2 = list2->next; 
    }
    if (carry > 0) {
        temp = new Node<int>(carry);
        pok->next = temp;
        pok = pok->next;
    }
    //std::cout << res << "bla" <<std::endl;

    return res;
}

/* druga po redu varijanta f-je suma1 je dobar primer zasto ne treba
 vracati klase po vrednosti. Naime, optimizacija povratne vrednosti 
 funkcije kojuckompajler uvek primenjuje, cesto zaobilazi konstuktore 
kopiranja. U posmatranom slucaju, iako konstruktor kopiranja biva isforsirano
pozvan, destruktor ove klase se poziva i na privremenom objektu 
u koji se kopira i informacije iz liste se svakako gube. Ovo sve je 
vazilo kada je u main-u upotrebljavana jednakost za dodelu povratne 
vrednosti funkcije. Kada je zamenjen izraz tako da se funkcija iskoristila
u varijanti linked_list<int> sum_list(sum1(list1.head, list2.head))
program je misteriozno proradio kao sto sam ocekivao da ce raditi za jednakost. */


linked_list<int> *suma2(Node<int> *list1, Node<int> *list2)
{
    int zbir, num1 = 0, num2 = 0;
   // std::shared_ptr<linked_list<int>> ptr(new linked_list<int>);
    linked_list<int> *ptr = new linked_list<int>;
    while (list1 != NULL || list2 != NULL) {
        if (list1 != NULL) {
            num1 = num1 * 10 + (list1->data);
            list1 = list1->next;
        }
        if (list2 != NULL) {
            num2 = num2 * 10 + list2->data;
            list2 = list2->next;
        }
    }
    zbir = num1 + num2;
    while (zbir != 0) {
        Node<int> *temp = new Node<int>(zbir % 10);
        temp->next = ptr->head;
        ptr->head = temp;
        zbir /= 10;    
    }
    std::cout << *ptr;
    return ptr;
}



int main() 
{
    linked_list<int> list1 {2,3,9}, list2 {9,8};
    std:: cout << "Program sumira liste spreda i u\
 obrnutom poretku" << std::endl;
    linked_list<int> sum_list; //= sum1(list1.head, list2.head);
    sum_list = sum1(list1.head, list2.head);
    //zanimljivo je primetiti da se kod jednakosti mimo dodele
    //ne desava return value optimizicija kako treba, a kod gorenavedene
    //se ne poziva konstruktor kopiranja zbog prisustva ove optimizacije
    std::cout << sum_list; 
    linked_list<int> *fin = suma2(list1.head, list2.head);
    std:: cout << *fin;
    delete fin; 
}