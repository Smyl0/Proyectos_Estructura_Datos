#include "Menu.h"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;


Menu::Menu(Curso& curso, GestorCalificaciones& gestor)
    : curso(curso), gestor(gestor) {}

// ---------- Helpers de entrada ----------
int Menu::leerEntero(const string& mensaje) {
    int v;
    while (true) {
        cout << mensaje;
        if (cin >> v) { cin.ignore(numeric_limits<streamsize>::max(), '\n'); return v; }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  [!] Entrada invalida." << endl;
    }
}

string Menu::leerTexto(const string& mensaje) {
    string v;
    cout << mensaje;
    getline(cin, v);
    return v;
}

bool Menu::preguntarRepetir(const string& accion) {
    cout << "  Desea " << accion << " otra vez? (s/n): ";
    string r; getline(cin, r);
    return (r == "s" || r == "S");
}

void Menu::pausar() {
    cout << "\n  Presione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Menu::limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// ============================================================
// ISSUE #4 - Jonathan
// Menu principal
// ============================================================
void Menu::mostrarMenuPrincipal() {
    int op;
    do {
        limpiarPantalla();
        cout << "================================" << endl;
        cout << "       GESTOR DE PERSONAS       " << endl;
        cout << "================================" << endl;
        cout << "  1. Estudiantes"                 << endl;
        cout << "  2. Registro de calificaciones"  << endl;
        cout << "  3. Promedio de un estudiante"   << endl;
        cout << "  4. Promedio general del curso"  << endl;
        cout << "  0. Salir"                       << endl;
        cout << "================================" << endl;
        op = leerEntero("  Opcion (0-4): ");

        switch (op) {
            case 1: submenuEstudiantes();            break;
            case 2: gestor.submenuCalificaciones();  break;
            case 3: opcionPromedioEstudiante();      break;
            case 4: opcionPromedioCurso();           break;
            case 0: cout << "\n  Hasta luego!\n"; break;
            default:
                cout << "  [!] Opcion invalida." << endl;
                pausar();
        }
    } while (op != 0);
}

// ============================================================
// ISSUE #5 - Jonathan
// Submenu estudiantes: listar + ingresar
// ============================================================
void Menu::submenuEstudiantes() {
    int op;
    do {
        limpiarPantalla();
        cout << "\n=== GESTION DE ESTUDIANTES ===" << endl;
        curso.listarEstudiantes();
        cout << "\n  1. Ingresar estudiante" << endl;
        cout << "  2. Modificar estudiante" << endl;
        cout << "  3. Eliminar estudiante"  << endl;
        cout << "  0. Regresar"             << endl;
        op = leerEntero("  Opcion: ");

        switch (op) {
            case 1: ingresarEstudiante();  break;
            case 2: modificarEstudiante(); break;
            case 3: eliminarEstudiante();  break;
            case 0: break;
            default: cout << "  [!] Opcion invalida." << endl; pausar();
        }
    } while (op != 0);
}

void Menu::ingresarEstudiante() {
    do {
        limpiarPantalla();
        if (curso.estaLleno()) {
            cout << "  [!] Cupo maximo alcanzado ("
                 << Curso::MAX_ESTUDIANTES << " estudiantes)." << endl;
            pausar(); return;
        }
        cout << "\n--- Nuevo estudiante ---" << endl;
        string cedula    = leerTexto("  Cedula                    : ");
        string nombres   = leerTexto("  Nombres                   : ");
        string apellidos = leerTexto("  Apellidos                 : ");
        string fecha     = leerTexto("  Fecha nacimiento DD/MM/AAAA: ");

        Estudiante nuevo(cedula, nombres, apellidos, fecha);
        // agregarEstudiante agrega al final de la ListaDoble
        if (curso.agregarEstudiante(nuevo))
            cout << "  [OK] Estudiante agregado al final de la lista." << endl;
        else
            cout << "  [!] No se pudo registrar." << endl;
        pausar();
    } while (preguntarRepetir("ingresar un estudiante"));
}

// ============================================================
// ISSUE #6 - Jonathan
// Modificar y eliminar usando indice sobre la lista
// ============================================================
void Menu::modificarEstudiante() {
    if (curso.estaVacio()) {
        cout << "  [!] No hay estudiantes registrados." << endl;
        pausar(); return;
    }
    do {
        limpiarPantalla();
        cout << "\n--- Modificar estudiante ---" << endl;
        curso.listarEstudiantes();
        int num = leerEntero("  Numero (0 = cancelar): ");
        if (num == 0) return;
        if (num < 1 || num > curso.totalEstudiantes()) {
            cout << "  [!] Numero invalido." << endl;
            pausar(); continue;
        }

        // Obtener referencia al nodo de la lista
        Estudiante& actual = curso.getEstudiantes().obtener(num - 1);
        cout << "\n  Datos actuales:" << endl;
        actual.mostrarDatos();
        cout << "\n  Deje en blanco para mantener el valor actual:" << endl;

        string cedula    = leerTexto("  Cedula    [" + actual.getCedula()    + "]: ");
        string nombres   = leerTexto("  Nombres   [" + actual.getNombres()   + "]: ");
        string apellidos = leerTexto("  Apellidos [" + actual.getApellidos() + "]: ");
        string fecha     = leerTexto("  Fecha     [" + actual.getFechaNacimiento() + "]: ");

        if (cedula.empty())    cedula    = actual.getCedula();
        if (nombres.empty())   nombres   = actual.getNombres();
        if (apellidos.empty()) apellidos = actual.getApellidos();
        if (fecha.empty())     fecha     = actual.getFechaNacimiento();

        // Crear estudiante modificado y preservar notas
        Estudiante modificado(cedula, nombres, apellidos, fecha);
        Nodo<double>* n = actual.getNotas().getCabeza();
        while (n != nullptr) {
            modificado.agregarNota(n->dato);
            n = n->siguiente;
        }

        // Modificar en la lista doblemente enlazada
        curso.modificarEstudiante(num - 1, modificado);
        cout << "  [OK] Estudiante modificado." << endl;
        pausar();
    } while (preguntarRepetir("modificar un estudiante"));
}

void Menu::eliminarEstudiante() {
    if (curso.estaVacio()) {
        cout << "  [!] No hay estudiantes para eliminar." << endl;
        pausar(); return;
    }
    do {
        limpiarPantalla();
        cout << "\n--- Eliminar estudiante ---" << endl;
        curso.listarEstudiantes();
        int num = leerEntero("  Numero (0 = cancelar): ");
        if (num == 0) return;
        if (num < 1 || num > curso.totalEstudiantes()) {
            cout << "  [!] Numero invalido." << endl;
            pausar(); continue;
        }

        Estudiante& e = curso.getEstudiantes().obtener(num - 1);
        cout << "  Confirma eliminar a "
             << e.getNombres() << " " << e.getApellidos() << "? (s/n): ";
        string conf; getline(cin, conf);

        if (conf == "s" || conf == "S") {
            // Eliminar nodo de la lista doblemente enlazada
            curso.eliminarEstudiante(num - 1);
            cout << "  [OK] Estudiante eliminado." << endl;
        } else {
            cout << "  Operacion cancelada." << endl;
        }
        pausar();
    } while (!curso.estaVacio() && preguntarRepetir("eliminar un estudiante"));
}

// ============================================================
// ISSUE #3 - Steven (invocado desde Menu)
// ============================================================
void Menu::opcionPromedioEstudiante() {
    limpiarPantalla();
    cout << "\n=== PROMEDIO DE UN ESTUDIANTE ===" << endl;
    string cedula = leerTexto("  Cedula: ");

    Estudiante* e = curso.buscarPorCedula(cedula);
    if (e == nullptr) {
        cout << "  [!] No se encontro un estudiante con cedula: " << cedula << endl;
    } else {
        cout << "\n  Nombre  : " << e->getNombres() << " " << e->getApellidos() << endl;
        cout << "  Edad    : " << e->getEdad() << " anios" << endl;
        if (!e->tieneNotas())
            cout << "  Promedio: Sin calificaciones registradas." << endl;
        else
            cout << "  Promedio: " << fixed << setprecision(2) << e->calcularPromedio() << endl;
    }
    pausar();
}

// ============================================================
// ISSUE #9 - Geremy (invocado desde Menu)
// ============================================================
void Menu::opcionPromedioCurso() {
    limpiarPantalla();
    cout << "\n=== PROMEDIO GENERAL DEL CURSO ===" << endl;
    double p = curso.promedioGeneral();
    if (p < 0)
        cout << "  No se han registrado calificaciones de estudiantes." << endl;
    else
        cout << "  Promedio general: " << fixed << setprecision(2) << p << endl;
    pausar();
}
