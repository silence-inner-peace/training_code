// #include "singleton.h"

class MyClass {
public:
    MyClass() {
        myArr = NULL;
        std::cout << "MyClass::MyClass()" << std::endl;
    }
    void setId(int Id)
    {
        myId = Id;
    }
    int getId()
    {
        return myId;
    }
    int* getArr()
    {
        return myArr;
    }
    void setArr(int* pp)
    {
        myArr = pp;
    }

    ~MyClass() {
        std::cout << "MyClass::~MyClass()" << std::endl;
    }
private:
    int myId;
    int* myArr;
};