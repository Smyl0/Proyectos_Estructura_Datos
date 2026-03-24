// Listas Secuenciales - Steven
#include <iostream>
#include "ListaSimple.h"
#include "ListaDoble.h"

using namespace std;

int main() {

    // Lista Simple con int
    ListaSimple<int> ls1;
    ls1.insertarAlInicio(5);
    ls1.insertarAlFinal(10);
    ls1.insertarAlFinal(20);
    ls1.insertarAlFinal(30);

    cout << "Lista simple int: ";
    ls1.mostrar();
    cout << "Primero: " << ls1.getPrimero() << endl;
    cout << "Ultimo: " << ls1.getUltimo() << endl;
    cout << "Buscar 10: " << (ls1.buscar(10) ? "Encontrado" : "No encontrado") << endl;
    cout << "Buscar 99: " << (ls1.buscar(99) ? "Encontrado" : "No encontrado") << endl;
    ls1.eliminar(10);
    cout << "Despues de eliminar 10: ";
    ls1.mostrar();

    // Lista Simple con string
    ListaSimple<string> ls2;
    ls2.insertarAlInicio("Hola");
    ls2.insertarAlFinal("Mundo");
    ls2.insertarAlFinal("C++");

    cout << "\nLista simple string: ";
    ls2.mostrar();
    cout << "Primero: " << ls2.getPrimero() << endl;
    cout << "Ultimo: " << ls2.getUltimo() << endl;
    ls2.eliminar("Mundo");
    cout << "Despues de eliminar Mundo: ";
    ls2.mostrar();

    // Lista Doble con int
    ListaDoble<int> ld1;
    ld1.insertarAlInicio(50);
    ld1.insertarAlFinal(100);
    ld1.insertarAlFinal(200);
    ld1.insertarAlFinal(300);

    cout << "\nLista doble int (inicio->fin): ";
    ld1.mostrarInicioFin();
    cout << "Lista doble int (fin->inicio): ";
    ld1.mostrarFinInicio();
    cout << "Primero: " << ld1.getPrimero() << endl;
    cout << "Ultimo: " << ld1.getUltimo() << endl;
    cout << "Buscar 200: " << (ld1.buscar(200) ? "Encontrado" : "No encontrado") << endl;
    ld1.eliminar(200);
    cout << "Despues de eliminar 200: ";
    ld1.mostrarInicioFin();

    // Lista Doble con string
    ListaDoble<string> ld2;
    ld2.insertarAlInicio("Nodo0");
    ld2.insertarAlFinal("Nodo1");
    ld2.insertarAlFinal("Nodo2");
    ld2.insertarAlFinal("Nodo3");

    cout << "\nLista doble string (inicio->fin): ";
    ld2.mostrarInicioFin();
    cout << "Lista doble string (fin->inicio): ";
    ld2.mostrarFinInicio();
    ld2.eliminar("Nodo2");
    cout << "Despues de eliminar Nodo2: ";
    ld2.mostrarInicioFin();

    return 0;
}