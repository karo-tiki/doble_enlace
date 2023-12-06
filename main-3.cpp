//lista boblemente enlazada circular
#include <iostream>
#include <functional> 
using namespace std;

template <class ED>
struct nodo {
    ED val;
    nodo<ED> *next;
    nodo<ED> *prev;

    nodo(ED v, nodo<ED> *n = nullptr, nodo<ED> *p = nullptr) : val(v), next(n), prev(p) {}
};

template <class T, class functor>
struct lista_c {
    nodo<T> *head = nullptr;
    functor compare;

    bool find(T valor);
    void add(T valor);
    void del(T valor);
    void print();
};

template <class T, class functor>
void lista_c<T, functor>::add(T va) {
    if (!find(va)) {
        nodo<T> *nuevo = new nodo<T>(va);

        if (!head) {
            head = nuevo;
            nuevo->next = head;
            nuevo->prev = head;
        } else {
            nodo<T> *temp = head;

            do {
                if (compare(va, temp->val)) {
                    nuevo->next = temp;
                    nuevo->prev = temp->prev;
                    temp->prev->next = nuevo;
                    temp->prev = nuevo;

                    if (temp == head) {
                        head = nuevo;
                    }

                    return;
                }
                temp = temp->next;

            } while (temp != head);

            nuevo->next = head;
            nuevo->prev = temp->prev;
            temp->prev->next = nuevo;
            temp->prev = nuevo;
        }
    }
}

template <class T, class functor>
bool lista_c<T, functor>::find(T valor) {
    nodo<T> *actual = head;
    if (!head) {
        return false;
    }
    do {
        if (actual->val == valor) {
            return true;
        }
        actual = actual->next;
    } while (actual != head);
    return false;
}

template <class T, class functor>
void lista_c<T, functor>::del(T valor) {
    if (!head) {
        return;
    }
    nodo<T> *temp = head;

    do {
        if (temp->valor == valor) {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            if (temp == head) {
                head = temp->next;
            }
            delete temp;
            return;
        }
        temp = temp->next;
    } while (temp != head);
}


template <class T, class functor>
void lista_c<T, functor>::print() {
    if (!head) {
        cout << "Lista vacía" << endl;
        return;
    }

    
    cout << " head -> ";
    nodo<T> *tempAscendente = head;
    do {
        cout << tempAscendente->val << " -> ";
        tempAscendente = tempAscendente->next;
    } while (tempAscendente != head);
    cout << "head" << endl;

    
    cout << " head <- ";
    nodo<T> *tempDescendente = head->prev;
    do {
        cout << tempDescendente->val << " <- ";
        tempDescendente = tempDescendente->prev;
    } while (tempDescendente != head->prev);
    cout << "head" << endl;
}

int main() {
    lista_c<int, less<int>> lista;
    lista.add(1);
    lista.add(5);
    lista.add(5);
    lista.add(7);
    lista.add(10);
    lista.add(15);
    cout << "Lista doblemente enlazada circular" << endl;
    lista.print();

    return 0;
}
