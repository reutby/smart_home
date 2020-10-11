#include "event_base.hpp"
#include <iostream>
#include <sstream>
namespace pikachu{

EventAttribute::EventAttribute(const Location& a_location,EventTypes a_type )
: m_location(a_location)
, m_type(a_type) 
{

}

EventBase::EventBase(const Location& a_location, EventTypes a_eventtype,size_t a_seqnum)
: m_eventAttribute(a_location,a_eventtype)
, m_timeStamp()
, m_seqnumber(a_seqnum)
, m_enequenumber(0)
{

}

void EventBase::SetEnequeueSeq(size_t a_seq)
{
    m_enequenumber = a_seq;
}

size_t EventBase::GetEnqueueSeq()const
{
    return m_enequenumber;
}

size_t EventBase::GetSeqNumber()const
{
    return m_seqnumber;
}
bool operator==(const EventAttribute&a_comparewith,const EventAttribute&a_compareto)
{
    if(a_comparewith.GetLocation() == a_compareto.GetLocation() &&
    a_comparewith.GetEventType() == a_compareto.GetEventType())
    {
        return true;
    }
    return false;
}
std::ostream& operator<<(std::ostream& is, const EventAttribute&a_comparewith)
{
    is<<"room: " <<a_comparewith.GetLocation().GetRoom()<< "floor: " <<a_comparewith.GetLocation().GetFloor()<<"type: "<< a_comparewith.GetEventType()<<std::endl;
    return is;
}
bool operator<(const EventAttribute&a_comparewith,const EventAttribute&a_compareto)
{
    std::stringstream ss1,ss2;
    ss1<<a_comparewith.GetEventType()<<a_comparewith.GetLocation().GetFloor() <<
    a_comparewith.GetLocation().GetRoom();
    ss2<<a_compareto.GetEventType()<<a_compareto.GetLocation().GetFloor() <<
    a_compareto.GetLocation().GetRoom();
    return (ss1.str() < ss2.str()) ? true : false; 
}

EventBase::~EventBase()
{

}
void EventBase::GetPayload(std::string& a_retpayload)const
{
    
}


}//pikachu