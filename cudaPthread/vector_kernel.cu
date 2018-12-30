#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>
#include "vector_kernel.h"

__global__ void vectorAddKernel(float *a, float *b, float *c, int n)
{
	int tid;
	tid = threadIdx.x;
	if(tid < n)
		c[tid] = a[tid] + b[tid];
}
