/* 2D heat equation

   Copyright (C) 2014  CSC - IT Center for Science Ltd.

*/

//#include <algorithm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pngwriter.h"

// function to swap the two numbers
void swap(float *x, float *y)
{
  float t;
  t   = *x;
  *x   = *y;
  *y   =  t;
}

// Utility routine for allocating a two dimensional array
float **malloc_2d(int nx, int ny)
{
  float **array;
  int i;

  array = (float **) malloc(nx * sizeof(float *));
  array[0] = (float *) malloc(nx * ny * sizeof(float));

  for (i = 1; i < nx; i++) {
    array[i] = array[0] + i * ny;
  }

  return array;
}

// Utility routine for deallocating a two dimensional array
void free_2d(float **array)
{
  free(array[0]);
  free(array);
}

int main()
{
    const int nx = 200;   // Width of the area
    const int ny = 200;   // Height of the area

    const float a = 0.5;     // Diffusion constant

    const float dx = 0.01;   // Horizontal grid spacing 
    const float dy = 0.01;   // Vertical grid spacing

    const float dx2 = dx*dx;
    const float dy2 = dy*dy;

    const float dt = dx2 * dy2 / (2.0 * a * (dx2 + dy2)); // Largest stable time step
    const int numSteps = 500;                             // Number of time steps
    const int outputEvery = 100;                          // How frequently to write output image

    int numElements = nx*ny;

    // Allocate two sets of data for current and next timesteps
    float** Un   = malloc_2d(nx,ny);
    float** Unp1 = malloc_2d(nx,ny);

    // Initializing the data with a pattern of disk of radius of 1/6 of the width
    float radius2 = (nx/6.0) * (nx/6.0);
    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {
            // Distance of point i, j from the origin
            float ds2 = (i - nx/2) * (i - nx/2) + (j - ny/2)*(j - ny/2);
            if (ds2 < radius2)
            {
                Un[i][j] = 65.0;
            }
            else
            {
                Un[i][j] = 5.0;
            }
        }
    }

    // Fill in the data on the next step to ensure that the boundaries are identical.
    memcpy(Unp1[0], Un[0], numElements*sizeof(float));

    // Main loop
    for (int n = 0; n < numSteps; n++)
    {
        // Going through the entire area
      //#pragma acc parallel loop copyin(Un[0:nx][0:ny]) copyout(Unp1[0:nx][0:ny]) 
#pragma acc parallel loop collapse(2) copyin(Un[0:nx][0:ny]) copyout(Unp1[0:nx][0:ny])
        for (int i = 1; i < nx-1; i++)
        {
            for (int j = 1; j < ny-1; j++)
            {
 	       float uij = Un[i][j];
	       // Explicit scheme
	       Unp1[i][j] = uij + a * dt * ( (Un[i-1][j] - 2.0*uij + Un[i+1][j])/dx2 
                                           + (Un[i][j-1] - 2.0*uij + Un[i][j+1])/dy2 );
            }
        }
        // Write the output if needed
        if (n % outputEvery == 0)
        {
            char filename[64];
            sprintf(filename, "heat_%04d.png", n);
            save_png(Un[0], nx, ny, filename, 'c');
        }
        // Swapping the pointers for the next timestep
	memcpy(Un[0], Unp1[0], numElements*sizeof(float));
    }

    // Release the memory
    free_2d(Un);
    free_2d(Unp1);
    
    return 0;
}
