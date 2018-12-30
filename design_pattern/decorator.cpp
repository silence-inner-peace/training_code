#include <iostream>
#include <string>
using namespace std; 

//抽象角色类
class Role
{
public:
    virtual void Action() = 0;              //抽象行动类
};

//具体角色类
class RealPlayer : public Role
{
public:
    void Action()
    {
        cout << "动作结束" << endl;
    }
};

//装饰类
class Decorator : public Role
{
public:
    Decorator(Role * pRole) : m_pRoleObj(pRole) {}
    void Action()
    {
        if (m_pRoleObj != NULL)
        {
            m_pRoleObj->Action();
        }
    }
protected:
    Role *m_pRoleObj;
};

//具体装饰类：出拳
class ConcreateAction1 : public Decorator
{
public:
    ConcreateAction1(Role *pDecorator) : Decorator(pDecorator) {}
    void Action()
    {
        AddedBehavior();
        Decorator::Action();
    }
    void  AddedBehavior()
    {
        cout << "出拳  " << endl;
    }
};

//具体动作装饰类：踢腿
class ConcreateAciton2 : public Decorator
{
public:
    ConcreateAciton2(Role *pDecorator) : Decorator(pDecorator) {}
    void Action()
    {
        AddedBehavior();
        Decorator::Action();
    }
    void  AddedBehavior()
    {
        cout << "踢腿  " << endl;
    }
};

int main()
{
    Role* pRole = new RealPlayer();

    //让角色出拳
    Decorator* pAction1 = new ConcreateAction1(pRole);

    //让角色踢腿
    Decorator* pAction2 = new ConcreateAciton2(pAction1);

    pAction2->Action();

    delete pRole;
    pRole = NULL;

    delete pAction1;
    pAction1 = NULL;

    delete pAction2;
    pAction2 = NULL;

//    getchar();
    return 0;
}

