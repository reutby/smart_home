#ifndef TEMPERATURE_CHANGE_CONTROLLER_H
#define TEMPERATURE_CHANGE_CONTROLLER_H
#include "icontroller.hpp"

namespace pikachu{

class TemperatureChangeController : public IController{
public:
    TemperatureChangeController(const std::vector<EventAttribute> &a_Monitorlocations);
    void SubscribeToEvents(const std::tr1::shared_ptr<ISubscriberManager> &a_submng);
    void UnSubscribeToEvent(std::tr1::shared_ptr<ISubscriberManager> a_submng);
    const std::vector<EventAttribute>& GetEventAttribute()const;
    void GetEvent(const std::tr1::shared_ptr<EventBase> & a_event);
    size_t Size()const;
private:
    std::vector<EventAttribute> m_attributeEvents;
    std::vector<std::tr1::shared_ptr<EventBase> > m_reciveEvents;
};
}//pikachu

#endif//TEMPERATURE_CHANGE_CONTROLLER_H