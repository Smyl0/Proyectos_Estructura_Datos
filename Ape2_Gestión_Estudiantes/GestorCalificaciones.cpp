#include "GestorCalificaciones.h"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

GestorCalificaciones::GestorCalificaciones(Curso& curso) : curso(curso) {}

double GestorCalificaciones::leerNota(const string& mensaje) {
    double v;
    while (true) {
        cout << mensaje;
        if (cin >> v && v >= 0.0 && v <= 10.0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return v;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  [!] Ingrese un valor valido entre 0.0 y 10.0" << endl;
    }
}

int GestorCalificaciones::leerIndice(const string& mensaje) {
    int v;
    cout << mensaje;
    cin >> v;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return v;
}

bool GestorCalificaciones::registrarNota(const string& cedula, double nota) {
    Estudiante* e = curso.buscarPorCedula(cedula);
    if (e == nullptr) return false;
    return e->agregarNota(nota);
}

bool GestorCalificaciones::modificarNota(const string& cedula,
                                          int indice, double nuevaNota) {
    Estudiante* e = curso.buscarPorCedula(cedula);
    if (e == nullptr) return false;
    return e->modificarNota(indice, nuevaNota);
}

bool GestorCalificaciones::eliminarNota(const string& cedula, int indice) {
    Estudiante* e = curso.buscarPorCedula(cedula);
    if (e == nullptr) return false;
    return e->eliminarNota(indice);
}

void GestorCalificaciones::listarNotas(const string& cedula) const {
    Estudiante* e = const_cast<Curso&>(curso).buscarPorCedula(cedula);
    if (e == nullptr) { cout << "  Estudiante no encontrado." << endl; return; }

    ListaDoble<double>& notas = e->getNotas();
    if (notas.estaVacia()) {
        cout << "  Sin calificaciones registradas." << endl;
        return;
    }

    cout << "\n" << left << setw(6) << "N." << setw(10) << "Nota" << endl;
    cout << string(16, '-') << endl;

    Nodo<double>* actual = notas.getCabeza();
    int i = 1;
    while (actual != nullptr) {
        cout << left << setw(6) << i
             << fixed << setprecision(2) << actual->dato << endl;
        actual = actual->siguiente;
        i++;
    }
    cout << string(16, '-') << endl;
    cout << "  " << notas.getTamanio() << "/" << Estudiante::MAX_NOTAS
         << " calificaciones registradas." << endl;
}

void GestorCalificaciones::submenuCalificaciones() {
    cout << "\n=== REGISTRO DE CALIFICACIONES ===" << endl;

    string cedula;
    Estudiante* estudiante = nullptr;

    while (true) {
        cout << "  Cedula (0 = regresar): ";
        cin >> cedula;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (cedula == "0") return;

        estudiante = curso.buscarPorCedula(cedula);
        if (estudiante != nullptr) break;

        cout << "  [!] Cedula no encontrada." << endl;
        cout << "  1. Intentar otra cedula   2. Regresar" << endl;
        cout << "  Opcion: ";
        string op; getline(cin, op);
        if (op == "2") return;
    }

    cout << "\n  Estudiante : " << estudiante->getNombres()
         << " " << estudiante->getApellidos() << endl;
    cout << "  Edad       : " << estudiante->getEdad() << " anios" << endl;

    int opcion;
    do {
        cout << "\n--- Calificaciones ---" << endl;
        listarNotas(cedula);
        cout << "\n  1. Agregar nota" << endl;
        cout << "  2. Modificar nota" << endl;
        cout << "  3. Eliminar nota" << endl;
        cout << "  0. Regresar" << endl;
        cout << "  Opcion: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (opcion == 1) {
            if (estudiante->notasCompletas()) {
                cout << "  [!] Ya se ingresaron todas las notas posibles ("
                     << Estudiante::MAX_NOTAS << "/" << Estudiante::MAX_NOTAS << ")." << endl;
            } else {
                double nota = leerNota("  Nota (0.0 - 10.0): ");
                if (registrarNota(cedula, nota)) {
                    cout << "  [OK] Nota agregada al final de la lista." << endl;
                    if (estudiante->notasCompletas())
                        cout << "  [!] Lista de notas completa." << endl;
                }
            }
        } else if (opcion == 2) {
            int idx = leerIndice("  Numero de nota a modificar: ");
            double nueva = leerNota("  Nueva nota (0.0 - 10.0): ");
            if (modificarNota(cedula, idx - 1, nueva))
                cout << "  [OK] Nota modificada." << endl;
            else
                cout << "  [!] Indice invalido." << endl;
        } else if (opcion == 3) {
            int idx = leerIndice("  Numero de nota a eliminar: ");
            if (eliminarNota(cedula, idx - 1))
                cout << "  [OK] Nota eliminada de la lista." << endl;
            else
                cout << "  [!] Indice invalido." << endl;
        }
    } while (opcion != 0);
}