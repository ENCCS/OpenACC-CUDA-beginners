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


void init(float* arr, int nx, int ny)
{
    int i, j;
    /* TODO: Implement data initialization with OpenACC on device */    
    for (i = 0; i < nx + 2; i++) 
      for (j = 0; j < ny + 2; j++) {
	int index = getIndex(i,j,(ny+2));
	arr[index] = 0e0;
      }

    /* TODO: Implement data initialization with OpenACC on device */
    for (i = 0; i < nx + 2; i++) {
      arr[i*(ny+2)+ny+1] = 1e0;	
    }

    /* TODO: Implement data initialization with OpenACC on device */
    for (i = 0; i < ny+2; i++) {
      arr[(nx+1)*(ny+2)+i] = 1e0;
    }
}

void update(float *newarr, float *oldarr, float *norm, int nx, int ny)
{
    int i, j;
    const float factor = 0.25;
    float lnorm;

    if (norm != NULL) {
        lnorm = 0;
        /* TODO: Implement computation with OpenACC on device */
        for (i = 1; i < nx + 1; i++) {
	   for (j = 1; j < ny + 1; j++) {
  	      const int index = getIndex(i, j, ny+2);
	      float uim1j = oldarr[getIndex(i-1, j, ny+2)];
	      float uijm1 = oldarr[getIndex(i, j-1, ny+2)];
	      float uip1j = oldarr[getIndex(i+1, j, ny+2)];
	      float uijp1 = oldarr[getIndex(i, j+1, ny+2)];
	      
	      // Explicit scheme
	      newarr[index] = factor * (uim1j + uip1j + uijm1 + uijp1);
	      lnorm = fmaxf(lnorm, fabsf(newarr[index] - oldarr[index]));
            }
        }
        *norm = lnorm;
    } else {
        /* TODO: Implement computation with OpenACC on device */
        for (i = 1; i < nx + 1; i++) {
            for (j = 1; j < ny + 1; j++) {
  	      const int index = getIndex(i, j, ny+2);
	      float uim1j = oldarr[getIndex(i-1, j, ny+2)];
	      float uijm1 = oldarr[getIndex(i, j-1, ny+2)];
	      float uip1j = oldarr[getIndex(i+1, j, ny+2)];
	      float uijp1 = oldarr[getIndex(i, j+1, ny+2)];
	      newarr[index] = factor * (uim1j + uip1j + uijm1 + uijp1);
	    }
        }
    }
}

void usage(pname)
{
    printf("Usage: %s [nx] [ny]", pname);
}


int main(int argc, char **argv)
{
    float eps;

    float *u, * unew;
    float norm = 0e0, mlups = 0e0;
    int maxiter, nx, ny, iter, ndef = 2400;
    clock_t t_start, t_end;
    float dt;

    eps = 0.5e-3;
    maxiter = (int)(1e0 / eps);

    switch (argc) {
    case 1:
        nx = ndef;
        ny = nx;
        break;
    case 2:
        nx = atoi(argv[1]);
        ny = nx;
        break;
    case 3:
        nx = atoi(argv[1]);
        ny = atoi(argv[2]);
        break;
    default:
        usage(argv[0]);
        return -1;
    }

    printf("Stencil: nx,ny,maxiter,eps=%d %d %d %18.16f\n", nx, ny, maxiter, eps);

    u = (float*)calloc((nx+2)*(ny+2), sizeof(float));
    unew = (float*)calloc((nx+2)*(ny+2), sizeof(float));

    /* TODO: Initialize data region on device */

    init(u, nx, ny);
    init(unew, nx, ny);

    t_start = clock();

    norm = eps + 1;
    iter = 0;
    while (iter <= maxiter && norm >= eps) {
        update(unew, u, NULL, nx, ny);
        update(u, unew, &norm, nx, ny);
        iter = iter + 2;
        if (iter % 100 == 0 || norm < eps) {
            printf(": norm, eps= %18.16f %18.16f\n", norm, eps);
        }
    }


    free(u);
    free(unew);

    mlups = 1.0e-6 * iter * nx * ny;
    t_end = clock();
    dt = ((float)(t_end - t_start)) / CLOCKS_PER_SEC;
    printf("'Stencil: norm =%18.16f with iter = %d\n", norm, iter);
    printf("'Stencil: Time =%18.16f sec, MLups/s=%18.16f\n", dt, (float) mlups / dt);

    return 0;
}
