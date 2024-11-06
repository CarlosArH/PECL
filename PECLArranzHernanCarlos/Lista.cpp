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

    // Mostrar encabezados
    std::cout << std::left << std::setw(10) << "PID" 
              << std::setw(15) << "USUARIO" 
              << std::setw(15) << "TIPO" 
              << std::setw(15) << "ESTADO" 
              << std::setw(10) << "PRIORIDAD" 
              << std::endl;

    // Mostrar cada proceso en la lista
    while (actual != nullptr) {
        // Imprimir directamente los atributos del proceso
        std::cout << std::left << std::setw(10) << actual->proceso->getPID() 
                  << std::setw(15) << actual->proceso->getUsuario() 
                  << std::setw(15) << (actual->proceso->esTiempoReal() ? "Tiempo Real" : "Normal") 
                  << std::setw(15) << (actual->proceso->mostrar_proceso() ? "Ejecucion" : "Parado") 
                  << std::setw(10) << actual->proceso->getPrioridad() 
                  << std::endl;

        actual = actual->siguiente;  // Avanza al siguiente nodo
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

void Lista::buscarProcesosListaNormal(Proceso* menorPrioridadNormal){
	// Buscar proceso normal de menor prioridad
    NodoLista* actual = this->cabeza;
    while (actual != nullptr) {
        if (menorPrioridadNormal == nullptr || actual->proceso->getPrioridad() < menorPrioridadNormal->getPrioridad()) {
            menorPrioridadNormal = actual->proceso;
        }
        actual = actual->siguiente;
    }
    std::cout << "Normal menor prioridad >\t";
    if (menorPrioridadNormal != nullptr) {
        menorPrioridadNormal->mostrar();
    } else {
        std::cout << "No hay procesos normales en la lista." << std::endl;
    }
}
void Lista::buscarProcesosListaTiempoReal(Proceso* mayorPrioridadTiempoReal){
	// Buscar proceso en tiempo real de mayor prioridad
    NodoLista* actual = this->cabeza;
    while (actual != nullptr) {
        if (mayorPrioridadTiempoReal == nullptr || actual->proceso->getPrioridad() > mayorPrioridadTiempoReal->getPrioridad()) {
            mayorPrioridadTiempoReal = actual->proceso;
        }
        actual = actual->siguiente;
    }
	std::cout << "Tiempo real menor prioridad >\t";
    if (mayorPrioridadTiempoReal != nullptr) {
        mayorPrioridadTiempoReal->mostrar();
    } else {
        std::cout << "No hay procesos en tiempo real en la lista." << std::endl;
    }
}

void Lista::encontrarUsuarioListaNormal(string nombre){
	bool encontrado = false;
    // Buscar en la lista normal
    NodoLista* actual = this->cabeza;
    while (actual != nullptr) {
        if (actual->proceso->getUsuario() == nombre) {
            actual->proceso->mostrar();
            encontrado = true;
        }
        actual = actual->siguiente;
    }
}
void Lista::encontrarUsuarioListaTiempoReal(string nombre){
	bool encontrado = false;
	// Buscar en la lista de tiempo real
    NodoLista* actual = this->cabeza;
    while (actual != nullptr) {
        if (actual->proceso->getUsuario() == nombre) {
            actual->proceso->mostrar();
            encontrado = true;
        }
        actual = actual->siguiente;
    }
}

void Lista::mostrarProcesoParaEliminar(Proceso* proceso){
	// Mostrar encabezados
    std::cout  << std::left << std::setw(10) << "PID" << std::setw(15) << "USUARIO" << std::setw(15) << "TIPO" << std::setw(15) << "ESTADO" << std::setw(10) << "PRIORIDAD" << std::endl;
	std::cout  << std::left << proceso->getPID() 
                  << std::setw(15) << proceso->getUsuario() 
                  << std::setw(15) << (proceso->esTiempoReal() ? "Tiempo Real" : "Normal") 
                  << std::setw(15) << (proceso->mostrar_proceso() ? "Ejecucion" : "Parado") 
                  << std::setw(10) << proceso->getPrioridad() 
                  << std::endl;
	proceso->mostrar();
}

void Lista::mostrarProcesoParaCambiar(Proceso* proceso){
        std::cout << std::left << std::setw(10) << "PID" << std::setw(15) << "USUARIO" << std::setw(15) << "TIPO" << std::setw(15) << "ESTADO" << std::setw(10) << "PRIORIDAD" << std::endl;
        std::cout << std::left << std::setw(10) << proceso->getPID() 
				  << std::setw(15) << proceso->getUsuario() 
                  << std::setw(15) << (proceso->esTiempoReal() ? "Tiempo Real" : "Normal") 
                  << std::setw(15) << (proceso->mostrar_proceso() ? "Ejecucion" : "Parado") 
                  << std::setw(10) << proceso->getPrioridad() 
                  << std::endl;
}