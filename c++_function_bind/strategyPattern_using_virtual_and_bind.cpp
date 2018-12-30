#include <iostream>
#include <functional>
using namespace std;

//virtual class strategy pattern
class Calculater
{
public:
    virtual int calculate(int x, int y) = 0;
};

class Minus : public Calculater
{
public:
    int calculate(int x, int y) 
    {
        return x - y;
    }
};

class Plus : public Calculater
{
public:
    int calculate(int x, int y) 
    {
        return x + y;
    }
};

class CalcuClient
{
private:
    Calculater* m_caculater;
public:
    CalcuClient(Calculater* caculater) : m_caculater(caculater){}

    int calculate(int x, int y)
    {
        return m_caculater->calculate(x, y);
    }
};


//bind+function strategy pattern
class NewCalcuClient
{
private:
    std::function<int(int, int)> m_function;

public:
    NewCalcuClient(std::function<int(int, int)> function) : m_function(function){}

    int calculate(int x, int y)
    {
        return m_function(x, y);
    }
};


int main()
{
    Minus minus;
    CalcuClient virtualMinus(&minus);

    Plus plus;
    CalcuClient virtualPlus(&plus);

    int r = virtualMinus.calculate(7, 4);
    int r2 = virtualPlus.calculate(7, 4);

// bind+function
    NewCalcuClient bindMinus(bind(&Minus::calculate, &minus, placeholders::_1, placeholders::_2));
    NewCalcuClient bindPlus(bind(&Plus::calculate, &plus, placeholders::_1, placeholders::_2));
    int r3 = bindMinus.calculate(7, 4);
    int r4 = bindPlus.calculate(7, 4);
    
    cout<<"virtualMinus: "<<r<<endl;
    cout<<"virtualPlus: "<<r2<<endl;
    cout<<"bindMinus: "<<r3<<endl;
    cout<<"bindPlus: "<<r4<<endl;


    return 0;
}
