#ifndef LISTA_HPP
#define LISTA_HPP

#include "NodoLista.hpp"
#include <iostream>
#include <string>
#include <iomanip>

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
	void buscarProcesosListaNormal(Proceso* menorPrioridadNormal);
    void buscarProcesosListaTiempoReal(Proceso* mayorPrioridadTiempoReal);
	void encontrarUsuarioListaNormal(string nombre);
	void encontrarUsuarioListaTiempoReal(string nombre);
	pnodoLista cabeza;
    int longitud;
	void mostrarProcesoParaEliminar(Proceso* proceso);
	void mostrarProcesoParaCambiar(Proceso*proceso);
};

#endif // LISTA_HPP