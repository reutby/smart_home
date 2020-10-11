#include "motion_detector_event.hpp"

namespace pikachu{

MotionDetectorEvent::MotionDetectorEvent(const std::string& a_room, size_t a_floor, size_t a_seqnum)
: EventBase(Location(a_room,a_floor), EVENT_MOTION_DETECTOR,a_seqnum)
{

}

void MotionDetectorEvent::GetPayload(std::string& a_retpayload)const
{

}

}//pikachu