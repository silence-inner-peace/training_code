#pragma once

#include <math.h>
#include <iostream>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

void GPU_add(float *d_loc_matA,float * d_loc_matB,float * d_loc_matC,int nx,int ny,int loc_nz,dim3 dimBlock,dim3 dimGrid);

