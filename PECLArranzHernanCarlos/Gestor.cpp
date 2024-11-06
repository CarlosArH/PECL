#include "Gestor.hpp"
#include <algorithm>

#include "Gestor.hpp"
#include <iostream>

Gestor::Gestor() {
    pidCounter = 0;   //contador de PIDs
    usuarioCounter = 1;    //Contador de usuarios del sistema
    int n = 600;
    arrayPIDs = new int[n];
    for (int i = 0; i < n; ++i) {
        arrayPIDs[i] = i + 300;
    }
    std::random_shuffle(arrayPIDs, arrayPIDs + n);	//generar una lista con numemros ordenados aleatoriamente del 300 al 900

    prioridadesNormales = new int[40]; // Para procesos normales
    prioridadesTiempoReal = new int[100]; // Para procesos en tiempo real

    // Generar prioridades para procesos normales (-19 a +19)
    for (int i = 0; i < 40; ++i) {
        prioridadesNormales[i] = i - 19; // Generar números entre -19 y +19
    }
    std::random_shuffle(prioridadesNormales, prioridadesNormales + 40);

    // Generar prioridades para procesos en tiempo real (0 a 99)
    for (int i = 0; i < 100; ++i) {
        prioridadesTiempoReal[i] = i; // Generar números entre 0 y 99
    }
    std::random_shuffle(prioridadesTiempoReal, prioridadesTiempoReal + 100);
	indexNormales = 0;
    indexTiempoReal = 0;
}

Gestor::~Gestor(){
    delete[] arrayPIDs;
    delete[] prioridadesNormales;
    delete[] prioridadesTiempoReal;
}

void Gestor::genera12Procesos() {
    int procesosEnPila = pila.getLongitud();
    if (procesosEnPila + 12 > 48) {
        std::cout << "No se pueden generar mas de 48 procesos en la pila.\n";
        return;
    }

    for (int i = pidCounter; i < pidCounter + 12; i++) {
        pila.generarProceso(usuarioCounter, arrayPIDs, i);
        ++usuarioCounter;
    }
    pidCounter = pidCounter + 12;
}


void Gestor::muestraProcesos(){
    pila.mostrarProcesos();
}


void Gestor::borraProcesosPila(){
	pila.vaciar();
}


void Gestor::encolarProcesos() {
    int indexNormales = 0;
    int indexTiempoReal = 0; 
    while (!pila.estaVacia()) {
        Proceso* proceso = pila.extraer();
        proceso->establecerPrioridad(prioridadesTiempoReal, prioridadesNormales, indexTiempoReal, indexNormales);
        indexNormales++;
        indexTiempoReal++;
        int indice = colas[0].indiceCola(proceso, colas); // Obtener el índice de la cola
        colas[indice].insertar(proceso); // Encolar el proceso en la cola correspondiente
    }
}


void Gestor::muestraProcesosGPUs0y1() {
	cout << "GPU 0:" << endl;
	colas[0].mostrar();
	cout << "GPU 1:" << endl;
	colas[1].mostrar();
}
 

void Gestor::muestraProcesosGPUs2y3() {
	std::cout << "GPU 2:" << std::endl;
	colas[2].mostrar();
	std::cout << "GPU 3:" << std::endl;
	colas[3].mostrar();
}


void Gestor::borraProcesosColas() {
    for (int i = 0; i < 4; i++) {
        while (!colas[i].estaVacia()) {
            colas[i].eliminar();
        }
    }
}

void Gestor::enlistarProcesos() {
    for (int i = 0; i < 4; i++) {
        while (!colas[i].estaVacia()) {
            Proceso* proceso = colas[i].eliminar();
            proceso->setEjecucion(true);
            if (i < 2) {
                listaNormal.insertar(proceso);
            } else {
                listaTiempoReal.insertar(proceso);
            }
        }
    }
}

void Gestor::muestraProcesosNormal() {
    cout << "Lista Normal:" << std::endl;
    listaNormal.mostrar();
}


void Gestor::muestraProcesosTiempoReal() {
    cout << "Lista Tiempo Real:" << std::endl;
    listaTiempoReal.mostrar();
}


void Gestor::buscarProcesos() {
    Proceso* menorPrioridadNormal = nullptr;
    Proceso* mayorPrioridadTiempoReal = nullptr;
	//listaNormal.buscarProcesosListaNormal(listaNormal, menorPrioridadNormal);
	listaNormal.buscarProcesosListaNormal(menorPrioridadNormal);
	listaTiempoReal.buscarProcesosListaTiempoReal(mayorPrioridadTiempoReal);
}


void Gestor::buscarProcesoPorNombreUsuario() {
    std::string nombreUsuario;
    std::cout << "Ingrese el nombre de usuario: ";
    std::cin >> nombreUsuario;
	listaNormal.encontrarUsuarioListaNormal(nombreUsuario);
	listaTiempoReal.encontrarUsuarioListaTiempoReal(nombreUsuario);

}


void Gestor::eliminarProcesoPorPID() {
    int pid;
    std::cout << "Ingrese el PID del proceso a eliminar: ";
    std::cin >> pid;

    // Buscar en la lista normal
    Proceso* proceso = listaNormal.buscarPorPID(pid);

    // Si no se encuentra, buscar en la lista de tiempo real
    if (proceso == nullptr) {
        proceso = listaTiempoReal.buscarPorPID(pid);
    }
	// Actualizar el estado de ejecución y apilar el proceso
	proceso->setEjecucion(false);
	pila.insertar(proceso);
	
    // Si se encontró el proceso, proceder a eliminarlo
    if (proceso != nullptr) {
        // Mostrar información del proceso a eliminar
        if (listaNormal.buscarPorPID(pid) != nullptr) {
            listaNormal.mostrarProcesoParaEliminar(proceso);
            listaNormal.eliminarPorPID(pid);
        } else {
            listaTiempoReal.mostrarProcesoParaEliminar(proceso);
            listaTiempoReal.eliminarPorPID(pid);
        }

    } else {
        std::cout << "No se encontró un proceso con el PID " << pid << std::endl;
    }
}


void Gestor::cambiarPrioridadProcesoPorPID() {
    int pid, nuevaPrioridad;
    std::cout << "Ingrese el PID del proceso al que desea cambiar la prioridad: ";
    std::cin >> pid;

    Proceso* proceso = listaNormal.buscarPorPID(pid);
	Lista lista = listaNormal;
    if (proceso == nullptr) {
        proceso = listaTiempoReal.buscarPorPID(pid);
		Lista lista = listaTiempoReal;
    }

    if (proceso != nullptr) {
        lista.mostrarProcesoParaCambiar(proceso);
		std::cout << "Ingrese la nueva prioridad para el proceso: ";
        std::cin >> nuevaPrioridad;
		// Cambiar la prioridad del proceso
        proceso->setPrioridad(nuevaPrioridad);
		//Mostrar proceso despues de cambiar la prioridad
		lista.mostrarProcesoParaCambiar(proceso);
    } else {
        std::cout << "No se encontró un proceso con el PID " << pid << std::endl;
    }
}

void Gestor::reiniciar() {
    borraProcesosPila();
    borraProcesosColas();
    listaNormal.~Lista();
    listaTiempoReal.~Lista();
}

// Métodos adicionales para adaptarse al main
int Gestor::ProcesosEnPila() {
    return pila.getLongitud();
}

int Gestor::ProcesosEnGPU0()  {
    return colas[0].getLongitud();
}

int Gestor::ProcesosEnGPU1() {
    return colas[1].getLongitud();
}

int Gestor::ProcesosEnGPU2()  {
    return colas[2].getLongitud();
}

int Gestor::ProcesosEnGPU3()  {
    return colas[3].getLongitud();
}

int Gestor::ProcesosEnListaNormal()  {
    return listaNormal.getLongitud();
}

int Gestor::ProcesosEnListaTiempoReal()  {
    return listaTiempoReal.getLongitud();
}

int Gestor::ProcesosEnArbol()  {
    // Implementar si se añade la funcionalidad del árbol
    return 0;
}