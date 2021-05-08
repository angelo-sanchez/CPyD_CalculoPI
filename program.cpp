#include <iostream>
#include <ctime>

// Dejar sólo una de las siguientes descomentadas, dependiendo de qué implementacion quiero usar.

// Implementación usando sólo la directiva omp parallel.
// #include "only-omp-parallel.h"
// Implementación usando omp for sin usar reduction
// #include "omp-for-without-reduction.h"
// Implementación usando omp for y la clausula reduction.
#include "omp-for-reduction.h"

using namespace std;
int main()
{
    int pasos = 100000000;
    int repeticiones = 10;
    long *tiempos = new long[repeticiones];
    clock_t inicio, fin;
    double pi;
    for (int i = 0; i < repeticiones; i++)
    {
        inicio = clock();
        // El método calcularPI está implementado de manera diferente en cada uno de los archivos importados.
        pi = calcularPI(pasos);
        fin = clock();
        cout << "PI aproximado: " << pi
             << " | Tiempo de cálculo: " << ((double)fin - (double)inicio) / (double)CLOCKS_PER_SEC << " segundos."
             << endl << endl;
        tiempos[i] = fin - inicio;
    }
    double sum = 0.0;
    for (int i = 0; i < repeticiones; i++)
    {
        sum += (double)tiempos[i];
    }
    cout << "Tiempo promedio de ejecución: " << (sum / (double)repeticiones) / (double)CLOCKS_PER_SEC << " segundos." << endl;
    return 0;
}