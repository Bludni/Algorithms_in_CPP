#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <iostream>
#include <vector>

template <typename T>
class linked_list;

template <typename T>
std::ostream& operator<<(std::ostream&, linked_list<T>&);

template <typename T>
class Node {
    public:
        T data;
        Node* next;
        Node() {};
        Node(T data, Node* next = NULL):data(data),next(next) {}
};

template <typename T>
class linked_list {
    public: 
        Node<T>* head;
        linked_list() {head = nullptr; std:: cout << "default" << std::endl;}
        linked_list(linked_list<T>* pok):head(pok->head) {}
        linked_list(std::initializer_list<T> in_list);
        linked_list(std::vector<T> &container);
        linked_list(const linked_list<T>&);
        ~linked_list();
        linked_list<T>& operator=(linked_list<T>&& other);
        friend std::ostream& operator<< <>(std::ostream&, linked_list<T>&);
};

template <class T>
linked_list<T>::linked_list(std::initializer_list<T> in_list) 
{
    Node<T> *end;
    for (auto it = in_list.begin(); it != in_list.end(); it++) {
        Node<T> *temp = new Node<T>(*it);
        if (it == in_list.begin()) {
            head = temp;
            end = head;
            continue;
        }
        end->next = temp;
        end = temp;
    }
}

//zanimljiva sintaksa za dodelu tipa vrednosti sadrzanog u kontejneru.
//Naime pise se  typename T::value_type.
template<class T>
linked_list<T>::linked_list(std::vector<T> &container)
{
    Node<T> *end;
    for (auto it = container.begin(); it != container.end(); it++) {
        Node<T> *temp = new Node<T>(*it);
        if (it == container.begin()) {
            head = temp;
            end = head;
            continue;
        }
        end->next = temp;
        end = temp;
    }
}

template <class T>
linked_list<T>::linked_list(const linked_list<T> &lista)
{
    Node<T> *pok = lista.head; Node<T> *end;
    while (pok != NULL) {
        Node<T> *temp = new Node<T>(pok->data);
        if (pok == lista.head) {
            head = temp;
            end = head;
        }
        else {
            end->next = temp;
            end = end->next;
        }
        pok = pok->next;
    }
    std::cout << "Copy constructor called" << std::endl;
    std:: cout << *this;
}

template <class T>
linked_list<T>::~linked_list()
{
    Node<T> *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

//operator mora da se deklarise sa namespaceom klase, ako nije prijatelj.
template <class T>
linked_list<T>& linked_list<T>::operator=(linked_list<T>&& other)
{
    std::cout << "Move constructor" << std::endl;
    if (this == &other) return *this;
    /*Node<T> *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        delete temp;
    }*/ /*zakomentarisani kod je u sustini destruktor za koji mislim da nema
    potrebe ukoliko je destruktor same klase propisno definisan, iako je u
    clanku iz kog sam ucio move semantiku, on zapravo stavljen */
    this->head = other.head;
    other.head = nullptr;
    return *this;
    /*ako je povratna vrednost referenca, a baratamo sa pokazivacem
    neophodno je dereferencirati pokazivac kako bi se referenca 
    odnosila na ono na sta pokazivac pokazuje. */
}

template<class T>
std::ostream& operator<<(std::ostream& out, linked_list<T>& lista)
{
    Node<T> *pok;
    pok = lista.head;
    while (pok != NULL) {
        if (pok->next == NULL) out << pok->data << std::endl;
        else out << pok->data << " -> ";
        pok = pok->next;
    }
    return out;
}

#endif /* LINKED_LIST_H */

/*Prijateljska funkcija mogla je biti deklarisana samo unutar klase sa dodatnim template-om.
Ovo ponašanje je, medjutim, nepoželjno imajući u vidu da bi svaka specijalizacija templejta
funkcije mogla da pristupi svakoj specijalizaciji templejta klase.
Umesto ovoga, bolje rešenje da se prijateljska funkcija deklariše pre njene deklaracije 
unutar klase kao templejt (na početku ovog fajla) i zatim da se u deklaraciji unutar
klase zada <> posle imena prijateljske funkcije ili operatora. Na ovaj način se funkcija
deklarisan u klasi specijalizuje i omogučava prijateljstvo sa samo jednom specijalizacijom
klase.  */