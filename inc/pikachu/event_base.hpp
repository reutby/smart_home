#ifndef EVENT_BASE_H
#define EVENT_BASE_H
#include "time_stamp.hpp"
#include <string>
#include "location.hpp"
#include "event_types.hpp"
namespace pikachu{


class EventAttribute{
public: 
    enum AllBuikding{EVENT_ATT_ALL_FLOOERS = 10000};
    EventAttribute(const Location& location,EventTypes m_type );
    //~EventAttribute()// = default
    const EventTypes GetEventType()const;
    const Location& GetLocation()const;
private:
    Location m_location;
    EventTypes m_type;
};
class EventBase{

public:
    EventBase(const Location& location, EventTypes a_eventtype,size_t a_seqNumber);
    virtual ~EventBase();
    const TimeStamp& GetTimeStamp()const;
    const EventAttribute& GetEventAttribute()const;
    virtual void GetPayload(std::string& a_retpayload)const;
    size_t GetSeqNumber()const;
    void SetEnequeueSeq(size_t a_seq);
    size_t GetEnqueueSeq()const;


private:
    EventAttribute m_eventAttribute;
    TimeStamp m_timeStamp;
    size_t m_seqnumber;
    size_t m_enequenumber;
};

inline bool operator<(const EventBase&a_comparewith,const EventBase&a_compareto)
{
    if(a_comparewith.GetSeqNumber() < a_compareto.GetSeqNumber()){
        return true;
    }
    return false;
}
inline const Location& EventAttribute::GetLocation()const
{
    return m_location;
}
inline const EventTypes EventAttribute::GetEventType()const
{
    return m_type;
}

inline const EventAttribute&EventBase:: GetEventAttribute()const
{
    return m_eventAttribute;
}
inline const TimeStamp& EventBase::GetTimeStamp()const
{
    return m_timeStamp;
}

std::ostream& operator<<(std::ostream& is, const EventAttribute&a_comparewith);

bool operator==(const EventAttribute&a_comparewith,const EventAttribute&a_compareto);

bool operator<(const EventAttribute&a_comparewith,const EventAttribute&a_compareto);

}//pikachu

#endif//EVENT_BASE_H