#include <omp.h>
#include "calculator.h"

class WithoutReduction : public calculator {
public:
    virtual double calcularPI(int pasos)
    {
        double pi, sum = 0.0;
        double step = 1.0 / (double)pasos;

        #pragma omp parallel for
        for (int i = 0; i < pasos; i++)
        {
            double x = (i + 0.5) * step;
            double y = 4.0 / (1.0 + x * x);
            #pragma omp critical
            sum = sum + y;
        }
        return step * sum;
    }
};