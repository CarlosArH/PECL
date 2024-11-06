#include "Proceso.hpp"
#include <algorithm>

Proceso::Proceso(int pid, string usuario, bool tiempoReal) {
    this->pid = pid;
    this->usuario = usuario;
    this->estado = false; // Inicialmente parado
    this->tiempoReal = tiempoReal; // 0 = normal, 1 = tiempo real
    this->prioridad = prioridad;
}

Proceso::~Proceso() {
    // Destructor
}

int Proceso::getPID(){
    return pid;
}

string Proceso::getUsuario() {
    return usuario;
}

bool Proceso::mostrar_proceso() {
    return estado;
}

int Proceso::getPrioridad() {
    return prioridad;
}

bool Proceso::esTiempoReal() {
    return tiempoReal;
}

void Proceso::setEjecucion(bool estado) {
    this->estado = estado;
}

void Proceso::setPrioridad(int prioridad) {
    this->prioridad = prioridad;
}

void Proceso::establecerPrioridad(int* prioridadesTiempoReal, int* prioridadesNormales, int indexTR, int indexN) {
	setEjecucion(false); // Establecer el estado en parado
	// Asignar prioridad según el tipo de proceso
	if (esTiempoReal()) {
		setPrioridad(prioridadesTiempoReal[indexTR++]);
	} else {
		setPrioridad(120 + prioridadesNormales[indexN++]); // Aplicar cálculo para procesos normales
	}
}

void Proceso::mostrar(){
    cout << "El proceso cuyo PID es " << pid  << " es de tipo en " << (tiempoReal ? "Tiempo Real" : "Normal") 
		<< ", su estado es " << (estado ? "ejecucion" : "parado") << " y su prioridad es: " << prioridad << endl;
}