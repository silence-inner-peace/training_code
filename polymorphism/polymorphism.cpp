//#pragma pack(push)
//#pragma pack(4)

#include<iostream>
using namespace std;

class A {}; 

class B 
{
public:
  B() {}
  ~B() {}
//  void MemberFuncTest( int para ) { }
  static void StaticMemFuncTest( int para ){  }
};

class C 
{
 C(){}
 virtual ~C() {}
};

class D 
{
 D(){}
 virtual ~D() {}
 virtual int VirtualMemFuncTest1()=0;
 virtual int VirtualMemFuncTest2()=0;
 virtual int VirtualMemFuncTest3()=0;
};

class E
{
 int  m_Int;
 char m_Char;
};

class F : public E
{
 static int s_data ;
};
int F::s_data=100;

class G : public E
{
 virtual int VirtualMemFuncTest1(int para)=0;
 int m_Int;
};
class H : public G
{
 int m_Int;
};

class I : public D
{
 virtual int VirtualMemFuncTest1()=0;
 virtual int VirtualMemFuncTest2()=0;
};

int main( int argc, char **argv )
{
 cout<<"sizeof( A ) = "<<sizeof( A )<<endl;
 cout<<"sizeof( B ) = "<<sizeof( B )<<endl;
 cout<<"sizeof( C ) = "<<sizeof( C )<<endl;
 cout<<"sizeof( D ) = "<<sizeof( D )<<endl;
 cout<<"sizeof( E ) = "<<sizeof( E )<<endl;
 cout<<"sizeof( F ) = "<<sizeof( F )<<endl;
 cout<<"sizeof( G ) = "<<sizeof( G )<<endl;
 cout<<"sizeof( H ) = "<<sizeof( H )<<endl;
 cout<<"sizeof( I ) = "<<sizeof( I )<<endl;

#if defined( _WIN32 )
 system("pause");
#endif
 return 0;
}
