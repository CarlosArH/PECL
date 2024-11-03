#include "Cola.hpp"

Cola::Cola()
{
	primero = NULL;
	ultimo = NULL;
	longitud = 0;
}

void Cola::insertar(Proceso* p) {
    pnodoCola nuevo = new NodoCola(p, nullptr);
    
    // Si la cola está vacía, simplemente inserta el nuevo nodo
    if (!primero) {
        primero = nuevo;
        ultimo = nuevo;
    } else {
        pnodoCola actual = primero;
        pnodoCola anterior = nullptr;

        // Buscar la posición correcta para insertar el nuevo nodo
        while (actual != nullptr && actual->proceso->getPrioridad() <= p->getPrioridad()) {
            anterior = actual;
            actual = actual->siguiente;
        }

        // Si se inserta al principio
        if (anterior == nullptr) {
            nuevo->siguiente = primero;
            primero = nuevo;
        } else {
            // Inserta en medio o al final
            nuevo->siguiente = actual;
            anterior->siguiente = nuevo;
            if (actual == nullptr) {
                ultimo = nuevo; // Actualiza el último si se inserta al final
            }
        }
    }
    longitud++;
}


void Cola::mostrar(){
    pnodoCola aux = primero;
    while (aux) {
        Proceso* proceso = aux->proceso; // Obtener el proceso del nodo
        cout << "El proceso cuyo PID es " << proceso->getPID() 
             << " es de tipo " << (proceso->esTiempoReal() ? "en tiempo real" : "normal") 
             << ", su estado es " << (proceso->mostrar_proceso() ? "ejecución" : "parado") 
             << " y su prioridad es: " << proceso->getPrioridad() << endl;
        aux = aux->siguiente; // Avanzar al siguiente nodo
    }
}

Proceso* Cola::eliminar()
{
	if (!primero) return nullptr;
    pnodoCola nodo = primero;
    Proceso* p = nodo->proceso;
    primero = nodo->siguiente;
    if (!primero) {
        ultimo = nullptr;
    }
    delete nodo;
    longitud--;
    return p;
}

Proceso* Cola ::verPrimero() {
	return primero->proceso;
}

bool Cola::estaVacia()  {
    return primero == nullptr;
}

int Cola::getLongitud() {
    return longitud;
}

int Cola::indiceCola(Proceso* p, Cola* colas) {
	//Determinar la cola en la que tine que ir según el tipo de cola y según la longitud de cada cola
		int indiceCola = 0;
		if (p->esTiempoReal()) {
			indiceCola = (colas[2].getLongitud() <= colas[3].getLongitud()) ? 2 : 3; 
		} else {
			indiceCola = (colas[0].getLongitud() <= colas[1].getLongitud()) ? 0 : 1;
		}
	return indiceCola;
}

Cola::~Cola()
{
	while(primero)
		eliminar();
}