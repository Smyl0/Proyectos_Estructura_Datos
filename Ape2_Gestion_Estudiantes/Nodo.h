#pragma once

// ============================================================
// ISSUE #1 - Steven
// Nodo generico para lista doblemente enlazada
// Cada nodo guarda un dato de tipo T y punteros
// al nodo anterior y al siguiente
// ============================================================

template <typename T>
struct Nodo {
    T dato;
    Nodo<T>* anterior;
    Nodo<T>* siguiente;

    Nodo(T dato) {
        this->dato     = dato;
        this->anterior = nullptr;
        this->siguiente = nullptr;
    }
};
