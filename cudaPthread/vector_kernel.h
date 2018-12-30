#include <stdio.h>
#include <cuda.h>
#include <stdlib.h>

__global__ void vectorAddKernel(float *a, float *b, float *c, int n);
