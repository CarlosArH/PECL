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
	void buscarProcesosListaNormal(Lista listaNormal, Proceso* menorPrioridadNormal);
    void buscarProcesosListaTiempoReal(Lista listaTiempoReal, Proceso* mayorPrioridadTiempoReal);
	void encontrarUsuarioListaNormal(string nombre, Lista listaNormal);
	void encontrarUsuarioListaTiempoReal(string nombre, Lista listaTiempoReal);
	pnodoLista cabeza;
    int longitud;
	void mostrarProcesoParaEliminar(Proceso* proceso);
	void mostrarProcesoParaCambiar(Proceso*proceso);
};

#endif // LISTA_HPP