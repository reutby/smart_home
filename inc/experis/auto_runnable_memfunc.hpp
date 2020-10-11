#ifndef AUTO_RUNNABLE_MEM_FUNC_H
#define AUTO_RUNNABLE_MEM_FUNC_H
#include "runable.hpp"

namespace experis{
namespace common{

template<class ClassName>
class AutoRunnableMemFunc : public common::Runable{
public:
    typedef void (ClassName::*Func)();
    AutoRunnableMemFunc(ClassName& a_ref,Func a_func);
    virtual ~AutoRunnableMemFunc(){}; 
    virtual void Run();
private:
    ClassName& m_ref;
    Func m_funcToRun;
};

template<class ClassName>
AutoRunnableMemFunc<ClassName>::AutoRunnableMemFunc(ClassName& a_ref,Func a_func)
: m_ref(a_ref)
, m_funcToRun(a_func)
{
}
template<class ClassName>
void AutoRunnableMemFunc<ClassName>::Run()
{
    (m_ref.*m_funcToRun)();
}


template<class ClassName,class A1>
class AutoRunnableMemFuncOneArg : public common::Runable{
public:
    typedef void (ClassName::*Func)(A1);
    AutoRunnableMemFuncOneArg(ClassName& a_ref,Func a_func, A1& a_arg1);
    //virtual ~AutoRunnableMemFuncThreeArg(){}; 
    virtual void Run();
private:
    ClassName& m_ref;
    Func m_funcToRun;
    A1 m_arg1;
   
};

template<class ClassName,class A1>
AutoRunnableMemFuncOneArg<ClassName,A1>::AutoRunnableMemFuncOneArg(ClassName& a_ref,Func a_func, A1& a_arg1)
: m_ref(a_ref)
, m_funcToRun(a_func)
, m_arg1(a_arg1)
{
}

template<class ClassName,class A1>
void AutoRunnableMemFuncOneArg<ClassName,A1>::Run()
{
    (m_ref.*m_funcToRun)(m_arg1);
}



template<class ClassName,class A1, class A2>
class AutoRunnableMemFuncTwoArg : public common::Runable{
public:
    typedef void (ClassName::*Func)(A1,A2);
    AutoRunnableMemFuncTwoArg(ClassName& a_ref,Func a_func, A1 a_arg1,A2 a_arg2);
    //virtual ~AutoRunnableMemFuncThreeArg(){}; 
    virtual void Run();
private:
    ClassName& m_ref;
    Func m_funcToRun;
    A1 m_arg1;
    A2 m_arg2;
};

template<class ClassName,class A1, class A2>
AutoRunnableMemFuncTwoArg<ClassName,A1,A2>::AutoRunnableMemFuncTwoArg(ClassName& a_ref,Func a_func, A1 a_arg1,A2 a_arg2)
: m_ref(a_ref)
, m_funcToRun(a_func)
, m_arg1(a_arg1)
, m_arg2(a_arg2)
{
}

template<class ClassName,class A1, class A2>
void AutoRunnableMemFuncTwoArg<ClassName,A1,A2>::Run()
{
    (m_ref.*m_funcToRun)(m_arg1,m_arg2);
}



template<class ClassName,class A1, class A2 , class A3>
class AutoRunnableMemFuncThreeArg : public common::Runable{
public:
    typedef void (ClassName::*Func)(A1,A2,A3);
    AutoRunnableMemFuncThreeArg(ClassName& a_ref,Func a_func, A1 a_arg1,A2 a_arg2, A3 a_arg3);
    //virtual ~AutoRunnableMemFuncThreeArg(){}; 
    virtual void Run();
private:
    ClassName& m_ref;
    Func m_funcToRun;
    A1 m_arg1;
    A2 m_arg2;
    A3 m_arg3;
};

template<class ClassName,class A1, class A2 , class A3>
AutoRunnableMemFuncThreeArg<ClassName,A1,A2,A3>::AutoRunnableMemFuncThreeArg(ClassName& a_ref,Func a_func, A1 a_arg1,A2 a_arg2, A3 a_arg3)
: m_ref(a_ref)
, m_funcToRun(a_func)
, m_arg1(a_arg1)
, m_arg2(a_arg2)
, m_arg3(a_arg3)
{
}

template<class ClassName,class A1, class A2 , class A3>
void AutoRunnableMemFuncThreeArg<ClassName,A1,A2,A3>::Run()
{
    (m_ref.*m_funcToRun)(m_arg1,m_arg2,m_arg3);
}


}//common
}//experis
#endif//AUTO_RUNNABLE_MEM_FUNC_H