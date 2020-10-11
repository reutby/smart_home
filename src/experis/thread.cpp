#include <iostream>
#include <cassert>
#include <errno.h>
#include "thread.hpp"

namespace experis{

static void* doCommand(void* _command){
    common::Runable* tap = static_cast<common::Runable*>(_command);
    tap->Run();
    return NULL;
}

Thread::Thread(const std::tr1::shared_ptr<common::Runable>& _command)
: m_command(_command)
, m_ptid()
, m_isjoinable(false)
{
    int status = pthread_create(&m_ptid,NULL,doCommand,(void*)((m_command.get())));
    if(status!= 0){
        assert(EINVAL!= status);
        assert(EPERM != status);
        assert(EAGAIN == status); 		
        throw InsufficientResource("Insufficient resources to create another thread");
    }
}
void Thread::Join()
{
    int status = pthread_join(m_ptid,NULL);
    switch (status){
        case 0:
            break;
        case EDEADLK:{
            throw ADeadlockWasdDetected("A deadlock was detected");
            break;
        }
        case EINVAL:{
            throw IsNotAJoinableThread("thread is not a joinable thread");
            break;
        }
        default:{
            assert(ESRCH != status);
            assert(!"Unknown error.");
            break;
        }
    }
}

Thread::~Thread()
{
    //pthread_join(m_ptid,NULL);
}
void Thread::Cancel(){
    if(pthread_cancel(m_ptid)!=0){
        throw ThreadCouldNotBeFound("No thread with the ID thread could be found");
    }
}

pthread_t Thread::ThreadId()const{
    return m_ptid;
}
void Thread::TryJoin()
{
    int status = pthread_tryjoin_np(m_ptid,NULL);
    switch (status){
        case 0:
            break;
        case EBUSY:{
            throw ThreadAsNotBeenTerminated("thread had not yet terminated at the time of the call.");
        }
        case EDEADLK:{
            throw ADeadlockWasdDetected("A deadlock was detected");
        }
        case EINVAL:{
            throw IsNotAJoinableThread("thread is not a joinable thread");
        }
        default:{
            assert(ESRCH != status);
            assert(!"Unknown error.");
            break;
        }
    }

}

}//experis