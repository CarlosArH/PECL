#ifndef COLA_HPP
#define COLA_HPP

#include "NodoCola.hpp"

#include <iostream>


class Cola{
public:
	Cola();
	~Cola();	
	void insertar(Proceso* p);
	Proceso* eliminar();
	bool estaVacia();
	int getLongitud();
	void mostrar();
	Proceso* verPrimero();
	int indiceCola(Proceso* p, Cola* colas);
private:
	pnodoCola primero, ultimo;
	int longitud;
};

#endif