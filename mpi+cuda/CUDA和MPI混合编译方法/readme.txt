nvcc -c kernel.cu

mpic++ -c test.cpp -L /usr/local/cuda-8.0/lib64 -lcudart -I /usr/local/cuda-8.0/include

mpic++ -o main test.o kernel.o -L /usr/local/cuda-8.0/lib64 -lcudart -I /usr/local/cuda-8.0/include