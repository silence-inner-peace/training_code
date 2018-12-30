CUDA_INSTALL_PATH = /usr/local/cuda-8.0
MPI_INSTALL_PATH = /home/mpi/mpich-3.2.1

NVCC = $(CUDA_INSTALL_PATH)/bin/nvcc
MPICC = $(MPI_INSTALL_PATH)/bin/mpic++

LDFLAGS = -L $(CUDA_INSTALL_PATH)/lib64
LIB = -lcudart


CFILES = test.cpp
CUFILES = test_cuda.cu
OBJECTS = test_cuda.o test.o 
EXECNAME = test

all:
	$(NVCC) -c $(CUFILES)
	$(MPICC) -c $(CFILES)
	$(MPICC) -o $(EXECNAME) $(OBJECTS) $(LDFLAGS) $(LIB) 

clean:
	rm -f *.o $(EXECNAME)

# 用以下三行即可
# nvcc -c test_cuda.cu
# mpic++ -c test.cpp
# mpic++ -o out.o test.o test_cuda.o  -L /usr/local/cuda-8.0/lib64 -lcudart