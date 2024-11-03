#ifndef PILA_HPP
#define PILA_HPP

#include "NodoPila.hpp"

#include <iostream>

class Pila{
public:
	Pila();
	~Pila();
	void insertar(Proceso* p);
	void generarProceso(int usuarios, int* array, int i);
	void mostrarProcesos() ;
	Proceso* extraer();
	void vaciar() ;
	pnodoPila getCima();
	Proceso* cima() const;
	void mostrar() const;
	bool estaVacia() const;
	int getLongitud() const;
	
	
private:
	pnodoPila ultimo;
	int longitud;
};

#endif