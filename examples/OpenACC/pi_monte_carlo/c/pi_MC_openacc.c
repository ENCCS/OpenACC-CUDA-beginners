#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include <curand.h>


float cpu_pi(int n)
{
    int inside, i;
    float *x, *y;
    
    x = (float *)malloc(n * sizeof(float));
    y = (float *)malloc(n * sizeof(float));

    for (i = 0; i < n; i++) {
        x[i] = (float)rand() / (float)RAND_MAX;
        y[i] = (float)rand() / (float)RAND_MAX;
    }

    inside = 0;
    for (i = 0; i < n; i++) {
        if (x[i]*x[i] + y[i]*y[i] < 1.0) {
            inside++;
        }
    }

    free(x);
    free(y);

    return 4.0 * (float)inside / (float)n;
}


float gpu_pi(int n)
{
    curandGenerator_t g;
    int inside, istat, i;
    unsigned int *a;
    float *x, *y, pi;
    
    pi = 0;
    
    x = (float *)malloc(n * sizeof(float));
    y = (float *)malloc(n * sizeof(float));

    inside = 0;

    /* 
     * TODO: Add here the initialization of the curand random number generator,
     *       create appropriate data environments, generate arrays x and y of
     *       uniformly distributed random number as instructed in the README.md,
     *       compute the loop using openacc and release the random number generator.
     */    
    for (i = 0; i < n; i++) {
        if (x[i]*x[i] + y[i]*y[i] < 1.0) {
            inside++;
        }
    }        
    free(x);
    free(y);

    istat = curandDestroyGenerator(g);
    if (istat != CURAND_STATUS_SUCCESS) {
        fprintf(stderr, "Error in curandDestroyGenerator: %d\n", istat);
    }

    pi = 4.0 * (float)inside / (float)n;

    return pi;
}


int main(int argc, char *argv[])
{
    int nsamples;
    const int ndef = 20000;
    float *x, *y, pi;
    int i, inside, outside;
    int istat;

    if (argc < 2) {
	nsamples = ndef;
    } else {
        nsamples = atoi(argv[1]);
    }

    printf("Pi equals to %9.6f\n", cpu_pi(nsamples));
    printf("Pi equals to %9.6f\n", gpu_pi(nsamples));
    
    return 0;
}
