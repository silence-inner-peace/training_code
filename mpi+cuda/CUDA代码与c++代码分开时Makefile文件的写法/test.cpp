#include<stdio.h>
#include<malloc.h>
#include<math.h>
#include<stdlib.h>
#include "mpi.h"

extern "C" void cudaFun (int is , FILE  *fp ,  int  nx , int nz );
int main( int argc, char  *argv[ ] )
{
        int myid , numprocs , count , is , nx , nz ;
        float * vp;

        nx = 1000 ; nz = 1000 ;

        MPI_Init(&argc,&argv);
        MPI_Comm_rank(MPI_COMM_WORLD,&myid);
        MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
        MPI_Barrier(MPI_COMM_WORLD);

        FILE *fp;
        fp=fopen( "test.dat" , "wb" );
        for ( is = myid ; is < 10 ; is = is    +    numprocs )
        {
                printf( " is== %d  \n "  , is ) ;
                cudaFun( is , fp , nx , nz );
        }
        MPI_Finalize( );
	return 0;
}

