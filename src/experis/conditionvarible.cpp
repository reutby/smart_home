#include <cassert>
#include <errno.h>
#include "conditionvarible.hpp"
#include "systemlackedthenecessaryresources.hpp"
#include "insufficientmemoryexiststoinit.hpp"

namespace experis{

ConditionVarible::ConditionVarible()
{
    int result = pthread_cond_init(&m_conditionVar, NULL);
    switch(result){
		case 0:
			break;
		case ENOMEM:
			throw InsufficientMemoryExistsToInit("Insufficient memory exists to initialize the condition variable.");
		case EAGAIN:
			throw SystemLackedTheNecessaryResources("The system lacked the necessary resources (other than memory) to initialize another condition variable.");
		default:
			assert(result != EBUSY);
			assert(result != EINVAL);
			assert(!"Unknown error.");
	}
}


void ConditionVarible::SignalAll()
{
	int result = pthread_cond_broadcast(&m_conditionVar);
	if (result != 0){
		assert(EINVAL != result);
		assert(!"Unknown error.");
	}
}
void ConditionVarible::Signal()
{
    int result = pthread_cond_signal(&m_conditionVar);
    if (result != 0){
	    assert(EINVAL != result);
		assert(!"Unknown error.");
    }
}

ConditionVarible::~ConditionVarible(){
    int result = pthread_cond_destroy(&m_conditionVar);
    if (result != 0){
		assert(result != EINVAL);
		assert(result == EBUSY);
        SignalAll();
        pthread_cond_destroy(&m_conditionVar); 
	}
}

}//experis