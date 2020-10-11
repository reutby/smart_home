#include <cassert>
#include <errno.h>
#include "mutex.hpp"

namespace experis{

Mutex::Mutex()
{
    int result = pthread_mutex_init(&m_mutex,NULL);
    switch(result){
		case 0:
			break;
		case ENOMEM:
			throw InsufficientMemoryExistsToInit("Mutex::Mutex() - Insufficient memory exists to initialize the mutex.");
		case EPERM:
			throw NoPrivilegeToPerformTheOperation("Mutex::Mutex() - The caller does not have the privilege to perform the operation.");
		case EAGAIN:
			throw SystemLackedTheNecessaryResources("Mutex::Mutex() - The system lacked the necessary resources (other than memory) to initialize another mutex.");
		default:
			assert(result != EBUSY);
			assert(result != EINVAL);
			assert(!"Unknown error.");
	}
}

void Mutex::Lock()
{
	int status = pthread_mutex_lock(&m_mutex);
	if (status != 0){
		assert(status != EINVAL);
		assert(status != EAGAIN);
		assert(status != EDEADLK);
		assert(status == EBUSY);
		throw MutexAlreadyLocked("mutex already locked");
	}
}

void Mutex::UnLock(){
	int status = pthread_mutex_unlock(&m_mutex);
	if (status != 0){
		assert(errno != EINVAL);
		assert(errno != EAGAIN);
		assert(status == EPERM);
		throw TheCurrentThreadNotOwnTheMutex("Mutex::UnLock() - The current thread does not own the mutex.");
	}
}

Mutex::~Mutex(){
	int status = pthread_mutex_destroy(&m_mutex);
	if (status != 0){
		assert(status != EINVAL);
		assert(status == EBUSY);
		UnLock();
		pthread_mutex_destroy(&m_mutex);
	}
}
void ConditionVarible::Wait(Mutex& _mutex, std::tr1::shared_ptr<IExpression> a_expression)
{
	while(a_expression->CheackEexpression())
	{
		int result = pthread_cond_wait(&m_conditionVar,_mutex.GetMutex());
		if (result != 0){
			assert(EINVAL != result);
			assert(EPERM == result);
			throw TheMutexWasNotOwnedByCurrentThread("The mutex was not owned by the current thread at the time of the call.");
		}
		if(a_expression->CheackEexpression()){
			return;
		}
	}
}
Locker::Locker(Mutex& a_mutex)
: m_locker(a_mutex)
{
	m_locker.Lock();
}

Locker::Locker(std::tr1::shared_ptr<MutexWrapper> a_mutex)
: m_locker(a_mutex->m_mutex)
{
	m_locker.Lock();
}
Locker::~Locker()
{
	m_locker.UnLock();
}


}//experis
