#include <omp.h>

double calcularPI(int pasos)
{
    int n = omp_get_max_threads(); //Retorna la cantidad de threads del equipo
    int *inicio = new int[n];
    double *sumParcial = new double[n];
    double step = 1.0 / (double)pasos,
           sum = 0.0,
           pi;

    for (int i = 0; i < n; i++)
    {
        inicio[i] = (pasos / n) * i;
        sumParcial[i] = 0.0;
    }

    #pragma omp parallel
    for (int i = 0; i < (pasos / n); i++)
    {
        int id = omp_get_thread_num();
        double x = ((double)(inicio[id] + i) + 0.5) * step;
        sumParcial[id] = sumParcial[id] + 4.0 / (1.0 + (x * x));
    }

    for (int i = 0; i < n; i++)
        sum = sum + sumParcial[i];
    return step * sum;
}
