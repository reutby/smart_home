#ifndef AUTO_RUNNABLE_STATIC_FUNC_H
#define AUTO_RUNNABLE_STATIC_FUNC_H
#include "runable.hpp"

namespace experis{
namespace common{

class AutoRunnableStaticFunc : public Runable{
public:
    typedef void (*Func)();
    AutoRunnableStaticFunc(Func a_func);
    virtual void Run();
private:
    Func m_funcToRun;
};

template<class A1>
class AutoRunnableStaticFuncOneArg : public Runable{
public:
    typedef void (*Func)(A1);
    AutoRunnableStaticFuncOneArg(Func a_func, A1& a_arg); 
    virtual void Run();
private:
    Func m_funcToRun;
    A1& m_arg;
};

template <class A1>
AutoRunnableStaticFuncOneArg<A1>:: AutoRunnableStaticFuncOneArg(Func a_func, A1 &a_arg)
: m_funcToRun(a_func)
, m_arg(a_arg)
{
}

template <class A1>
void AutoRunnableStaticFuncOneArg<A1>:: Run()
{
    m_funcToRun(m_arg);
}


template<class A1,class A2>
class AutoRunnableStaticFuncTwoArg : public Runable{
public:
    typedef void (*Func)(A1,A2);
    AutoRunnableStaticFuncTwoArg(Func a_func, A1 a_arg1,A2& A_arg2); 
    virtual void Run();
private:
    Func m_funcToRun;
    A1 m_arg1;
    A2 m_arg2;
};


template <class A1,class A2>
AutoRunnableStaticFuncTwoArg<A1,A2>:: AutoRunnableStaticFuncTwoArg(Func a_func, A1 a_arg1, A2 &a_arg2)
: m_funcToRun(a_func)
, m_arg1(a_arg1)
, m_arg2(a_arg2)
{
}

template <class A1, class A2>
void AutoRunnableStaticFuncTwoArg<A1,A2>:: Run()
{
    m_funcToRun(m_arg1,m_arg2);
}

}//common
}//experis
#endif//AUTO_RUNNABLE_STATIC_FUNC_H