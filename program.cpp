#include <iostream>
#include <ctime>
#include <vector>

#include "calculator.h"
#include "only-omp-parallel.h"
#include "omp-for-without-reduction.h"
#include "omp-for-reduction.h"

using namespace std;

void informeUso(char* program){
    cerr << "Programa para calcular una aproximacion del numero PI y obtener estadisticas de rendimiento" << endl
    << endl
    << "Uso: " << string(program) << " <implementacion> [steps]" << endl
    << "    donde <implementacion> puede ser uno de los siguientes:" << endl
    << "    parallel-only            Implementacion usando solo omp parallel" << endl
    << "    without-reduction        Implementacion sin usar la clausula reduction" << endl
    << "    for-reduction            Implementacion usando omp for reduction" << endl
    << endl
    << "    steps                    Cantidad de pasos que se haran para aproximar a PI, si no esta presente su valor sera de 100000" << endl;
}

int main(int arg_count, char** arg_vector)
{
    if(arg_count == 1){
        informeUso(arg_vector[0]);
        return -1;
    }
    vector<string> args(arg_vector, arg_vector + arg_count);
    calculator *c;
    
    if(args[1] == "parallel-only")
        c = new OnlyParallel();
    else if (args[1] == "without-reduction")
        c = new WithoutReduction();
    else if(args[1] == "for-reduction")
        c = new ForReduction();
    else{
        informeUso(arg_vector[0]);
        return -1;
    }

    int pasos = 100000;
    if(args.size() > 2){
        pasos = stoi(args[2]);
    }

    int repeticiones = 10;
    long *tiempos = new long[repeticiones];
    clock_t inicio, fin;
    double pi;
    for (int i = 0; i < repeticiones; i++)
    {
        inicio = clock();
        // El método calcularPI está implementado de manera diferente en cada uno de los archivos importados.
        
        pi = c->calcularPI(pasos);
        fin = clock();
        cout << "PI aproximado: " << pi
             << " | Tiempo de calculo: " << ((double)fin - (double)inicio) / (double)CLOCKS_PER_SEC << " segundos."
             << endl << endl;
        tiempos[i] = fin - inicio;
    }
    double sum = 0.0;
    for (int i = 0; i < repeticiones; i++)
    {
        sum += (double)tiempos[i];
    }
    cout << "Tiempo promedio de ejecucion: " << (sum / (double)repeticiones) / (double)CLOCKS_PER_SEC << " segundos." << endl;
    return 0;
}