#include "smart_home_system.hpp"

namespace pikachu{

SmartHomeSystem::SmartHomeSystem(size_t a_eventsTodistribute,IFactory::Simulation a_simulation)
: m_subscribersContainer(new SubscribersContainer())
, m_eventQueue(new EventQueue())
, m_agents(m_eventQueue,m_subscribersContainer)
, m_eventDistributer(1,m_subscribersContainer,m_eventQueue,a_eventsTodistribute)
, m_simulation(a_simulation)
{
    m_agents.CreateDevicesAgents(m_simulation);
    //m_agents.InitilizedAgent()
}

void SmartHomeSystem::RunApplication()
{
    m_agents.RunAgents();
    switch(m_simulation){
        case IFactory::FACTORY_SIMULATION1:{
            m_eventDistributer.StartDistributerEvents(0,250000);
            break;
        }
        case IFactory::FACTORY_SIMULATION2:{
            m_eventDistributer.StartDistributerEvents(500000,250000); 
            break;           
        }
        case IFactory::FACTORY_SIMULATION3:{
            m_eventDistributer.StartDistributerEvents(500000,500000); 
            break;           
        }
        case IFactory::FACTORY_SIMULATION4:{
            m_eventDistributer.StartDistributerEvents(2250000, 500000); 
            break;
        }
    }
}

void SmartHomeSystem::WaitForFinishing()
{
    while (m_eventDistributer.GetDistributerLeftCount() > 0)
    {
        //std::cout<<m_eventQueue->Size()<<std::endl;
      //  std::cout<<"queue size"<<m_eventQueue->Size()<<" distributeeventsleft: "<<m_eventDistributer.GetDistributerLeftCount()<<std::endl;          
    }
    m_eventDistributer.StopDistributerEvents();
    m_agents.StopAgentsActivity();
    m_eventQueue->Stop();
}

void SmartHomeSystem::StopAplication()
{
    m_eventQueue->Stop();
    m_eventDistributer.StopDistributerEvents();
    m_agents.StopAgentsActivity();
}
void SmartHomeSystem::GetDevices(std::vector<std::tr1::shared_ptr<IDeviceAgent> >& a_devices)
{
    m_agents.GetDevices(a_devices);
}

SmartHomeSystem::~SmartHomeSystem()
{
    //StopAplication();
}
}//pikachu