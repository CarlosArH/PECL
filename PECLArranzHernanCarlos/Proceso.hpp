#ifndef PROCESO_HPP
#define PROCESO_HPP

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class Proceso {
private:
    int pid;
    string usuario;
    bool estado; 
    int prioridad;
    bool tiempoReal; 
public:
    Proceso(int pid, string usuario, bool tiempoReal);
    ~Proceso();
    int getPID();
    string getUsuario();
    bool mostrar_proceso();
    int getPrioridad();
    bool esTiempoReal();
    void setEjecucion(bool estado);
	void setPrioridad(int prioridad);
    void establecerPrioridad(int* prioridadesTiempoReal, int* prioridadesNormales, int indexTR, int indexN);
    void mostrar();
};
#endif // PROCESO_HPP