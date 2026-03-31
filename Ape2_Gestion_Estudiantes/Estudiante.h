#pragma once
#include "ListaDoble.h"
#include <string>
using namespace std;

// ============================================================
// ISSUE #1 - Steven
// Clase Estudiante
// Las notas se almacenan en una ListaDoble<double>
// ============================================================

class Estudiante {
private:
    string cedula;
    string nombres;
    string apellidos;
    string fechaNacimiento; // formato DD/MM/AAAA
    ListaDoble<double> notas;

public:
    static const int MAX_NOTAS = 7;

    Estudiante();
    Estudiante(string cedula, string nombres,
               string apellidos, string fechaNacimiento);

    // Getters
    string getCedula()          const;
    string getNombres()         const;
    string getApellidos()       const;
    string getFechaNacimiento() const;
    int    getEdad()            const;
    ListaDoble<double>& getNotas();

    // Setters
    void setCedula(string c);
    void setNombres(string n);
    void setApellidos(string a);
    void setFechaNacimiento(string f);

    // Operaciones sobre notas
    bool   agregarNota(double nota);
    bool   modificarNota(int indice, double nuevaNota);
    bool   eliminarNota(int indice);
    double calcularPromedio() const;
    bool   tieneNotas()       const;
    bool   notasCompletas()   const;

    // Mostrar
    void mostrarDatos()   const;
    void mostrarResumen() const;
};
