#ifndef MUTEX_H
#define MUTEX_H
#include <pthread.h>
#include "uncopyable.hpp"
#include "conditionvarible.hpp"
#include "insufficientmemoryexiststoinit.hpp"
#include "noprivilegetoperformtheoperation.hpp"
#include "systemlackedthenecessaryresources.hpp"
#include "thecurrentthreadnotownthemutex.hpp"
#include "mutexalreadylocked.hpp"

namespace experis{
class Mutex: private UnCopyable{

public:
    Mutex();
    virtual ~Mutex();
    void Lock();
    void UnLock();
private:
    pthread_mutex_t* GetMutex()const;
    friend void ConditionVarible::Wait(Mutex& _mutex, std::tr1::shared_ptr<IExpression> a_expression);
private:
    mutable pthread_mutex_t m_mutex;
};

inline pthread_mutex_t* Mutex::GetMutex()const
{
    return &m_mutex;
}

class MutexWrapper;
class Locker {
public:
    Locker(Mutex& a_mutex);
    Locker(std::tr1::shared_ptr<MutexWrapper> a_mutex);
    ~Locker();

private:
    Mutex& m_locker;
};

class MutexWrapper : private experis::UnCopyable{
    friend class Locker;
public:
    // MutexWrapper();// = default
    // ~MutexWrapper();// = default
private:
    Mutex m_mutex;
};

}//experis

#endif //MUTEX_H
