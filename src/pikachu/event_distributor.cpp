#include <algorithm>
#include "event_distributor.hpp"
#include "auto_runnable_memfunc.hpp"
#include "hard_distribute_policy.hpp"
#include "easy_distribute_policy.hpp"
namespace pikachu{


struct JoinThreads{
    void operator()(std::tr1::shared_ptr<experis::Thread> a_thread)
    {
        a_thread->Join();
    }
};

struct InsertToMap{
InsertToMap(EventDistributer::ControllerPolicyMap& a_map, std::tr1::shared_ptr<IDistributePolicy> a_policy)
: m_map(a_map)
, m_distPolicy(a_policy)
{}
void operator ()(std::tr1::shared_ptr<IController> a_controller)
{
    m_map.insert(std::make_pair(a_controller,m_distPolicy));
}
EventDistributer::ControllerPolicyMap& m_map;
std::tr1::shared_ptr<IDistributePolicy> m_distPolicy;
};

EventDistributer::EventDistributer(size_t a_numberofthreads, const std::tr1::shared_ptr<ISubscriberSelector> a_selector, const std::tr1::shared_ptr<IDequeue> a_dequeue, size_t a_numberofeventdistrbute)
: m_subscriberSelector(a_selector)
, m_dequeue(a_dequeue)
, m_numberOfEventsForDistribute(a_numberofeventdistrbute)
{
    
}    

void EventDistributer::insertToMap(std::vector<std::tr1::shared_ptr<IController> > &a_controllers, std::tr1::shared_ptr<IDistributePolicy> a_policy)
{
    std::for_each(a_controllers.begin(),a_controllers.end(), InsertToMap(m_mapControlersDistpolicy,a_policy));
}

size_t EventDistributer::GetDistributerLeftCount()const
{
    return m_numberOfEventsForDistribute.Value();
}
EventDistributer::~EventDistributer()
{
}
void EventDistributer::initPolicyMap(size_t a_hardNumberofevents,size_t a_easyNumberofevents)
{
    std::vector<std::tr1::shared_ptr<IController> > multi, single;
    m_subscriberSelector->GetMultiAndSingleEventsSubscribers(multi,single);
    if(multi.empty() && single.empty()){
        throw NoControllersHaveBeenRegister("no controllers have been register!!");
    }
    size_t threadsnumber = single.size()/2;
    if(!threadsnumber){
        ++threadsnumber;
    }
    m_easyPolicy = std::tr1::shared_ptr<IDistributePolicy>(new EasyDistributePolicy(threadsnumber, a_easyNumberofevents,single));
    m_hardPolicy = std::tr1::shared_ptr<IDistributePolicy>(new HardDistributePolicy(a_hardNumberofevents,multi));
    
    insertToMap(multi,m_hardPolicy);
    insertToMap(single,m_easyPolicy);
}
void EventDistributer::StartDistributerEvents(size_t a_hardNumberofevents,size_t a_easyNumberofevents)
{
    initPolicyMap(a_hardNumberofevents,a_easyNumberofevents);
    std::tr1::shared_ptr<experis::common::Runable> r(new experis::common::AutoRunnableMemFunc<EventDistributer>
    (*this,&EventDistributer::dequeueEventAndSelectSubscriber));
    m_thread = std::tr1::shared_ptr<experis::Thread>(new experis::Thread(r));
}

void EventDistributer::StopDistributerEvents()
{
    //m_stopFlag.Set(true);
    experis::Locker locker(m_gaurd);
    m_hardPolicy->FinishDistribute();
    m_easyPolicy->FinishDistribute();
    m_thread->Join();
}

void EventDistributer::dequeueEventAndSelectSubscriber()
{
    while(m_numberOfEventsForDistribute.Value()){
        std::tr1::shared_ptr<EventBase> a = m_dequeue->Dequeue();
        if(a){
            std::vector<std::tr1::shared_ptr<IController> > subscribers;
            m_subscriberSelector->SelectSubscriber(a->GetEventAttribute(),subscribers);
            if(!subscribers.empty()){
                --m_numberOfEventsForDistribute;
                sendToSubscribers(subscribers,a);
            }
        }
    }
}

void EventDistributer::sendToSubscribers(std::vector<std::tr1::shared_ptr<IController> > 
&a_subscribers,const std::tr1::shared_ptr<EventBase> a_event)
{
    for(std::vector<std::tr1::shared_ptr<IController> >::iterator itr = a_subscribers.begin();itr!= a_subscribers.end();++itr)
    {
        EventDistributer::ControllerPolicyMap::iterator mapitr = m_mapControlersDistpolicy.find(*itr);
        if(mapitr!=m_mapControlersDistpolicy.end()){
            mapitr->second->Distribute(*itr,a_event);
        }
    }
}

}//pikachu