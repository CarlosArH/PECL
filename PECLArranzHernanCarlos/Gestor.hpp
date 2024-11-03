#ifndef GESTOR_HPP
#define GESTOR_HPP

#include <ctime>     // Para time()
#include <algorithm> // Para std::random_shuffle
#include "Pila.hpp"  // Asegúrate de que los archivos están en la ruta correcta
#include "Cola.hpp"
#include "Lista.hpp"

// Eliminamos "using namespace std" aquí para evitar problemas de nombres en los encabezados

class Gestor {
private:
    Pila pila;
    Cola colas[4];  // Define el array de colas sin inicialización aquí
    Lista listaNormal;
    Lista listaTiempoReal;
    int pidCounter;
    int usuarioCounter;
    int* arrayPIDs;
    int* prioridadesNormales;
    int* prioridadesTiempoReal;
	int indexNormales;
    int indexTiempoReal;

public:
    Gestor();
    ~Gestor();
    void genera12Procesos();
    void muestraProcesos();
    void borraProcesosPila();
    void encolarProcesos();
    void muestraProcesosGPUs0y1();
    void muestraProcesosGPUs2y3();
    void borraProcesosColas();
    void enlistarProcesos();
    void muestraProcesosNormal();
    void muestraProcesosTiempoReal();
    void buscarProcesos();
    void buscarProcesoPorNombreUsuario();
    void eliminarProcesoPorPID();
    void cambiarPrioridadProcesoPorPID();
    void reiniciar();

    // Métodos adicionales para adaptarse al main
    int ProcesosEnPila();
    int ProcesosEnGPU0();
    int ProcesosEnGPU1();
    int ProcesosEnGPU2();
    int ProcesosEnGPU3();
    int ProcesosEnListaNormal();
    int ProcesosEnListaTiempoReal();
    int ProcesosEnArbol();
};

#endif // GESTOR_HPP
