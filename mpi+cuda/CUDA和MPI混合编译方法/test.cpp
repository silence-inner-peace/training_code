#include "cuda.cuh"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "mpi.h"
#include <iostream>
using namespace std;
#define BLOCK_DIMX 16
#define BLOCK_DIMZ 16


void CPUtest(int settimes, int row, int col, float **GA, float **GB)
{
	for (int i = 0; i < settimes; i++)
	{
		for(int i=0;i<row+1;i++){
			for(int j=0;j<col+1;j++){
				GA[i][j]=GB[i][j];
			}
		}
	}
}


int InitCUDA(int myid)
{
  int devCount = 0;
  int dev = 0;

  cudaGetDeviceCount(&devCount);
  if (devCount == 0) 
  {
    fprintf(stderr, "There is no device supporting CUDA.\n");
    return false;
  }

  for (dev = 0; dev < devCount; ++dev)
  {
    cudaDeviceProp prop;

    if (cudaGetDeviceProperties(&prop, dev) == cudaSuccess)
    {

       if (prop.major >= 1) break;
    }
	     
  }

  if (dev == devCount)
  {
     fprintf(stderr, "There is no device supporting CUDA.\n");
     return false;
  }

  cudaSetDevice(myid);
  cudaDeviceProp prop1;
  cudaGetDeviceProperties(&prop1,myid);
  fprintf(stdout, "multiProcessorCount %d : %d\n", myid, prop1.multiProcessorCount);
  return true;
}


void matadd(float *matA, float *matB, float *matC, int nx, int ny, int nz, int myid, int size)
{
  int ista, iend;
  //给主进程分配最后一个分块
  if (myid != 0) 
  {
    ista = (myid - 1) * ( nz / size); 
    iend = ista + nz / size - 1;
  } 
  else 
  {
    ista = (size - 1) * (nz / size);
    iend = nz - 1;
  }

  int loc_nz = iend - ista + 1;
  float *loc_matA = (float *) malloc( loc_nz * ny * nx * sizeof(float));
  float *loc_matB = (float *) malloc( loc_nz * ny * nx * sizeof(float));
  float *loc_matC = (float *) malloc( loc_nz * ny * nx * sizeof(float));

  MPI_Status status;
  int *count=new int[size];//记录每个进程处理的个数多少

  if (myid != 0)
  {
    MPI_Send(&loc_nz, 1, MPI_INT, 0, myid, MPI_COMM_WORLD);
  } 
  else 
  {
    count[0] = loc_nz;
    for (int i = 1; i < size; i ++) 
    {
      MPI_Recv(&count[i], 1, MPI_INT, i, i, MPI_COMM_WORLD, &status);
    } 
  }

  if (myid == 0)
  {
    for (int ix = 0; ix < count[0] * ny * nx; ix ++)
    {
     loc_matA[count[0] * ny * nx - 1 - ix] = matA[nz * ny * nx - 1 - ix];
     loc_matB[count[0] * ny * nx - 1 - ix] = matB[nz * ny * nx - 1 - ix];
    }
    for (int isz = 1; isz < size; isz ++) 
    {
      int idx = 0;
      if (isz == 1) 
      {
        idx = 0;
      }
      else 
      {
        idx += count[isz - 1];
      }
      MPI_Send(matA + idx * ny * nz, count[isz] * ny * nx, MPI_FLOAT, isz, isz, MPI_COMM_WORLD);
      MPI_Send(matB + idx * ny * nz, count[isz] * ny * nx, MPI_FLOAT, isz, isz, MPI_COMM_WORLD);
    }
  } 
  else 
  {
    MPI_Recv(loc_matA, loc_nz * ny * nx, MPI_FLOAT, 0, myid, MPI_COMM_WORLD, &status);
    MPI_Recv(loc_matB, loc_nz * ny * nx, MPI_FLOAT, 0, myid, MPI_COMM_WORLD, &status);
  }

  float *d_loc_matA;
  cudaMalloc((void **) &d_loc_matA, loc_nz * ny * nx * sizeof(float));
  cudaMemcpy(d_loc_matA, loc_matA, loc_nz * ny * nx * sizeof(float), cudaMemcpyHostToDevice);

  float *d_loc_matB;
  cudaMalloc((void **) &d_loc_matB, loc_nz * ny * nx * sizeof(float));
  cudaMemcpy(d_loc_matB, loc_matB, loc_nz * ny * nx * sizeof(float), cudaMemcpyHostToDevice);

  float *d_loc_matC;
  cudaMalloc((void **) &d_loc_matC, loc_nz * ny * nx * sizeof(float));

  dim3 dimBlock(BLOCK_DIMX, BLOCK_DIMZ);
  dim3 dimGrid(nx / BLOCK_DIMX, ny / BLOCK_DIMZ);

  GPU_add(d_loc_matA, d_loc_matB, d_loc_matC, nx, ny, loc_nz,dimBlock,dimGrid);

  cudaMemcpy(loc_matC, d_loc_matC, loc_nz * ny * nx * sizeof(float), cudaMemcpyDeviceToHost);

  if (myid !=0 )
  {
    MPI_Send(loc_matC, loc_nz * ny * nx, MPI_FLOAT, 0, myid, MPI_COMM_WORLD);
  } 
  else 
  {
    for (int ix = 0; ix < count[0] * ny * nx; ix ++)
      matC[nz * ny * nx - 1 - ix] = loc_matC[loc_nz * ny * nx - 1 - ix];
    for (int isz = 1; isz < size; isz ++)
    {
      int idx = 0;
      if (isz == 1) 
        idx = 0;
      else 
        idx += count[isz - 1];
      MPI_Recv(matC + idx * ny * nz, count[isz] * ny * nx, MPI_FLOAT, isz, isz, MPI_COMM_WORLD, &status);
    }
  }

  cudaFree(d_loc_matA);
  cudaFree(d_loc_matB);
  cudaFree(d_loc_matC);

  free(loc_matA);
  free(loc_matB);
  free(loc_matC);
  return;
}

////////////////////////////////////////////////////////////////////////////////////////////
// Main program
////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int InitCUDA(int myid);
void matadd(float *matA, float *matB, float *matC, int nx, int ny, int nz, int myid, int size);
int main(int argc, char *argv[])
{
  int myid, numprocs;
  int namelen;
  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);

  InitCUDA(myid);

  int nx = 96, ny = 96, nz = 500;
  float *a = (float *)malloc(nx * ny * nz * sizeof(float));
  float *b = (float *)malloc(nx * ny * nz * sizeof(float));
  float *c = (float *)malloc(nx * ny * nz * sizeof(float));

  for (int iz = 0; iz < nz; iz ++)
    for (int iy = 0; iy < ny; iy ++)
      for (int ix = 0; ix < nx; ix++)
      {
        a[iz * ny * nx + iy * nx + ix] = 1.0f;
        b[iz * ny * nx + iy * nx + ix] = 2.0f;
        c[iz * ny * nx + iy * nx + ix] = 0.0f;
      }

  clock_t tstart = clock();
  matadd(a, b, c, nx, ny, nz, myid, numprocs);
  clock_t tend = clock();

  if (myid == 0)
    printf("time for matrix addition is %.5f\n", (double)(tend - tstart)/CLOCKS_PER_SEC);

  if (myid == 0)
  {
    printf("c = %f\n", c[nx * ny * nz - 1]);

    for (int iz = 0; iz < nz; iz ++)
     for (int iy = 0; iy < ny; iy ++)
       for (int ix = 0; ix < nx; ix++)
         if ((c[iz * ny * nx + iy * nx + ix] - 3.0) >1.0e-2)
         {
              fprintf(stderr, "Error occurs\n");
              return EXIT_FAILURE;
         }
  }

  free(a);
  free(b);
  free(c);

  MPI_Finalize();
  return EXIT_SUCCESS;
}