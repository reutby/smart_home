#include "monitor_detector_controller.hpp"
#include <algorithm>
#include <iostream>
#include <unistd.h>
namespace pikachu{

struct Subscribed{
    Subscribed(const std::tr1::shared_ptr<ISubscriberManager> a_subscribermng, const std::tr1::shared_ptr<IController> a_controller)
    :m_subscribermng(a_subscribermng)
    ,m_controller(a_controller)
    {}
    void operator()(const EventAttribute& a_event)
    {
        m_subscribermng->InsertSubscriber(a_event,m_controller);
    }
    std::tr1::shared_ptr<ISubscriberManager> m_subscribermng;
    std::tr1::shared_ptr<IController> m_controller;
};

struct UnSubscribed{
    UnSubscribed(const std::tr1::shared_ptr<ISubscriberManager>  a_subscribermng, const std::tr1::shared_ptr<IController> a_controller)
    :m_subscribermng(a_subscribermng)
    ,m_controller(a_controller)
    {}
    void operator()(const EventAttribute& a_event)
    {
        m_subscribermng->RemoveSubscriber(a_event,m_controller);
    }
    std::tr1::shared_ptr<ISubscriberManager> m_subscribermng;
    std::tr1::shared_ptr<IController> m_controller;
};

MonitorDetectorController::MonitorDetectorController(const std::vector<EventAttribute> &a_Monitorlocations)
: m_attributeEvents(a_Monitorlocations)
{

}

void MonitorDetectorController::UnSubscribeToEvent(const std::tr1::shared_ptr<ISubscriberManager> a_submng)
{
    std::tr1::shared_ptr<MonitorDetectorController> p = shared_from_this();
    std::for_each(m_attributeEvents.begin(),m_attributeEvents.end(),UnSubscribed(a_submng,p));
}

void MonitorDetectorController::SubscribeToEvents(const std::tr1::shared_ptr<ISubscriberManager> a_submng)
{
    std::tr1::shared_ptr<MonitorDetectorController> p = shared_from_this();
    std::for_each(m_attributeEvents.begin(),m_attributeEvents.end(),Subscribed(a_submng,p));
    
}
void MonitorDetectorController::GetEvent(const std::tr1::shared_ptr<EventBase> a_event)
{
    MapEventQueue::iterator itr= m_reciveEvents.find(a_event->GetEventAttribute());
    if(itr!= m_reciveEvents.end()){
        itr->second.push(a_event);
    }
    else{
        m_reciveEvents.insert(std::make_pair(a_event->GetEventAttribute(), std::queue<std::tr1::shared_ptr<EventBase> >()));
        m_reciveEvents.operator[](a_event->GetEventAttribute()).push(a_event);
    }
}

size_t MonitorDetectorController::Size()
{
    size_t sum = 0;
    for (MapEventQueue::iterator itr = m_reciveEvents.begin();itr!= m_reciveEvents.end();
    ++itr){
        sum+=itr->second.size();
    }
    return sum;
}
const std::vector<EventAttribute>& MonitorDetectorController::GetEventAttribute()const
{
    return m_attributeEvents; 
}

bool MonitorDetectorController::CheckQueueOrder()
{
    for(MapEventQueue::iterator itr = m_reciveEvents.begin();itr!= m_reciveEvents.end();++itr){
        std::tr1::shared_ptr< EventBase> comparewith = itr->second.front();
        while(itr->second.size() > 1){
            itr->second.pop();
            std::tr1::shared_ptr< EventBase> a_compareto = itr->second.front();
            if(a_compareto->GetEnqueueSeq() != comparewith->GetEnqueueSeq() + 1){
                return false;
            }
            comparewith = a_compareto;
        }
    }
    return true;
}
}//pikachu