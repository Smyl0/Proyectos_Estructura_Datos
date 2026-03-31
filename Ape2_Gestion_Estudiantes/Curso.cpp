#include "Curso.h"
#include <iostream>
#include <iomanip>
using namespace std;

// ============================================================
// ISSUE #2 - Steven
// ============================================================

bool Curso::agregarEstudiante(const Estudiante& e) {
    if (estaLleno()) return false;
    estudiantes.agregar(e);
    return true;
}

bool Curso::eliminarEstudiante(int indice) {
    return estudiantes.eliminar(indice);
}

bool Curso::modificarEstudiante(int indice, const Estudiante& e) {
    return estudiantes.modificar(indice, e);
}

void Curso::listarEstudiantes() const {
    if (estudiantes.estaVacia()) {
        cout << "  No hay estudiantes registrados." << endl;
        return;
    }
    cout << "\n" << left
         << setw(5)  << "N."
         << setw(13) << "Cedula"
         << setw(18) << "Nombres"
         << setw(18) << "Apellidos"
         << setw(14) << "F.Nacimiento"
         << setw(5)  << "Edad" << endl;
    cout << string(73, '-') << endl;

    // Recorrido de la lista doblemente enlazada (cabeza -> cola)
    Nodo<Estudiante>* actual = estudiantes.getCabeza();
    int i = 1;
    while (actual != nullptr) {
        const Estudiante& e = actual->dato;
        cout << left
             << setw(5)  << i
             << setw(13) << e.getCedula()
             << setw(18) << e.getNombres()
             << setw(18) << e.getApellidos()
             << setw(14) << e.getFechaNacimiento()
             << setw(5)  << e.getEdad() << endl;
        actual = actual->siguiente;
        i++;
    }
    cout << string(73, '-') << endl;
    cout << "  Total: " << estudiantes.getTamanio() << " estudiante(s)" << endl;
}

// ============================================================
// ISSUE #2 - Steven
// Busqueda recorriendo la lista doblemente enlazada
// ============================================================
Estudiante* Curso::buscarPorCedula(const string& cedula) {
    // Recorrido cabeza -> cola buscando la cedula
    Nodo<Estudiante>* actual = estudiantes.getCabeza();
    while (actual != nullptr) {
        if (actual->dato.getCedula() == cedula)
            return &(actual->dato);
        actual = actual->siguiente;
    }
    return nullptr; // No encontrado
}

// ============================================================
// ISSUE #3 - Steven
// Promedio individual y promedio general del curso
// ============================================================
double Curso::promedioEstudiante(const string& cedula) {
    Estudiante* e = buscarPorCedula(cedula);
    if (e == nullptr) return -1.0;
    return e->calcularPromedio();
}

double Curso::promedioGeneral() const {
    double suma = 0.0;
    int    total = 0;

    // Recorrer lista de estudiantes (cabeza -> cola)
    Nodo<Estudiante>* nodoEst = estudiantes.getCabeza();
    while (nodoEst != nullptr) {
        // Recorrer lista de notas del estudiante (cabeza -> cola)
        Nodo<double>* nodoNota = nodoEst->dato.getNotas().getCabeza();
        while (nodoNota != nullptr) {
            suma += nodoNota->dato;
            total++;
            nodoNota = nodoNota->siguiente;
        }
        nodoEst = nodoEst->siguiente;
    }

    if (total == 0) return -1.0;
    return suma / total;
}

int  Curso::totalEstudiantes() const { return estudiantes.getTamanio(); }
bool Curso::estaLleno()        const { return estudiantes.getTamanio() >= MAX_ESTUDIANTES; }
bool Curso::estaVacio()        const { return estudiantes.estaVacia(); }
ListaDoble<Estudiante>& Curso::getEstudiantes() { return estudiantes; }
