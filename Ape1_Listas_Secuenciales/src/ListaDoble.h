#ifndef LISTADOBLE_H
#define LISTADOBLE_H

#include <iostream>
using namespace std;

template <typename T>
struct NodoDoble {
    T info;
    NodoDoble<T>* siguiente;
    NodoDoble<T>* anterior;

    NodoDoble(T valor) {
        info = valor;
        siguiente = NULL;
        anterior = NULL;
    }
};

template <typename T>
class ListaDoble {
private:
    NodoDoble<T>* primero;
    NodoDoble<T>* ultimo;

public:
    ListaDoble() {
        primero = NULL;
        ultimo = NULL;
    }

    ~ListaDoble() {
        NodoDoble<T>* actual = primero;
        while (actual != NULL) {
            NodoDoble<T>* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
    }

    void insertarAlInicio(T valor) {
        NodoDoble<T>* nuevo = new NodoDoble<T>(valor);
        if (primero == NULL) {
            primero = nuevo;
            ultimo = nuevo;
        } else {
            nuevo->siguiente = primero;
            primero->anterior = nuevo;
            primero = nuevo;
        }
    }

    void insertarAlFinal(T valor) {
        NodoDoble<T>* nuevo = new NodoDoble<T>(valor);
        if (ultimo == NULL) {
            primero = nuevo;
            ultimo = nuevo;
        } else {
            ultimo->siguiente = nuevo;
            nuevo->anterior = ultimo;
            ultimo = nuevo;
        }
    }

    bool buscar(T valor) {
        NodoDoble<T>* actual = primero;
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
        NodoDoble<T>* actual = primero;
        while (actual != NULL) {
            if (actual->info == valor) {
                if (actual->anterior != NULL)
                    actual->anterior->siguiente = actual->siguiente;
                else
                    primero = actual->siguiente;
                if (actual->siguiente != NULL)
                    actual->siguiente->anterior = actual->anterior;
                else
                    ultimo = actual->anterior;
                delete actual;
                return;
            }
            actual = actual->siguiente;
        }
        cout << "Elemento no encontrado." << endl;
    }

    void mostrarInicioFin() {
        if (primero == NULL) {
            cout << "Lista vacia." << endl;
            return;
        }
        NodoDoble<T>* actual = primero;
        while (actual != NULL) {
            cout << actual->info;
            if (actual->siguiente != NULL) cout << " <-> ";
            actual = actual->siguiente;
        }
        cout << endl;
    }

    void mostrarFinInicio() {
        if (ultimo == NULL) {
            cout << "Lista vacia." << endl;
            return;
        }
        NodoDoble<T>* actual = ultimo;
        while (actual != NULL) {
            cout << actual->info;
            if (actual->anterior != NULL) cout << " <-> ";
            actual = actual->anterior;
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
