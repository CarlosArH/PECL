#include "Lista.hpp"

Lista::Lista() {
    cabeza = nullptr;
    longitud = 0;
}

Lista::~Lista() {
    while (cabeza != nullptr) {
        NodoLista* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

void Lista::insertar(Proceso* proceso) {
    NodoLista* nuevoNodo = new NodoLista(proceso);
    nuevoNodo->siguiente = cabeza;
    cabeza = nuevoNodo;
    longitud++;
}

void Lista::mostrar() const {
    NodoLista* actual = cabeza;
    while (actual != nullptr) {
        actual->proceso->mostrar();
        actual = actual->siguiente;
    }
}

Proceso* Lista::buscarPorPID(int pid) {
    NodoLista* actual = cabeza;
    while (actual != nullptr) {
        if (actual->proceso->getPID() == pid) {
            return actual->proceso;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

void Lista::eliminarPorPID(int pid) {
    NodoLista* actual = cabeza;
    NodoLista* anterior = nullptr;
    while (actual != nullptr && actual->proceso->getPID() != pid) {
        anterior = actual;
        actual = actual->siguiente;
    }
    if (actual != nullptr) {
        if (anterior == nullptr) {
            cabeza = actual->siguiente;
        } else {
            anterior->siguiente = actual->siguiente;
        }
        delete actual;
        longitud--;
    }
}

void Lista::cambiarPrioridadPorPID(int pid, int nuevaPrioridad) {
    Proceso* proceso = buscarPorPID(pid);
    if (proceso != nullptr) {
        proceso->setPrioridad(nuevaPrioridad);
    }
}

int Lista::getLongitud() const {
    return longitud;
}

void Lista::buscarProcesosListaNormal(Lista listaNormal, Proceso* menorPrioridadNormal){
	// Buscar proceso normal de menor prioridad
    NodoLista* actual = listaNormal.cabeza;
    while (actual != nullptr) {
        if (menorPrioridadNormal == nullptr || actual->proceso->getPrioridad() < menorPrioridadNormal->getPrioridad()) {
            menorPrioridadNormal = actual->proceso;
        }
        actual = actual->siguiente;
    }
    std::cout << "Proceso Normal de menor prioridad:" << std::endl;
    if (menorPrioridadNormal != nullptr) {
        menorPrioridadNormal->mostrar();
    } else {
        std::cout << "No hay procesos normales en la lista." << std::endl;
    }
}
void Lista::buscarProcesosListaTiempoReal(Lista listaTiempoReal, Proceso* mayorPrioridadTiempoReal){
	// Buscar proceso en tiempo real de mayor prioridad
    NodoLista* actual = listaTiempoReal.cabeza;
    while (actual != nullptr) {
        if (mayorPrioridadTiempoReal == nullptr || actual->proceso->getPrioridad() > mayorPrioridadTiempoReal->getPrioridad()) {
            mayorPrioridadTiempoReal = actual->proceso;
        }
        actual = actual->siguiente;
    }
	std::cout << "Proceso en Tiempo Real de mayor prioridad:" << std::endl;
    if (mayorPrioridadTiempoReal != nullptr) {
        mayorPrioridadTiempoReal->mostrar();
    } else {
        std::cout << "No hay procesos en tiempo real en la lista." << std::endl;
    }
}

void Lista::encontrarUsuarioListaNormal(string nombre, Lista listaNormal){
	bool encontrado = false;
    // Buscar en la lista normal
    NodoLista* actual = listaNormal.cabeza;
    while (actual != nullptr) {
        if (actual->proceso->getUsuario() == nombre) {
            actual->proceso->mostrar();
            encontrado = true;
        }
        actual = actual->siguiente;
    }
}
void Lista::encontrarUsuarioListaTiempoReal(string nombre, Lista listaTiempoReal){
	bool encontrado = false;
	// Buscar en la lista de tiempo real
    NodoLista* actual = listaTiempoReal.cabeza;
    while (actual != nullptr) {
        if (actual->proceso->getUsuario() == nombre) {
            actual->proceso->mostrar();
            encontrado = true;
        }
        actual = actual->siguiente;
    }
}

void Lista::mostrarProcesoParaEliminar(Proceso* proceso){
	std::cout << "PID\tUSUARIO\tESTADO\tPRIORIDAD\tTIPO" << std::endl;
	std::cout << proceso->getPID() << "\t" 
				<< proceso->getUsuario() << "\t" 
				<< (proceso->mostrar_proceso() ? "Ejecucion" : "Parado") << "\t" 
				<< proceso->getPrioridad() << "\t\t" 
				<< (proceso->esTiempoReal() ? "Tiempo Real" : "Normal") << std::endl;
	std::cout << "El proceso cuyo PID es " << proceso->getPID()
				<< " es de tipo " << (proceso->esTiempoReal() ? "en tiempo real" : "normal")
				<< ", su estado es " << (proceso->mostrar_proceso() ? "ejecucion" : "parado")
				<< " y su prioridad es: " << proceso->getPrioridad() << std::endl;
}

void Lista::mostrarProcesoParaCambiar(Proceso* proceso){
        std::cout << "PID\tUSUARIO\tESTADO\tPRIORIDAD\tTIPO" << std::endl;
        std::cout << proceso->getPID() << "\t" 
                  << proceso->getUsuario() << "\t" 
                  << (proceso->mostrar_proceso() ? "Ejecución" : "Parado") << "\t" 
                  << proceso->getPrioridad() << "\t\t" 
                  << (proceso->esTiempoReal() ? "Tiempo Real" : "Normal") << std::endl;
}