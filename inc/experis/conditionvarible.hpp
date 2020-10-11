#ifndef CONDITION_VARIBLE_H
#define CONDITION_VARIBLE_H
#include <pthread.h>
#include "uncopyable.hpp"
#include "themutexwasnotownedbycurrentthread.hpp"
#include "iexpression.hpp"
#include <tr1/memory>
namespace experis{

class Mutex;

class ConditionVarible: private UnCopyable{
public:
    ConditionVarible();
    void Wait(Mutex& _mutex, std::tr1::shared_ptr<IExpression> a_expression);
    void Signal();
    void SignalAll();
    ~ConditionVarible();

private:
    pthread_cond_t m_conditionVar;
};

}//experis

#endif//CONDITION_VARIBLE_H