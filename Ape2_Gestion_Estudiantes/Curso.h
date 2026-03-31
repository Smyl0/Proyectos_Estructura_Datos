#pragma once
#include "ListaDoble.h"
#include "Estudiante.h"
using namespace std;

// ============================================================
// ISSUE #2 - Steven
// Clase Curso
// Gestiona una ListaDoble<Estudiante>
// ============================================================

class Curso {
private:
    ListaDoble<Estudiante> estudiantes;

public:
    static const int MAX_ESTUDIANTES = 20;

    // CRUD
    bool agregarEstudiante(const Estudiante& e);
    bool eliminarEstudiante(int indice);
    bool modificarEstudiante(int indice, const Estudiante& e);
    void listarEstudiantes() const;

    // Busqueda — Issue #2
    Estudiante* buscarPorCedula(const string& cedula);

    // Promedios — Issue #3
    double promedioEstudiante(const string& cedula);
    double promedioGeneral()  const;

    // Utilidades
    int  totalEstudiantes() const;
    bool estaLleno()        const;
    bool estaVacio()        const;
    ListaDoble<Estudiante>& getEstudiantes();
};
