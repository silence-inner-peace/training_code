#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include "device_launch_parameters.h"
#include <device_functions.h>
#include <cuda_runtime_api.h>

__device__  volatile  int  vint = 0;
//a#########################
__global__ void fun ( float  * vp_device , int n, int nz, int  is )
{
        int it = threadIdx.x + blockDim.x * blockIdx.x;
        if  ( it < n ) {
                vp_device[it]=2000;
                if ( ( it > nz * 40 && it < 40 && it % nz < 60 ) ) 
                        vp_device [ it ] = 2500 * is * 100 ;
        }
}
//a########################
extern "C" void cudaFun ( int is , FILE  *fp ,  int  nx , int nz )
{
        int i ;
        float  * vp_device , * vp_host;

        cudaMalloc(&vp_device, nx*nz*sizeof(float));  
        cudaMemset(vp_device, 0, nx*nz*sizeof(float));

        vp_host=(float*)malloc(nx*nz*sizeof(float));

        float mstimer;

        cudaEvent_t start, stop;
        cudaEventCreate(&start);
        cudaEventCreate(&stop);

        fun <<<(  nx * nz   +   511 ) / 512, 512>>> ( vp_device ,  nx*nz , nz , is ) ;

        cudaMemcpy(vp_host, vp_device, nx*nz*sizeof(float),cudaMemcpyDeviceToHost); 

        fseek(fp,is*nx*nz*sizeof(float),0);
        for (  i  =  0  ;  i  <  nx  *  nz   ;  i   ++   )
                fwrite( &vp_host[i] , sizeof(float) , 1 , fp);

        cudaEventRecord(stop);
        cudaEventSynchronize(stop);
        cudaEventElapsedTime(&mstimer, start, stop);
        printf( "CUDA : is = %d, time = %g (s)\\n " ,is, mstimer/1000);
        cudaEventDestroy(start);
        cudaEventDestroy(stop);

        cudaFree(vp_device);
        free(vp_host);
}
