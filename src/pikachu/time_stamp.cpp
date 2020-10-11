#include "time_stamp.hpp"
#include <time.h>

namespace pikachu{
experis::AtomicValue<size_t> TimeStamp:: m_timestamp(0);

TimeStamp::TimeStamp()
{
    ++m_timestamp;
}
//which event is older 
bool operator<(const TimeStamp& a_comparewith,const TimeStamp& a_comparto)
{
    return (a_comparewith.m_timestamp.Value()<a_comparto.m_timestamp.Value());
}


size_t TimeStamp::GetTimeStamp()
{
    return m_timestamp.Value();
}
}//pikachu