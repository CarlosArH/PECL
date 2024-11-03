#include "Pila.hpp"
#include <algorithm>

Pila::Pila()
{
	ultimo = NULL;
	longitud = 0;
}

void Pila::insertar(Proceso* p)
{
	pnodoPila nuevo;
	nuevo = new NodoPila(p, ultimo);
	ultimo = nuevo;
	longitud++;
}

Proceso* Pila:: extraer()
{
	pnodoPila nodo;
	Proceso* p;
	if(!ultimo)
		return NULL;
	nodo = ultimo;
	ultimo = nodo->siguiente;
	p = nodo->proceso;
	longitud--;
	delete nodo;
	return p;
}

void Pila::vaciar()
{
	while(longitud != 0){
		extraer();
	}
}

Proceso* Pila::cima() const
{
	return ultimo ? ultimo->proceso : nullptr;
}

void Pila::mostrar() const
{
	pnodoPila aux = ultimo;
	cout << "\tEl contenido de la pila es: " << endl;
	while(aux) {
		aux->proceso->mostrar();
		aux = aux->siguiente;
	}
	cout << endl;
}

int Pila::getLongitud() const
{
	return this->longitud;
}

bool Pila::estaVacia() const {
    return ultimo == nullptr;
}

pnodoPila Pila::getCima(){
	return ultimo;
}

Pila::~Pila() {
    while (!estaVacia()) {
        extraer();
    }
}

void Pila::generarProceso(int usuarios, int* array, int i){
	int pid = array[i];
	string usuario = "usuario" + to_string(usuarios++);
	bool tiempoReal = rand() % 2;
	Proceso* proceso = new Proceso(pid, usuario, tiempoReal);
	insertar(proceso);
}

void Pila::mostrarProcesos()  {
    pnodoPila actual= this->getCima();
    while (actual != nullptr) {
        Proceso* proceso = actual->proceso;
        cout << "El proceso cuyo PID es " << proceso->getPID() 
                  << " es de tipo " << (proceso->esTiempoReal() ? "en tiempo real" : "normal") << endl;
        actual = actual->siguiente;
    }
}