#ifndef MOTION_DETECTOR_EVENT_H
#define MOTION_DETECTOR_EVENT_H
#include "event_base.hpp"
namespace pikachu{

class MotionDetectorEvent : public EventBase{
public:
    
    MotionDetectorEvent(const std::string& a_room, size_t a_floor, size_t a_seqnum);
    void GetPayload(std::string& a_retpayload)const;  
};


}//pikachu


#endif//MOTION_DETECTOR_EVENT_H