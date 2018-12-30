#include <iostream>
#include <functional>
#include <memory>
using namespace std;

///////////////////////////////////////////////////////////////////
//virtual class responsibility pattern
///////////////////////////////////////////////////////////////////
struct Request
{
    int RequestType;
};

class Handler
{
protected:
    std::shared_ptr<Handler> m_next;
public:
    Handler(std::shared_ptr<Handler> next) : m_next(next){}

    virtual void HandleRequest(Request) = 0;
};

class ConcreteHandler1 : public Handler
{
public:
    ConcreteHandler1(std::shared_ptr<Handler> next) : Handler(next){}

    void HandleRequest(Request request)
    {
        if (request.RequestType == 1)
        {
            cout << "request handled in ConcreteHandler1" << endl;
        }
        else
        {
            if (m_next != nullptr)
                m_next->HandleRequest(request);
        }
    }
};

class ConcreteHandler2 : public Handler
{
public:
    ConcreteHandler2(std::shared_ptr<Handler> next) : Handler(next){}

    void HandleRequest(Request request)
    {
        if (request.RequestType == 2)
        {
            cout << "request handled in ConcreteHandler2" << endl;
        }
        else
        {
            if (m_next != nullptr)
                m_next->HandleRequest(request);
        }
    }
};

class ConcreteHandler3 : public Handler
{
public:
    ConcreteHandler3(std::shared_ptr<Handler> next) : Handler(next){}

    void HandleRequest(Request request)
    {
        if (request.RequestType == 3)
        {
            cout << "request handled in ConcreteHandler3" << endl;
        }
        else
        {
            if (m_next != nullptr)
                m_next->HandleRequest(request);
        }
    }
};

///////////////////////////////////////////////////////////////////
//bind+function responsibility pattern
///////////////////////////////////////////////////////////////////
class ChainHandler
{
    
public:
    std::function<void(Request)> function;

    void HandleRequest(Request request)
    {
        function(request);
    }

    std::function<void(Request)>& getfunction()
    {
        return function;
    }
};

void assemble(std::function<void(Request)> call, std::function<void(Request)> next, Request request)
{
    if (next != nullptr)
        next(request);
    else
        call(request);
}

///////////////////////////////////////////////////////////////////
// test
///////////////////////////////////////////////////////////////////
void Test()
{
    auto thirdHandler = std::make_shared<ConcreteHandler3>(nullptr); 
    auto secondHandler = std::make_shared<ConcreteHandler2>(thirdHandler); 
    auto firstHandler = std::make_shared<ConcreteHandler1>(secondHandler); 

    Request request = { 2 };
    firstHandler->HandleRequest(request);

//////////////////////////////////////////////////////////////////////////

    ChainHandler chain;
    
    std::function<void(Request)> f1 = std::bind(&ConcreteHandler1::HandleRequest, firstHandler, std::placeholders::_1);
    std::function<void(Request)> f2 = std::bind(&ConcreteHandler2::HandleRequest, secondHandler, std::placeholders::_1);
    std::function<void(Request)> f3 = std::bind(&ConcreteHandler3::HandleRequest, thirdHandler, std::placeholders::_1);
    
    chain.function = std::bind(&assemble, f1, chain.function, std::placeholders::_1);
    chain.function = std::bind(&assemble, f2, chain.function, std::placeholders::_1);
    chain.function = std::bind(&assemble, f3, chain.function, std::placeholders::_1);

    chain.HandleRequest(request);
}

int main()
{
	Test();
    return 0;
}
