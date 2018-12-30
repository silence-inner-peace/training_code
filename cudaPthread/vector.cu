#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>
#include "vector.h"
#include "vector_kernel.h"

void vectorAdd(float *a, float *b, float *c, int n)
{
	float *d_a, *d_b, *d_c;
	cudaMalloc((void **)&d_a, n * sizeof(float));
	cudaMemcpy(d_a, a, n * sizeof(float), cudaMemcpyHostToDevice);
	cudaMalloc((void **)&d_b, n * sizeof(float));
	cudaMemcpy(d_b, b, n * sizeof(float), cudaMemcpyHostToDevice);
	cudaMalloc((void **)&d_c, n * sizeof(float));
	cudaMemcpy(d_b, b, n * sizeof(float), cudaMemcpyHostToDevice);
	vectorAddKernel<<<1, n>>>(d_a, d_b, d_c, n);
	cudaMemcpy(c, d_c, n * sizeof(float), cudaMemcpyDeviceToHost);
	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
}
