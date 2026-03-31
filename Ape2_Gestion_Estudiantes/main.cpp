#include "Menu.h"

int main() {
    Curso                curso;
    GestorCalificaciones gestor(curso);
    Menu                 menu(curso, gestor);

    menu.mostrarMenuPrincipal();
    return 0;
}
