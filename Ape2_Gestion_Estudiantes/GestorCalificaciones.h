#pragma once
#include "Curso.h"
using namespace std;


class GestorCalificaciones {
private:
    Curso& curso;

    double leerNota(const string& mensaje);
    int    leerIndice(const string& mensaje);

public:
    GestorCalificaciones(Curso& curso);


    bool registrarNota (const string& cedula, double nota);
    bool modificarNota (const string& cedula, int indice, double nuevaNota);
    bool eliminarNota  (const string& cedula, int indice);
    void listarNotas   (const string& cedula) const;


    void submenuCalificaciones();
};
