#include <stdio.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include <iostream>
#include "Array2D_CUDA.h"
using namespace std;

__global__ void kernel1(int* d_output, int *a, unsigned int N) 
{
  const unsigned int i = blockIdx.x*blockDim.x+threadIdx.x;
  if (i<N) {
    d_output[i] = a[i] + i;
  }
}
__global__ void kernel2(int* d_output, int *a, unsigned int N) 
{
  const unsigned int i = blockIdx.x*blockDim.x+threadIdx.x;
  if (i<N) {
    d_output[i] = a[i] + 2*i;
  }
}

class AbstractMetricsProcess
{
public:
	AbstractMetricsProcess(int rows, int cols)
	{
		int arraySize = rows*cols;
		int* testArr = new int[arraySize];
		for (int i = 0; i < arraySize; ++i)
		{
		  testArr[i] = i;
		}
		img = new Array2D< Cutype<int> >(rows,cols);
		img->set(testArr);
	}
	// void runCCL();
	virtual void calMetrics(dim3 grid,dim3 block) = 0;	//具体的指数计算类推迟到子类中实现
	void templateMethod(int rows, int cols, dim3 grid, dim3 block)
	{
    img->show();
    calMetrics(grid,block);
	}
  ~AbstractMetricsProcess()
  {
    delete img;
    img = NULL;
  }
public:
	Array2D< Cutype<int> >* img;
};



class ConcreateArea:public AbstractMetricsProcess 	
{
public:
	Array2D< Cutype<int> >* d_data1;  //每个派生类中的run函数封装一种对标记数组的操作，并将结果存储到派生类的成员变量中
public:
  ConcreateArea(int rows, int cols):AbstractMetricsProcess(rows,cols)
  {
    d_data1 = new Array2D< Cutype<int> >(rows,cols);
  };
  void calMetrics(dim3 grid,dim3 block) 
  {
    kernel1<<<grid, block>>>(d_data1->getDevData(), img->getDevData(), img->size());		//d_data来源于父类，d_data1来源于派生类
    d_data1->show();
  };
  ~ConcreateArea()
  {
    delete d_data1;
    d_data1 = NULL;
  }
};


class ConcreatePeri:public AbstractMetricsProcess
{
public:
	Array2D< Cutype<int> >* d_data2;
public:
  ConcreatePeri(int rows, int cols):AbstractMetricsProcess(rows,cols)
  {
    d_data2 = new Array2D< Cutype<int> >(rows,cols);
  };
  void calMetrics(dim3 grid,dim3 block) 
  {
    kernel2<<<grid, block>>>(d_data2->getDevData(), img->getDevData(), img->size());
    d_data2->show();
  };
  ~ConcreatePeri()
  {
    delete d_data2;
    d_data2 = NULL;
  }
};

template <class T>
void callTemplateMethod(T *proc,int rows,int cols,dim3 grid,dim3 block)
{
  if (proc!=NULL)
  {
    proc->templateMethod(rows,cols,grid,block);
    delete proc;
    proc = NULL;
  }
}




int main(int argc, char const *argv[])
{
  int rows = 10;
  int cols = 2;
	int arraySize = rows*cols;
	dim3 grid(1);
	dim3 block(arraySize);

  //下面这两个派生类的对象分别拥有一个基类对象，对象的地址是不同的，所以如果需要共用基类对象，需要将操作写到一个类中。
	ConcreatePeri *procPeri = new ConcreatePeri(rows,cols);
  callTemplateMethod(procPeri,rows,cols,grid,block);
  cout << "******************************************" << endl;
  ConcreateArea *procArea = new ConcreateArea(rows,cols);
  callTemplateMethod(procArea,rows,cols,grid,block);
  
	return 0;
}