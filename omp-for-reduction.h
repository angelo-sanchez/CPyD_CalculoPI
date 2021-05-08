#include <omp.h>
#include "calculator.h"

class ForReduction : public calculator {
public:
    virtual double calcularPI(int pasos)
    {
        int i;
        double x, pi, sum = 0.0;
        double step = 1.0 / (double)pasos;

        #pragma omp parallel for reduction(+:sum)
        for (i = 0; i < pasos; i++)
        {
            x = (i + 0.5) * step;
            sum = sum + 4.0 / (1.0 + x * x);
        }
        return step * sum;
    }
};