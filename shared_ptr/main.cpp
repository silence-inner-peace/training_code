#include "Shared_ptr.hpp"

using namespace std;




int main()
{

    Shared_ptr<int> p1(new int);
    *p1 = 222;
    cout<<"值："<<*p1<<" 引用计数："<<p1.use_count()<<endl;
    {
        Shared_ptr<int> p2(p1);
        *p2 = 333;
        cout<<"值："<<*p2<<" 引用计数："<<p1.use_count()<<endl;

        Shared_ptr<int> p3(p2);
        *p3 = 444;
        cout<<"值："<<*p3<<" 引用计数："<<p1.use_count()<<endl;
    }

    cout<<"引用计数："<<p1.use_count()<<endl;

    Shared_ptr<string> q1(new string("我是string1"));
    cout<<(*(q1)).c_str()<<endl;

    Shared_ptr<string> q2(new string("我是string2"));
    q2.swap(q1);
    cout<<(*(q1)).c_str()<<endl;

    return 0;
}

