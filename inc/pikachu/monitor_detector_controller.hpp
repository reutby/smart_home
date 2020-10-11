#ifndef MONITOR_DETECTOR_CONTROLLER
#define MONITOR_DETECTOR_CONTROLLER
#include <queue>
#include <map>
#include <tr1/memory>
#include "location.hpp"
#include "icontroller.hpp"
#include "event_base.hpp"
#include "isubscriber_container.hpp"
#include "mutex.hpp"
namespace pikachu{

class MonitorDetectorController :public IController,  public std::tr1::enable_shared_from_this<MonitorDetectorController>{

public:
    MonitorDetectorController(const std::vector<EventAttribute>& a_Monitorlocations);
    void SubscribeToEvents(const std::tr1::shared_ptr<ISubscriberManager>a_submng);
    void GetEvent(const std::tr1::shared_ptr<EventBase> a_event);
    const std::vector<EventAttribute>& GetEventAttribute()const;
    void UnSubscribeToEvent(std::tr1::shared_ptr<ISubscriberManager> a_submng);
    
    //debug
    bool CheckQueueOrder();
    size_t Size();

private:
    typedef std::map<EventAttribute, std::queue<std::tr1::shared_ptr<EventBase> > > MapEventQueue;
    std::vector<EventAttribute> m_attributeEvents;
    MapEventQueue m_reciveEvents;
};

}//pikachu


#endif //MONITOR_DETECTOR_CONTROLLER