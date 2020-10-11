#include <algorithm>
#include "easy_distribute_policy.hpp"
#include "auto_runnable_memfunc.hpp"
#include "sender_mvp.hpp"
#include "atomicvalue.hpp"
#include <unistd.h>
namespace pikachu{


struct JoinThreads{
    void operator()(std::tr1::shared_ptr<experis::Thread> a_thread)
    {
        a_thread->Join();
    }
};
void EasyDistributePolicy::initilizedThreads(size_t a_numofthreads)
{
    for(size_t i = 0; i<a_numofthreads;++i){
        std::tr1::shared_ptr<ISender> sender(new SenderMvp());
        m_senders.push_back(sender);
        std::tr1::shared_ptr<experis::common::Runable> run(new experis::common::AutoRunnableMemFuncOneArg<EasyDistributePolicy,std::tr1::shared_ptr<ISender> >
        (*this,&EasyDistributePolicy::workerDistribute,m_senders[i]));
        m_threads.push_back(std::tr1::shared_ptr<experis::Thread>(new experis::Thread(run)));
    }
}

void EasyDistributePolicy::initilizedControllersMap( std::vector<std::tr1::shared_ptr<IController> >&a_controllers)
{
    for(std::vector<std::tr1::shared_ptr<IController> >::iterator itr = a_controllers.begin();itr!= a_controllers.end();
    ++itr){
        m_mapControllersWindows.insert(std::make_pair(*itr,std::make_pair(ptr_pq(),0)));
        m_mapQueuesMutexs.insert(std::make_pair(*itr,std::tr1::shared_ptr<experis::MutexWrapper>(new experis::MutexWrapper())));    

    }
}

void EasyDistributePolicy::pqueueEmptyAction(ptr_pq&a_pq,
std::pair< std::tr1::shared_ptr<IController>, std::tr1::shared_ptr<EventBase> > &a_pair,size_t& a_index, std::tr1::shared_ptr<ISender> a_sander)
{
    if(a_pair.second->GetEnqueueSeq() == a_index){
        a_sander->SendEvent(a_pair.first,a_pair.second);
        ++a_index;  
    }
    else if(a_pair.second->GetEnqueueSeq()){ 
        a_pq.push(a_pair.second);                    
    }
}
void EasyDistributePolicy::pqNotEmptyAction(ptr_pq&a_pq,std::pair< std::tr1::shared_ptr<IController>, std::tr1::shared_ptr<EventBase> > &a_pair,size_t& a_index, std::tr1::shared_ptr<ISender> a_sander)
{
    
    if(a_pair.second->GetEnqueueSeq() == a_index){
        a_sander->SendEvent(a_pair.first,a_pair.second);    
        ++a_index;
    }
    else{
        a_pq.push(a_pair.second);
    }
    std::tr1::shared_ptr<EventBase> top = a_pq.top();
    while(top->GetEnqueueSeq() == a_index){
        a_pq.pop();
        a_sander->SendEvent(a_pair.first,top);
        ++a_index;
        top = a_pq.top();
    }
}   
EasyDistributePolicy::EasyDistributePolicy(size_t a_threadnum, size_t a_numofeventsfordis,std::vector<std::tr1::shared_ptr<IController> >& a_singleeventtype)
: m_numOfEvents(a_numofeventsfordis)
{
    initilizedControllersMap(a_singleeventtype);
    initilizedThreads(a_threadnum);
}

void EasyDistributePolicy::Distribute(std::tr1::shared_ptr<IController> a_controller, std::tr1::shared_ptr<EventBase> a_event)
{
    m_queue.Enqueue(std::make_pair(a_controller,a_event));
}


size_t EasyDistributePolicy::GetEventsLeft()const
{
    return m_numOfEvents.Value();
}

void EasyDistributePolicy::FinishDistribute()
{
    //add condition var;
    while(m_numOfEvents.Value()){
        
    }
    m_queue.Stop();
    std::for_each(m_threads.begin(),m_threads.end(),JoinThreads());
}

void EasyDistributePolicy::workerDistribute(std::tr1::shared_ptr<ISender> a_sander)
{
    typedef std::pair< std::tr1::shared_ptr<IController>, std::tr1::shared_ptr<EventBase> > ControllersEventsPair; 
    while(m_numOfEvents.Value()){
        ControllersEventsPair pair;
        m_queue.Dequeue(pair);
        if(pair.first){
            WindowsMutexes::iterator itrmutexs = m_mapQueuesMutexs.find(pair.first);
            ControllersWindows::iterator itrController = m_mapControllersWindows.find(pair.first);
            if(itrmutexs == m_mapQueuesMutexs.end()){
                continue;
            }
            experis::Locker locker((*itrmutexs).second);    
            ptr_pq& pq = (*itrController).second.first;
            size_t& index = (*itrController).second.second;
            if(pq.empty()){
                pqueueEmptyAction(pq,pair,index,a_sander);
            }
            else{
                pqNotEmptyAction(pq,pair,index,a_sander);
            }
            --m_numOfEvents;
        }
    }
}
}//pikachu