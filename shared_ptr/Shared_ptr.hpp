#ifndef Shared_ptr_Hpp
#define Shared_ptr_Hpp

#include <stdio.h>
#include <iostream>

using namespace std;

template <typename T>
class Shared_ptr
{
private:
    size_t* m_count;
    T* m_ptr;

public:
    //构造函数
    Shared_ptr() : m_ptr(nullptr), m_count(new size_t)
    {}

    Shared_ptr( T* ptr ) : m_ptr(ptr), m_count(new size_t)
    {
        cout<<"空间申请："<<ptr<<endl;
        *m_count = 1;
    }

    //析构函数
    ~Shared_ptr()
    {
        --(*m_count);
        if(*m_count == 0)
        {
            cout<<"空间释放："<<m_ptr<<endl;
            delete m_ptr;
            delete m_count;
            m_ptr = nullptr;
            m_count = nullptr;
        }
    }

    //拷贝构造函数
    Shared_ptr( const Shared_ptr& ptr )
    {
        m_count = ptr.m_count;
        m_ptr = ptr.m_ptr;
        ++(*m_count);
    }

    //拷贝赋值运算符
    void operator=( const Shared_ptr& ptr )
    {
        Shared_ptr(std::move(ptr));
    }

    //移动构造函数
    Shared_ptr( Shared_ptr&& ptr ) : m_ptr(ptr.m_ptr), m_count(ptr.m_count)
    {
        ++(*m_count);
    }

    //移动赋值运算符
    void operator=( Shared_ptr&& ptr )
    {
        Shared_ptr(std::move(ptr));
    }

    //解引用运算符
    T& operator*()
    {
        return *m_ptr;
    }

    //箭头运算符
    T* operator->()
    {
        return m_ptr;
    }

    //重载布尔值操作
    operator bool()
    {
        return m_ptr == nullptr;
    }

    T* get()
    {
        return m_ptr;
    }

    size_t use_count()
    {
        return *m_count;
    }

    bool unique()
    {
        return *m_count == 1;
    }

    void swap( Shared_ptr& ptr )
    {
        std::swap(*this, ptr);
    }

};



#endif /* Shared_ptr_Hpp */

