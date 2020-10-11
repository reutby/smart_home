#include "temparture_change_event.hpp"
#include <sstream>
namespace pikachu{

TempartureChangeEvent::TempartureChangeEvent(const std::string& a_room, size_t a_floor,double a_currentTemp, bool a_isUp)
: EventBase(EVENT_TEMPARTURE_CHANGE,a_room,a_floor)
, m_currentTemp(a_currentTemp)
, m_isUp(a_isUp)
{

}

void TempartureChangeEvent::GetPayload(std::string& a_retpayload)const
{
    std::stringstream ss;
    ss << "{current_temp: " << m_currentTemp <<"," << "is_temparture_up: " << m_isUp<<"}";
    a_retpayload.assign(ss.str());
}

}//pikachu