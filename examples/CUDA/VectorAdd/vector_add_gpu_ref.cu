#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

__global__ void vecAdd(int numElements, const float* a, const float* b, float* c)
{
    int i = threadIdx.x + blockIdx.x*blockDim.x;
    if (i < numElements)
    {
        c[i] = a[i] + b[i];
    }
}

int main()
{
    int numElements = 10000;

    float* a = (float*)calloc(numElements, sizeof(float));
    float* b = (float*)calloc(numElements, sizeof(float));
    float* c = (float*)calloc(numElements, sizeof(float));

    srand(1214134);
    for (int i = 0; i < numElements; i++)
    {
        a[i] = float(rand())/float(RAND_MAX + 1.0);
        b[i] = float(rand())/float(RAND_MAX + 1.0);
    }

    float* d_a;
    float* d_b;
    float* d_c;
    
    cudaMalloc((void**)&d_a, numElements*sizeof(float));
    cudaMalloc((void**)&d_b, numElements*sizeof(float));
    cudaMalloc((void**)&d_c, numElements*sizeof(float));

    cudaMemcpy(d_a, a, numElements*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, numElements*sizeof(float), cudaMemcpyHostToDevice);

    vecAdd<<<numElements/256 + 1, 256>>>(numElements, d_a, d_b, d_c);

    cudaMemcpy(c, d_c, numElements*sizeof(float), cudaMemcpyDeviceToHost);

    for (int i = 0; i < std::min(10, numElements); i++)
    {
        printf("%f + %f = %f\n", a[i], b[i], c[i]);
    }
    printf("...\n");
    
    return 0;
}

