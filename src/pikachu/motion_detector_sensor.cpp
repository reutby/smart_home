#include "motion_detector_sensor.hpp"
#include "auto_runnable_memfunc.hpp"
#include "motion_detector_event.hpp"
namespace pikachu{

MotionDetectorSensor::MotionDetectorSensor(const Location& a_location,size_t a_nmberofevent)
: m_location(a_location)
, m_eventNum(a_nmberofevent)
, m_thread()
{

}


void MotionDetectorSensor::generateEvents(std::tr1::shared_ptr<IReciver> a_reciver)
{
    for(size_t i=0; i<m_eventNum;++i)
    {
        std::tr1::shared_ptr<EventBase> event(new MotionDetectorEvent(m_location.GetRoom(),m_location.GetFloor(),i));
        a_reciver->ReciveEvent(event);
    }
}
void MotionDetectorSensor::PublishEvent(std::tr1::shared_ptr<IReciver> a_reciver)
{
    std::tr1::shared_ptr<experis::common::Runable> 
            func(new experis::common::AutoRunnableMemFuncOneArg<MotionDetectorSensor, 
            std::tr1::shared_ptr<IReciver> >(*this,&MotionDetectorSensor::generateEvents,a_reciver));
    m_thread = std::tr1::shared_ptr<experis::Thread>(new experis::Thread(func));
}

void MotionDetectorSensor::WaitForFinishingActivity()
{ 
    m_thread->Join();
    //will be immplememt when changing to infinitloop
}
MotionDetectorSensor::~MotionDetectorSensor()
{
}
}//pikachu