#include "mvp_factory.hpp"
#include "monitor_detector_controller.hpp"
#include "motion_detector_sensor.hpp"
#include "device_agent.hpp"
namespace pikachu{

MvpFactory::MvpFactory()
{

}
MvpFactory::~MvpFactory()
{

}
static void createMoinitorDetectorSensorDevices(std::vector<std::tr1::shared_ptr<IDeviceAgent> >& a_devices,const Location& loacation, size_t a_numofevents)
{
    std::tr1::shared_ptr<ISensor> motiondetector1(new MotionDetectorSensor(loacation,a_numofevents));
    a_devices.push_back(std::tr1::shared_ptr<IDeviceAgent>(new DeviceAgent(DeviceAgent::DEVICE_PUBLISHER,motiondetector1,std::tr1::shared_ptr<IController>())));
}

static void createMoinitorDetectorControllerDevices(std::vector<std::tr1::shared_ptr<IDeviceAgent> >& a_devices, std::vector<EventAttribute> & a_atribute)
{
    std::tr1::shared_ptr<IController> controller1(new MonitorDetectorController(a_atribute));   
    a_devices.push_back(std::tr1::shared_ptr<IDeviceAgent>(new DeviceAgent(DeviceAgent::DEVICE_SUBSCRIBER,std::tr1::shared_ptr<ISensor>(),controller1)));
}

std::tr1::shared_ptr<IDeviceAgent> MvpFactory::CreateDevice()
{
    return std::tr1::shared_ptr<IDeviceAgent>();
}
void MvpFactory::simulation1(std::vector<std::tr1::shared_ptr<IDeviceAgent> >& a_devices)
{
    std::vector<EventAttribute> attribute;
    createMoinitorDetectorSensorDevices(a_devices,Location("room_a", 1),m_numOfEvent);
    EventAttribute e1(Location("room_a",1),EVENT_MOTION_DETECTOR);
    attribute.push_back(e1);
    createMoinitorDetectorControllerDevices(a_devices,attribute);

}


void MvpFactory::simulation2(std::vector<std::tr1::shared_ptr<IDeviceAgent> >& a_devices)
{
    std::vector<EventAttribute> attribute;
    createMoinitorDetectorSensorDevices(a_devices,Location("room_a", 1),m_numOfEvent);
    createMoinitorDetectorSensorDevices(a_devices,Location("room_b", 2),m_numOfEvent);
    EventAttribute e1(Location("room_a",1),EVENT_MOTION_DETECTOR);
    attribute.push_back(e1);
    createMoinitorDetectorControllerDevices(a_devices,attribute);
    attribute.clear();
    EventAttribute e2(Location("*",EventAttribute::EVENT_ATT_ALL_FLOOERS),EVENT_MOTION_DETECTOR);
    attribute.push_back(e2);
    createMoinitorDetectorControllerDevices(a_devices,attribute);
}
void MvpFactory::simulation3(std::vector<std::tr1::shared_ptr<IDeviceAgent> >& a_devices)
{
    std::vector<EventAttribute> attribute;
    createMoinitorDetectorSensorDevices(a_devices,Location("room_a", 1),m_numOfEvent);
    createMoinitorDetectorSensorDevices(a_devices,Location("room_b", 2),m_numOfEvent);
    EventAttribute e1(Location("room_a",1),EVENT_MOTION_DETECTOR);
    attribute.push_back(e1);
    createMoinitorDetectorControllerDevices(a_devices,attribute);
    attribute.clear();
    EventAttribute e2(Location("room_b", 2),EVENT_MOTION_DETECTOR);
    attribute.push_back(e2);
    createMoinitorDetectorControllerDevices(a_devices,attribute);
    attribute.clear();
    EventAttribute e3(Location("*",EventAttribute::EVENT_ATT_ALL_FLOOERS),EVENT_MOTION_DETECTOR);
    attribute.push_back(e3);
    createMoinitorDetectorControllerDevices(a_devices,attribute);
}

void MvpFactory::simulation4(std::vector<std::tr1::shared_ptr<IDeviceAgent> >& a_devices)
{    
    std::vector<EventAttribute> attribute;
    createMoinitorDetectorSensorDevices(a_devices,Location("room_a", 1),m_numOfEvent);
    createMoinitorDetectorSensorDevices(a_devices,Location("room_b", 2),m_numOfEvent);
    createMoinitorDetectorSensorDevices(a_devices,Location("room_c", 2),m_numOfEvent);
    createMoinitorDetectorSensorDevices(a_devices,Location("room_d", 4),m_numOfEvent);
    EventAttribute e1(Location("room_a",1),EVENT_MOTION_DETECTOR);
    attribute.push_back(e1);
    createMoinitorDetectorControllerDevices(a_devices,attribute);
    attribute.clear();
    EventAttribute e2(Location("*",2),EVENT_MOTION_DETECTOR);
    attribute.push_back(e2);
    createMoinitorDetectorControllerDevices(a_devices,attribute);
    attribute.clear();
    EventAttribute e3(Location("*",EventAttribute::EVENT_ATT_ALL_FLOOERS),EVENT_MOTION_DETECTOR);
    attribute.push_back(e3);
    createMoinitorDetectorControllerDevices(a_devices,attribute);
    attribute.clear();
    EventAttribute e4(Location("room_d",4),EVENT_MOTION_DETECTOR);
    EventAttribute e5(Location("*",2),EVENT_MOTION_DETECTOR);
    attribute.push_back(e4);
    createMoinitorDetectorControllerDevices(a_devices,attribute);    
    attribute.push_back(e5);
    createMoinitorDetectorControllerDevices(a_devices,attribute);        

}
void MvpFactory::CreateDevices(std::vector<std::tr1::shared_ptr<IDeviceAgent> >& a_devices,Simulation a_simulationNum)
{
    switch(a_simulationNum){
        case FACTORY_SIMULATION1:{
            simulation1(a_devices);
            break;
        }
        case FACTORY_SIMULATION2:{
            simulation2(a_devices);
            break;
        }
        case FACTORY_SIMULATION3:{
            simulation3(a_devices);
            break;
        }
        case FACTORY_SIMULATION4:{
            simulation4(a_devices);
            break;
        }
        default:
            break;
    }
}

}//pikachu