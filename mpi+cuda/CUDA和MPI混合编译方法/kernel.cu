
#include "cuda.cuh"

__global__ void matadd_kernel(float *matA, float *matB, float *matC, int nx, int ny, int nz)
{
   int ix = blockDim.x * blockIdx.x + threadIdx.x;
   int iy = blockDim.y * blockIdx.y + threadIdx.y;

   for (int iz = 0; iz < nz; iz ++)
   {
     if (ix < nx && iy < ny)
        matC[iz * ny * nx + iy * nx + ix] = matA[iz * ny * nx + iy * nx + ix] + matB[iz * ny * nx + iy * nx + ix];
   }
}

 void GPU_add(float *d_loc_matA,float * d_loc_matB,float * d_loc_matC,int nx,int ny,int loc_nz,dim3 dimBlock,dim3 dimGrid)
 {
	   matadd_kernel<<<dimGrid, dimBlock>>>(d_loc_matA, d_loc_matB, d_loc_matC, nx, ny, loc_nz);
 }


