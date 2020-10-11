#ifndef HARD_DISTRIBUTE_POLICY_H
#define HARD_DISTRIBUTE_POLICY_H
#include "idistribute_policy.hpp"
#include "atomicvalue.hpp"
#include "thread.hpp"
#include "isender.hpp"
#include "controller_cmp.hpp"
#include "mutex.hpp"
#include <map>
#include <queue>
#include <vector>
namespace pikachu{

class HardDistributePolicy : public IDistributePolicy{
public:
    typedef std::tr1::shared_ptr<std::queue< std::pair<std::tr1::shared_ptr<IController>, std::tr1::shared_ptr<EventBase> > > >srd_ptr_queue;
    typedef std::map<std::tr1::shared_ptr<IController>, srd_ptr_queue, IControllerCmp > PrivateQueuesMap;
    typedef std::map<std::tr1::shared_ptr<IController>,std::tr1::shared_ptr<experis::MutexWrapper> > QueueMutexesMap;
    HardDistributePolicy(size_t a_numofeventsfordis,std::vector<std::tr1::shared_ptr<IController> >& a_multieventtype);
    // ~HardDistributePolicy();// = default
    void Distribute(std::tr1::shared_ptr<IController> a_controller, std::tr1::shared_ptr<EventBase> a_event);
    void FinishDistribute();
    //for debg
    size_t  GetEventsLeft()const;
private:
    void workersAction(std::tr1::shared_ptr<ISender> a_sender, srd_ptr_queue a_privatequeue
    ,std::tr1::shared_ptr<experis::MutexWrapper> a_queuemutex);
    void initilizedControllersMap( std::vector<std::tr1::shared_ptr<IController> >&a_controllers);
    void initilizedThreads(size_t a_numofthreads, std::vector<std::tr1::shared_ptr<IController> >&a_controllers);

private:    
    mutable experis::AtomicValue<size_t> m_numOfEvents;
    std::vector<std::tr1::shared_ptr<experis::Thread> > m_threads;
    std::vector<std::tr1::shared_ptr<ISender> > m_senders;
    PrivateQueuesMap m_mapControllersPrivateQueues; 
    QueueMutexesMap m_mutexesQueueMap;
};
}//pikachu

#endif//HARD_DISTRIBUTE_POLICY_H