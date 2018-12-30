#pragma pack(push)
#pragma pack(4)                                //要是这里的改成1字节对齐，则这个类是13个字节，而不是16个字节
#include <iostream>
using namespace std;

class A                                         //总字节数：4+1+8=13，由于4字节对齐，所以为16
{
public:
	int a;					//4个字节
	char b;					//一个字节
	virtual void fun1(){			//虚函数，代表有虚表，因此会创建一个8个字节的虚表指针
		
	}
	virtual void fun2(){

	}
	
	static int c;				//用static 修饰，代表存储在静态数据区，因此不占字节。
	void f();				//在代码段，不占字节。
};

int main()
{
	int a;
	a = sizeof(A);
	cout<<a<<endl;

	A obj;
	cout<<sizeof(obj)<<endl;
	return 0;
}
