#ifndef AGENT_CONTAINER_H
#define AGENT_CONTAINER_H
#include "mvpreciver.hpp"
#include "ifactory.hpp"
#include "ienqueue.hpp"
#include "isubscriber_manager.hpp"
namespace pikachu{

class AgentsContainer{
public:
    AgentsContainer(const std::tr1::shared_ptr<IEnqueue> a_enqueue, const std::tr1::shared_ptr<ISubscriberManager> a_subscribermng);    
    //will be userd in mvp2 using the configorator module 
    std::tr1::shared_ptr<IDeviceAgent> CreateDeviceAgent();
    void InitilizedAgent(std::tr1::shared_ptr<IDeviceAgent> a_device, const std::string &a_deviceId, const std::string & a_typename,const Location& a_Devicelocation, const std::string &a_config);
    //without cinfigorator - hard coded creation of agents, spacify in mvp fcatory hpp
    void CreateDevicesAgents(IFactory::Simulation a_simulation);
    void RunAgents();
    void StopAgentsActivity();
    //for debug
    void GetDevices(std::vector<std::tr1::shared_ptr<IDeviceAgent> >& m_devices);
private:
    std::tr1::shared_ptr<IEnqueue> m_enqueue;
    std::tr1::shared_ptr<ISubscriberManager> m_subscriberMng;
    std::tr1::shared_ptr<IFactory> m_factory;
    std::vector<std::tr1::shared_ptr<IDeviceAgent> > m_devices;
};

}//pikachu

#endif//AGENT_CONTAINER_H