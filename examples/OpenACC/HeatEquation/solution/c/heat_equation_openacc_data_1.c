#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Convert 2D index layout to unrolled 1D layout
 *
 * \param[in] i      Row index
 * \param[in] j      Column index
 * \param[in] width  The width of the area
 * 
 * \returns An index in the unrolled 1D array.
 */
#pragma acc routine seq
int getIndex(const int i, const int j, const int width)
{
    return i*width + j;
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
    float* Un   = (float*)calloc(numElements, sizeof(float));
    float* Unp1 = (float*)calloc(numElements, sizeof(float));

    // Initializing the data with a pattern of disk of radius of 1/6 of the width
    float radius2 = (nx/6.0) * (nx/6.0);
    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {
            int index = getIndex(i, j, nx);
            // Distance of point i, j from the origin
            float ds2 = (i - nx/2) * (i - nx/2) + (j - ny/2)*(j - ny/2);
            if (ds2 < radius2)
            {
                Un[index] = 65.0;
            }
            else
            {
                Un[index] = 5.0;
            }
        }
    }

    // Fill in the data on the next step to ensure that the boundaries are identical.
    memcpy(Unp1, Un, numElements*sizeof(float));

    // Main loop
#pragma acc data copyin(Un) create(Unp1)
{    
    for (int n = 0; n < numSteps; n++)
    {
        // Going through the entire area
	
#pragma acc parallel loop collapse(2) present(Un,Unp1)
        for (int i = 1; i < nx-1; i++)
        {
            for (int j = 1; j < ny-1; j++)
            {
                const int index = getIndex(i, j, nx);
                float uij = Un[index];
                float uim1j = Un[getIndex(i-1, j, nx)];
                float uijm1 = Un[getIndex(i, j-1, nx)];
                float uip1j = Un[getIndex(i+1, j, nx)];
                float uijp1 = Un[getIndex(i, j+1, nx)];

                // Explicit scheme
                Unp1[index] = uij + a * dt * ( (uim1j - 2.0*uij + uip1j)/dx2 + (uijm1 - 2.0*uij + uijp1)/dy2 );
            }
        }
        // Write the output if needed
        if (n % outputEvery == 0)
        {
            float maxtemp = -1.e-5;
#pragma acc update host(Un)	    
            for (int i = 0; i < nx; i++) {
              for (int j = 0; j < ny; j++) {
		const int index = getIndex(i,j,nx);
                if (maxtemp < Un[index]) {
                  maxtemp = Un[index];
                }
              }
            }
            printf("Maximum temperture is %f at %d steps \n", maxtemp, n);
        }
        // Copy the pointers for the next timestep
        //memcpy(Un, Unp1, numElements*sizeof(float));
#pragma acc parallel loop collapse(2)
        for (int i = 1; i < nx; i++) {
          for (int j = 1; j < ny; j++) {
	    int index = getIndex(i,j,nx);
            Un[index] = Unp1[index];
	  }
        }
    }
 }
    // Release the memory
    free(Un);
    free(Unp1);
    
    return 0;
}
