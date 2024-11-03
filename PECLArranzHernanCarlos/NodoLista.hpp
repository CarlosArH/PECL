#include <iostream>
#include "Proceso.hpp"
using namespace std;

class NodoLista{
public:
	NodoLista(Proceso* p, NodoLista* sig = NULL);
	~NodoLista();
	Proceso* proceso;
	NodoLista* siguiente;
private:

	friend class Lista;
};

typedef NodoLista* pnodoLista;