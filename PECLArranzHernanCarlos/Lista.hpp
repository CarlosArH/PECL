#ifndef LISTA_HPP
#define LISTA_HPP

#include "NodoLista.hpp"
#include <iostream>
#include <string>

class Lista {
public:
    Lista();
    ~Lista();

    void insertar(Proceso* proceso);
    void mostrar() const;
    Proceso* buscarPorPID(int pid) ;
    void eliminarPorPID(int pid);
    void cambiarPrioridadPorPID(int pid, int nuevaPrioridad);
    int getLongitud() const;

    pnodoLista cabeza;
    int longitud;
};

#endif // LISTA_HPP