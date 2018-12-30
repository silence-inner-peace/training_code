#include "singleton.h"
#include "myclass.h"
#include <iostream>

typedef Singleton<MyClass> MyClassSingleton;   // Global declaration

int main(){
    
    MyClass & obj = MyClassSingleton::Instance();
    obj.setId(1);
    int* p = obj.getArr();

    MyClass & obj1 = MyClassSingleton::Instance();
    obj1.setId(2);
    int* p1 = obj1.getArr();

    int i = 0;
    int*pp = new int[5];
    for(i=0;i<5;i++)
        pp[i] = i;
    obj1.setArr(pp);
    
    p = obj.getArr();
    p1 = obj1.getArr();

    return 0;
}

 
