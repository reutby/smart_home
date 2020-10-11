#ifndef THREAD_H
#define THREAD_H
#include <tr1/memory>
#include <pthread.h>
#include "runable.hpp"
#include "insufficientresource.hpp"
#include "adeadlockwasddetected.hpp"
#include "isnotajoinablethread.hpp"
#include "threadcouldnotbefound.hpp"
#include "thread_asnot_been_terminated.hpp"
namespace experis{

class Thread{

public:
    Thread(const std::tr1::shared_ptr<common::Runable> &_command);
    void Join();
    void TryJoin();
    pthread_t ThreadId()const;
    void Cancel();
    ~Thread();
private:
    const std::tr1::shared_ptr<common::Runable> m_command;
    pthread_t m_ptid;
    bool m_isjoinable;
    Thread(const Thread& _thread);
    Thread& operator=(const Thread& _thread);
};

}//experis


#endif //THREAD_H
