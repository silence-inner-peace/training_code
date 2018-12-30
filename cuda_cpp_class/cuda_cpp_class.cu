#include <stdio.h>

#include <iostream>

#include <cuda.h>

#include <cuda_runtime.h>

class MyClass;

__global__ void kernel(int *a, unsigned int N);



class MyClass {

public:

  MyClass(int len) {

    length = len;

    cudaMalloc((void **)&d_data, sizeof(int)*length);

    cudaMemset((void *)d_data, 0, sizeof(int)*length);

  };

  

  ~MyClass() {

    cudaFree((void *)d_data);

    printf("%s\n","cudafree" );

  };

  

  void run(dim3 grid,dim3 block) {

    kernel<<<grid, block>>>(d_data, length);

  };





  void set(int* h_data)

  {

  cudaMemcpy(d_data,h_data,sizeof(int)*length,cudaMemcpyHostToDevice);

  }

  

  int* getData(void) {

    return d_data;

  };

  int getLength(void)

  {

    return length;

  }

  void show(void)

  {

    int h_data[length];

    cudaMemcpy(h_data, getData(), sizeof(int)*length, cudaMemcpyDeviceToHost);

    for (int i=0; i<length; i++) {

      std::cout << h_data[i] << " ";

    }

    std::cout << std::endl;

  }

public:

  int *d_data;

  int length;

};





__global__ void kernel(int *a, unsigned int N) 
{
  const unsigned int i = blockIdx.x*blockDim.x+threadIdx.x;
  if (i<N) {
    a[i] += i;
  }
}
__global__ void kernel1(int *a, unsigned int N) 
{
  const unsigned int i = blockIdx.x*blockDim.x+threadIdx.x;
  if (i<N) {
    a[i] += 2*i;
  }
}
class MyClass1:public MyClass
{
public:
  MyClass1(int len):MyClass(len){};
  void run(dim3 grid,dim3 block) 
  {
    kernel1<<<grid, block>>>(d_data, length);
  };
};

int main(void) {

  int arraySize = 20;
  int* testArr = new int[arraySize];
  for (int i = 0; i < arraySize; ++i)
  {
      testArr[i] = i;
  }

  // MyClass c(arraySize);  //直接声明的对象是定义在栈上的，会被自动释放  
  // c.run();
  // c.show();



  dim3 grid(1);

  dim3 block(arraySize);

  MyClass1 *c = new MyClass1(arraySize);

  c->set(testArr);

  c->run(grid,block);

  c->show();

  delete c; //用指针指向new出来的对象是存放在堆上的，必须要手动delete对象，否则对象不会被释放掉。

}
