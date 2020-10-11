#ifndef IDEVICE_AGENT_H
#define IDEVICE_AGENT_H
#include <string>
#include <vector>
#include "uncopyable.hpp"
#include "location.hpp"
#include "isensor.hpp"
#include "icontroller.hpp"

namespace pikachu{

class IDeviceAgent : private experis::UnCopyable{
public:  

    virtual ~IDeviceAgent();
    virtual void InitilizedDevice(const std::string &a_deviceId, const std::string & a_typename,const Location& a_Devicelocation, const std::string &a_config)=0;
    virtual std::tr1::shared_ptr<ISensor> GetSensor() = 0;
    virtual std::tr1::shared_ptr<IController> GetController() = 0; 
    virtual void StopAgentActivity() = 0;   
};

}//pikachu

#endif//IDEVICE_AGENT_H