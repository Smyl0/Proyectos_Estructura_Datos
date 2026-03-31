#include "Estudiante.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdio>
using namespace std;

// ============================================================
// ISSUE #1 - Steven
// ============================================================

Estudiante::Estudiante() {}

Estudiante::Estudiante(string cedula, string nombres,
                       string apellidos, string fechaNacimiento) {
    this->cedula          = cedula;
    this->nombres         = nombres;
    this->apellidos       = apellidos;
    this->fechaNacimiento = fechaNacimiento;
}

// ---------- Getters ----------
string Estudiante::getCedula()          const { return cedula; }
string Estudiante::getNombres()         const { return nombres; }
string Estudiante::getApellidos()       const { return apellidos; }
string Estudiante::getFechaNacimiento() const { return fechaNacimiento; }
ListaDoble<double>& Estudiante::getNotas()    { return notas; }

int Estudiante::getEdad() const {
    int dia = 1, mes = 1, anio = 2000;
    sscanf(fechaNacimiento.c_str(), "%d/%d/%d", &dia, &mes, &anio);
    time_t t   = time(nullptr);
    tm* hoy    = localtime(&t);
    int edad   = (hoy->tm_year + 1900) - anio;
    int mesHoy = hoy->tm_mon + 1;
    int diaHoy = hoy->tm_mday;
    if (mesHoy < mes || (mesHoy == mes && diaHoy < dia)) edad--;
    return edad;
}

// ---------- Setters ----------
void Estudiante::setCedula(string c)          { cedula = c; }
void Estudiante::setNombres(string n)         { nombres = n; }
void Estudiante::setApellidos(string a)       { apellidos = a; }
void Estudiante::setFechaNacimiento(string f) { fechaNacimiento = f; }

// ---------- Notas (sobre la ListaDoble interna) ----------
bool Estudiante::agregarNota(double nota) {
    if (notasCompletas()) return false;
    notas.agregar(nota);
    return true;
}

bool Estudiante::modificarNota(int indice, double nuevaNota) {
    return notas.modificar(indice, nuevaNota);
}

bool Estudiante::eliminarNota(int indice) {
    return notas.eliminar(indice);
}

double Estudiante::calcularPromedio() const {
    if (notas.estaVacia()) return 0.0;
    double suma = 0.0;
    // Recorrer lista doblemente enlazada con puntero
    Nodo<double>* actual = notas.getCabeza();
    while (actual != nullptr) {
        suma += actual->dato;
        actual = actual->siguiente;
    }
    return suma / notas.getTamanio();
}

bool Estudiante::tieneNotas()     const { return !notas.estaVacia(); }
bool Estudiante::notasCompletas() const { return notas.getTamanio() >= MAX_NOTAS; }

// ---------- Mostrar ----------
void Estudiante::mostrarDatos() const {
    cout << "  Cedula          : " << cedula          << endl;
    cout << "  Nombres         : " << nombres         << endl;
    cout << "  Apellidos       : " << apellidos       << endl;
    cout << "  Fecha Nacimiento: " << fechaNacimiento << endl;
    cout << "  Edad            : " << getEdad() << " anios" << endl;
}

void Estudiante::mostrarResumen() const {
    cout << nombres << " " << apellidos
         << "  |  CI: " << cedula
         << "  |  Edad: " << getEdad() << endl;
}
