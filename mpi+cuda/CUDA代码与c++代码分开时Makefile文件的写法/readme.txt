nvcc -c test_cuda.cu
mpic++ -c test.cpp
mpic++ -o main test.o test_cuda.o  -L /usr/local/cuda-8.0/lib64 -lcudart