# Ape1 - Listas Secuenciales

**Asignatura:** Estructura de Datos  
**Universidad:** Universidad Técnica de Ambato  
**Ciclo:** Enero 2026 - Julio 2026  

## Integrantes

| Nombre | GitHub | Parte |
|---|---|---|
| Steven | @Smyl0 | main.cpp |
| Geremy | @GeremyBravo | ListaSimple.h |
| Jonathan | @JonathanChisag | ListaDoble.h |

## Descripción

Implementación de una Lista Simplemente Enlazada y una Lista Doblemente
Enlazada usando templates en C++ para manejar distintos tipos de datos.

## Estructura
```
Ape1_Listas_Secuenciales/
└── src/
    ├── ListaSimple.h
    ├── ListaDoble.h
    └── main.cpp
```

## Operaciones

**Lista Simple:** insertar al inicio, insertar al final, buscar,
eliminar, mostrar, getPrimero, getUltimo.

**Lista Doble:** insertar al inicio, insertar al final, buscar,
eliminar, mostrar inicio-fin, mostrar fin-inicio, getPrimero, getUltimo.

## Tipos probados

- int
- string

## Compilar y ejecutar
```bash
g++ -o programa src/main.cpp
./programa
```

## Conclusiones

Las listas enlazadas permiten manejar datos de forma dinámica.
La lista doble permite recorrer en ambas direcciones gracias al
puntero anterior. El uso de templates permite reutilizar el código
para cualquier tipo de dato.