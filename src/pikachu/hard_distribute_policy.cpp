#include "hard_distribute_policy.hpp"
#include <algorithm>
#include "auto_runnable_memfunc.hpp"
#include "sender_mvp.hpp"
#include "atomicvalue.hpp"

unsigned int sleep(unsigned int);

namespace pikachu{

struct JoinThreads{
    void operator()(std::tr1::shared_ptr<experis::Thread> a_thread)
    {
        a_thread->Join();
    }
};

void HardDistributePolicy::initilizedControllersMap(std::vector<std::tr1::shared_ptr<IController> >&a_controllers)
{
    for(std::vector<std::tr1::shared_ptr<IController> >::iterator itr = a_controllers.begin();
    itr!= a_controllers.end();++itr){
        HardDistributePolicy::srd_ptr_queue queue(new std::queue
        < std::pair<std::tr1::shared_ptr<IController>, std::tr1::shared_ptr<EventBase> > >());
        m_mapControllersPrivateQueues.insert(std::make_pair(*itr,queue));
        std::tr1::shared_ptr<experis::MutexWrapper> m(new experis::MutexWrapper());
        m_mutexesQueueMap.insert(std::make_pair(*itr,m));
    }
}

void HardDistributePolicy::initilizedThreads(size_t a_numofthreads, std::vector<std::tr1::shared_ptr<IController> >&a_controllers)
{
    for(size_t i = 0; i<a_numofthreads;++i){
        std::tr1::shared_ptr<ISender> sender(new SenderMvp());
        m_senders.push_back(sender);
        
        srd_ptr_queue queue = m_mapControllersPrivateQueues[(a_controllers[i])];
        std::tr1::shared_ptr<experis::MutexWrapper> mutexwrapper= m_mutexesQueueMap[(a_controllers[i])];

        std::tr1::shared_ptr<experis::common::Runable> run
        (new experis::common::AutoRunnableMemFuncThreeArg
        <HardDistributePolicy,std::tr1::shared_ptr<ISender>, srd_ptr_queue,std::tr1::shared_ptr<experis::MutexWrapper> >
        (*this,&HardDistributePolicy::workersAction, m_senders[i],queue,mutexwrapper));
        m_threads.push_back(std::tr1::shared_ptr<experis::Thread>(new experis::Thread(run)));
    }
}

void HardDistributePolicy::workersAction(std::tr1::shared_ptr<ISender> a_sender,
    srd_ptr_queue a_privatequeue,
    std::tr1::shared_ptr<experis::MutexWrapper> a_queuemutex)
{
    
    while(m_numOfEvents.Value()){
        experis::Locker locker(a_queuemutex);
        if(!a_privatequeue->empty()){
            std::tr1::shared_ptr<IController> controller = a_privatequeue->front().first;
            std::tr1::shared_ptr<EventBase>  event = a_privatequeue->front().second;
            
            a_sender->SendEvent(controller,event);
            a_privatequeue->pop();
            --m_numOfEvents;
        }
    }
}

HardDistributePolicy::HardDistributePolicy(size_t a_numofeventsfordis,std::vector<std::tr1::shared_ptr<IController> >& a_multieventtype)
:m_numOfEvents(a_numofeventsfordis)
{
    initilizedControllersMap(a_multieventtype);
    initilizedThreads(a_multieventtype.size(),a_multieventtype);
}

void HardDistributePolicy::Distribute(std::tr1::shared_ptr<IController> a_controller, std::tr1::shared_ptr<EventBase> a_event)
{
    PrivateQueuesMap::iterator itrqueue = m_mapControllersPrivateQueues.find(a_controller);
    QueueMutexesMap::iterator itrMutex = m_mutexesQueueMap.find(a_controller);
    if(itrqueue != m_mapControllersPrivateQueues.end() 
    && itrMutex != m_mutexesQueueMap.end()){
        experis::Locker lock(itrMutex->second);
        (*itrqueue).second->push(std::make_pair(a_controller,a_event));        
    }
    
}

void HardDistributePolicy::FinishDistribute()
{
    
    while(m_numOfEvents.Value()){
        //sleep(1);
    }
    std::for_each(m_threads.begin(),m_threads.end(),JoinThreads());
}

size_t  HardDistributePolicy::GetEventsLeft()const
{
    return m_numOfEvents.Value();
}

}//pikachu