#pragma once
#include "Nodo.h"
#include <stdexcept>
using namespace std;

// ============================================================
// ISSUE #1 - Steven
// Lista doblemente enlazada generica
// Operaciones: agregar, eliminar, obtener, tamanio
// ============================================================

template <typename T>
class ListaDoble {
private:
    Nodo<T>* cabeza;
    Nodo<T>* cola;
    int tamanio;

public:
    ListaDoble() {
        cabeza  = nullptr;
        cola    = nullptr;
        tamanio = 0;
    }

    ~ListaDoble() {
        limpiar();
    }

    // Agregar al final
    void agregar(T dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato);
        if (cabeza == nullptr) {
            cabeza = nuevo;
            cola   = nuevo;
        } else {
            nuevo->anterior = cola;
            cola->siguiente = nuevo;
            cola = nuevo;
        }
        tamanio++;
    }

    // Eliminar por indice (base 0)
    bool eliminar(int indice) {
        if (indice < 0 || indice >= tamanio) return false;

        Nodo<T>* actual = getNodo(indice);

        if (actual->anterior != nullptr)
            actual->anterior->siguiente = actual->siguiente;
        else
            cabeza = actual->siguiente;

        if (actual->siguiente != nullptr)
            actual->siguiente->anterior = actual->anterior;
        else
            cola = actual->anterior;

        delete actual;
        tamanio--;
        return true;
    }

    // Obtener referencia al dato por indice (base 0)
    T& obtener(int indice) {
        if (indice < 0 || indice >= tamanio)
            throw out_of_range("Indice fuera de rango");
        return getNodo(indice)->dato;
    }

    // Modificar dato por indice
    bool modificar(int indice, T dato) {
        if (indice < 0 || indice >= tamanio) return false;
        getNodo(indice)->dato = dato;
        return true;
    }

    int getTamanio() const { return tamanio; }
    bool estaVacia() const { return tamanio == 0; }

    Nodo<T>* getCabeza() const { return cabeza; }

    void limpiar() {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            Nodo<T>* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
        cabeza  = nullptr;
        cola    = nullptr;
        tamanio = 0;
    }

private:
    // Navega hasta el nodo del indice dado
    Nodo<T>* getNodo(int indice) const {
        Nodo<T>* actual;
        // Optimizacion: navegar desde cabeza o cola segun cercania
        if (indice <= tamanio / 2) {
            actual = cabeza;
            for (int i = 0; i < indice; i++)
                actual = actual->siguiente;
        } else {
            actual = cola;
            for (int i = tamanio - 1; i > indice; i--)
                actual = actual->anterior;
        }
        return actual;
    }
};
