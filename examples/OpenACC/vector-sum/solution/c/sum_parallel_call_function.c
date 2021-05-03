#include <stdio.h>
#ifdef _OPENACC
#include <openacc.h>
#endif

#define NX 102400

// return a*b;
#pragma acc routine seq
double add(double a, double b)
{
    return a + b;
}

int main(void)
{
    double vecA[NX], vecB[NX], vecC[NX];
    double sum;
    int i;

    /* Initialization of the vectors */
    for (i = 0; i < NX; i++) {
        vecA[i] = 1.0 / ((double) (NX - i));
        vecB[i] = vecA[i] * vecA[i];
    }

#pragma acc parallel
    {
#pragma acc loop
        for (i = 0; i < NX; i++) {
            vecC[i] = add(vecA[i], vecB[i]);
        }
    }

    sum = 0.0;
    /* Compute the check value */
    for (i = 0; i < NX; i++) {
        sum += vecC[i];
    }
    printf("Reduction sum: %18.16f\n", sum);

    return 0;
}
