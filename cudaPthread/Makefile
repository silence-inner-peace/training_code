vector : main.o vector.o vector_kernel.o
	nvcc -o vector main.o vector.o vector_kernel.o

vector_kernel.o : vector_kernel.cu vector_kernel.h
	nvcc -c vector_kernel.cu

vector.o : vector.cu vector.h vector_kernel.h
	nvcc -c vector.cu

main.o : main.cc vector.h
	cc -c main.cc -lpthread

clean:
	rm -rf *.o vector
