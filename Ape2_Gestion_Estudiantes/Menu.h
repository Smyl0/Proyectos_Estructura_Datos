#pragma once
#include "Curso.h"
#include "GestorCalificaciones.h"
using namespace std;


class Menu {
private:
    Curso&                 curso;
    GestorCalificaciones&  gestor;

    // Helpers de entrada
    int    leerEntero (const string& mensaje);
    double leerDouble (const string& mensaje);
    string leerTexto  (const string& mensaje);
    bool   preguntarRepetir(const string& accion);
    void   pausar();
    void   limpiarPantalla();

public:
    Menu(Curso& curso, GestorCalificaciones& gestor);

    void mostrarMenuPrincipal();   // Issue #4

    void submenuEstudiantes();     // Issue #5 y #6
    void ingresarEstudiante();     // Issue #5
    void modificarEstudiante();    // Issue #6
    void eliminarEstudiante();     // Issue #6

    void opcionPromedioEstudiante(); // Opcion 3 — Steven
    void opcionPromedioCurso();      // Opcion 4 — Geremy
};
