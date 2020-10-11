#include "device_agent.hpp"

namespace pikachu{

DeviceAgent::DeviceAgent(WorkType a_worktype,const std::tr1::shared_ptr<ISensor> &a_sensor,const std::tr1::shared_ptr<IController> &a_controller)
: m_sensor(a_sensor)
, m_controller(a_controller)
, m_details()
, m_workType(a_worktype)
{

}
DeviceAgent::~DeviceAgent()
{

}
void DeviceAgent::InitilizedDevice(const std::string &a_deviceId, const std::string & a_typename,const Location& a_Devicelocation, const std::string &a_config)
{
    m_details.m_deviceId.assign(a_deviceId);
    m_details.m_type.assign(a_typename);
    m_details.m_location = a_Devicelocation;
    m_details.m_config.assign(a_config);
}

std::tr1::shared_ptr<ISensor> DeviceAgent::GetSensor()
{
    return m_sensor;
}
std::tr1::shared_ptr<IController> DeviceAgent::GetController()
{
    return m_controller;
}

void DeviceAgent::StopAgentActivity()
{
    if(m_sensor){
        m_sensor->WaitForFinishingActivity();
        
    }
}
}//pikachu