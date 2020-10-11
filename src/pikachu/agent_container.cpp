#include "agent_container.hpp"
#include "mvp_factory.hpp"
#include <algorithm>
#include "device_agent.hpp"
namespace pikachu{


struct StopAgents{
    void operator()(std::tr1::shared_ptr<IDeviceAgent> device)
    {
        device->StopAgentActivity();
    }    
};

struct PublishOrSubscribed{
    PublishOrSubscribed(std::tr1::shared_ptr<IEnqueue> a_enqueue,std::tr1::shared_ptr<ISubscriberManager> a_submng)
    : m_enqueue(a_enqueue)
    , m_submng(a_submng)
    {}
    void operator()(std::tr1::shared_ptr<IDeviceAgent> device)
    {
        if(device->GetController()){
            device->GetController()->SubscribeToEvents(m_submng);
        }
        if(device->GetSensor()){
            std::tr1::shared_ptr<IReciver> reciver(new MvpReciver(m_enqueue));
            device->GetSensor()->PublishEvent(reciver);
        }
    }
    std::tr1::shared_ptr<IEnqueue> m_enqueue;
    std::tr1::shared_ptr<ISubscriberManager> m_submng;
};

AgentsContainer::AgentsContainer(const std::tr1::shared_ptr<IEnqueue> a_enqueue, const std::tr1::shared_ptr<ISubscriberManager> a_subscribermng)
: m_enqueue(a_enqueue)
, m_subscriberMng(a_subscribermng)
, m_factory(new MvpFactory())
{

}
std::tr1::shared_ptr<IDeviceAgent> AgentsContainer::CreateDeviceAgent()
{
    std::tr1::shared_ptr<IDeviceAgent> device = m_factory->CreateDevice();
    m_devices.push_back(device);
    return device;
}

void AgentsContainer::InitilizedAgent(std::tr1::shared_ptr<IDeviceAgent> a_device, const std::string &a_deviceId, const std::string & a_typename,const Location& a_Devicelocation, const std::string &a_config)
{
    
}

void AgentsContainer::RunAgents()
{
    std::for_each(m_devices.begin(),m_devices.end(), PublishOrSubscribed(m_enqueue,m_subscriberMng));
}
void AgentsContainer::CreateDevicesAgents(IFactory::Simulation a_simulation)
{
    m_factory->CreateDevices(m_devices,a_simulation);
}

void AgentsContainer::StopAgentsActivity()
{
    std::for_each(m_devices.begin(),m_devices.end(),StopAgents());
}

void AgentsContainer::GetDevices(std::vector<std::tr1::shared_ptr<IDeviceAgent> > &a_devices)
{
    a_devices = m_devices; 
}

}//pikachu