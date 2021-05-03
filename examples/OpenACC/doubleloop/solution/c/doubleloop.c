#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#ifdef _OPENACC
#include <openacc.h>
#endif

/* Convert 2D index layout to unrolled 1D layout
 *
 * \param[in] i      Row index
 * \param[in] j      Column index
 * \param[in] width  The width of the area
 *
 * \returns An index in the unrolled 1D array.
 */
int getIndex(const int i, const int j, const int width)
{
    return i*width + j;
}

void init(double * arr, int nx, int ny)
{
    int i, j;
    for (i = 0; i < nx + 2; i++) 
      for (j = 0; j < ny + 2; j++) {
	int index = getIndex(i,j,(ny+2));
	arr[index] = 0e0;
      }

    for (i = 0; i < nx + 2; i++) {
      arr[i*(ny+2)+ny+1] = 1e0;	
    }
    
    for (i = 0; i < ny+2; i++) {
      arr[(nx+1)*(ny+2)+i] = 1e0;
    }
}


int main(int argc, char **argv)
{
    double eps;

    double * u, * unew;
    const double factor = 0.25;
    const int niter = 2;
    double mlups = 0e0;
    int nx = 1022, ny = 1022;
    clock_t t_start, t_end;
    double dt;
    double sum;
    int i, j;
    int iter;
    const int numElements = (nx+2)*(ny+2);
    u = (double*)calloc(numElements, sizeof(double));
    unew = (double*)calloc(numElements, sizeof(double));

    init(u, nx, ny);
    init(unew, nx, ny);

    t_start = clock();

    for (iter = 0; iter < niter; iter++) {
#pragma acc parallel loop copyin(u[0:numElements]) copyout(unew[0:numElements])
        for (i = 1; i < nx + 1; i++)
#pragma acc loop	  
            for (j = 1; j < ny + 1; j++) {
	      const int index = getIndex(i, j, ny+2);
	      double uim1j = u[getIndex(i-1, j, ny+2)];
	      double uijm1 = u[getIndex(i, j-1, ny+2)];
	      double uip1j = u[getIndex(i+1, j, ny+2)];
	      double uijp1 = u[getIndex(i, j+1, ny+2)];
	      
	      // Explicit scheme
	      unew[index] = factor * (uim1j + uip1j + uijm1 + uijp1);
        }

#pragma acc parallel loop copyin(unew[0:numElements]) copyout(u[0:numElements])
        for (i = 1; i < nx + 1; i++)
#pragma acc loop
            for (j = 1; j < ny + 1; j++) {
	      const int index = getIndex(i, j, ny+2);
	      double uim1j = unew[getIndex(i-1, j, ny+2)];
	      double uijm1 = unew[getIndex(i, j-1, ny+2)];
	      double uip1j = unew[getIndex(i+1, j, ny+2)];
	      double uijp1 = unew[getIndex(i, j+1, ny+2)];
	     	      
	      u[index] = factor * (uim1j + uip1j + uijm1 + uijp1);
            }
    }

    /* Compute a reference sum, do not parallelize this! */
    sum = 0.0;
    for (i = 1; i < nx + 1; i++)
        for (j = 1; j < ny + 1; j++)
	  sum += u[i*(ny+2)+j];

    free(u);
    free(unew);

    mlups = niter * nx * ny * 1.0e-6;
    t_end = clock();
    dt = ((double)(t_end-t_start)) / CLOCKS_PER_SEC;
    printf("Stencil: Time =%18.16f sec, MLups/s=%18.16f, sum=%18.16f\n",dt, (double) mlups/dt, sum);

    return 0;
}
