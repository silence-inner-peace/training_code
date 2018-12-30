CUDA_INSTALL_PATH = /usr/local/cuda-8.0
MPI_INSTALL_PATH = /home/mpi/mpich-3.2.1

NVCC = $(CUDA_INSTALL_PATH)/bin/nvcc
MPICC = $(MPI_INSTALL_PATH)/bin/mpic++
LDFLAGS = -L $(CUDA_INSTALL_PATH)/lib64
LIB = -lcudart
CUDA_INCLUDE = -I /usr/local/cuda-8.0/include

CFILES = test.cpp
CUFILES = kernel.cu
OBJECTS = kernel.o test.o 
EXECNAME = test

all:
	$(NVCC) -c $(CUFILES)
	$(MPICC) -c $(CFILES) $(LDFLAGS) $(LIB) $(CUDA_INCLUDE)
	$(MPICC) -o $(EXECNAME) $(OBJECTS) $(LDFLAGS) $(LIB) $(CUDA_INCLUDE)

clean:
	rm -f *.o $(EXECNAME)
