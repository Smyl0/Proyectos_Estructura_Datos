#ifndef LISTASIMPLE_H
#define LISTASIMPLE_H

#include <iostream>
using namespace std;

template <typename T>
struct Nodo {
    T info;
    Nodo<T>* siguiente;

    Nodo(T valor) {
        info = valor;
        siguiente = NULL;
    }
};

template <typename T>
class ListaSimple {
private:
    Nodo<T>* primero;
    Nodo<T>* ultimo;

public:
    ListaSimple() {
        primero = NULL;
        ultimo = NULL;
    }

    ~ListaSimple() {
        Nodo<T>* actual = primero;
        while (actual != NULL) {
            Nodo<T>* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
    }

    void insertarAlInicio(T valor) {
        Nodo<T>* nuevo = new Nodo<T>(valor);
        if (primero == NULL) {
            primero = nuevo;
            ultimo = nuevo;
        } else {
            nuevo->siguiente = primero;
            primero = nuevo;
        }
    }

    void insertarAlFinal(T valor) {
        Nodo<T>* nuevo = new Nodo<T>(valor);
        if (ultimo == NULL) {
            primero = nuevo;
            ultimo = nuevo;
        } else {
            ultimo->siguiente = nuevo;
            ultimo = nuevo;
        }
    }

    bool buscar(T valor) {
        Nodo<T>* actual = primero;
        while (actual != NULL) {
            if (actual->info == valor) return true;
            actual = actual->siguiente;
        }
        return false;
    }

    void eliminar(T valor) {
        if (primero == NULL) {
            cout << "Lista vacia." << endl;
            return;
        }
        if (primero->info == valor) {
            Nodo<T>* temp = primero;
            primero = primero->siguiente;
            if (primero == NULL) ultimo = NULL;
            delete temp;
            return;
        }
        Nodo<T>* anterior = primero;
        Nodo<T>* actual = primero->siguiente;
        while (actual != NULL) {
            if (actual->info == valor) {
                anterior->siguiente = actual->siguiente;
                if (actual == ultimo) ultimo = anterior;
                delete actual;
                return;
            }
            anterior = actual;
            actual = actual->siguiente;
        }
        cout << "Elemento no encontrado." << endl;
    }

    void mostrar() {
        if (primero == NULL) {
            cout << "Lista vacia." << endl;
            return;
        }
        Nodo<T>* actual = primero;
        while (actual != NULL) {
            cout << actual->info;
            if (actual->siguiente != NULL) cout << " -> ";
            actual = actual->siguiente;
        }
        cout << endl;
    }

    T getPrimero() {
        return primero->info;
    }

    T getUltimo() {
        return ultimo->info;
    }
};

#endif