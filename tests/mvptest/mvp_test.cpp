#include "mu_test.h"
#include <sstream>
#include "event_queue.hpp"
#include "motion_detector_sensor.hpp"
#include "mvpreciver.hpp"
#include "monitor_detector_controller.hpp"
#include "event_distributor.hpp"
#include "sender_mvp.hpp"
#include "smart_home_system.hpp"
#include <unistd.h>
#include "device_agent.hpp"
#include <algorithm>
using namespace experis;
using namespace pikachu;

UNIT(recive_flow_fromsensor_to_queue)
    const size_t numberofevents =1000000;
    std::tr1::shared_ptr<IEventQueue> queue(new EventQueue());
    {
        std::tr1::shared_ptr<IReciver> reciver(new MvpReciver(queue));
        std::tr1::shared_ptr<ISensor> motiondetector(new MotionDetectorSensor(Location("room_a", 2),1000000));
        motiondetector->PublishEvent(reciver);
        motiondetector->WaitForFinishingActivity();
    }
    ASSERT_EQUAL(queue->Size(),numberofevents);
    END_UNIT

static void InsertAttribute(std::vector<EventAttribute>& a_vec, const Location* a_location, const EventTypes* a_events)
{
    const size_t sizeLocationArray = 3;
    const size_t sizeEventAttArray = 2;
    for(size_t i = 0; i<sizeLocationArray; ++i){
        for(size_t j= 0; j<sizeEventAttArray; ++j)
        {
            EventAttribute at(a_location[i],a_events[j]);
            a_vec.push_back(at);
        }
    }
    
}
UNIT(subscriber_flow_fromcontroller_to_subscribercontainer)
    
    std::vector<EventAttribute> vec;
    const Location locations[3] ={Location("room_a",1),Location("room_b",2), Location("room_c",3)};
    const EventTypes eventstypes[2] ={EVENT_MOTION_DETECTOR,EVENT_NOISE_LEVEL};
    InsertAttribute(vec, locations, eventstypes);
    ASSERT_EQUAL(vec.size(),6);
    std::tr1::shared_ptr<IController> controller(new MonitorDetectorController(vec));
    std::tr1::shared_ptr<IController> controller2(new MonitorDetectorController(vec));   
    std::tr1::shared_ptr<ISubscriberContainer> subscribersds(new SubscribersContainer());
    controller->SubscribeToEvents(subscribersds);
    controller2->SubscribeToEvents(subscribersds);
    ASSERT_EQUAL(subscribersds->Size(),12);

END_UNIT

UNIT(Unsubscriber_flow_fromcontroller_to_subscribercontainer)
    std::vector<EventAttribute> vec;
    const Location locations[3] ={Location("room_a",1),Location("room_b",2), Location("room_c",3)};
    const EventTypes eventstypes[2] ={EVENT_MOTION_DETECTOR,EVENT_NOISE_LEVEL};
    InsertAttribute(vec, locations, eventstypes);
    ASSERT_EQUAL(vec.size(),6);
    std::tr1::shared_ptr<IController> controller(new MonitorDetectorController(vec));   
    std::tr1::shared_ptr<ISubscriberContainer> subscribersds(new SubscribersContainer());
    controller->SubscribeToEvents(subscribersds);
    ASSERT_EQUAL(subscribersds->Size(),6);
    controller->UnSubscribeToEvent(subscribersds);
    ASSERT_EQUAL(subscribersds->Size(),0);
    
END_UNIT

UNIT(distribution_flow_1distributedthreads_1_controller_1sensor_1M_events)
    
    //subscribed
    std::vector<EventAttribute> vec;
    vec.push_back(EventAttribute(Location("room_b",2),EVENT_MOTION_DETECTOR));
    std::tr1::shared_ptr<IController> controller(new MonitorDetectorController(vec));   
    std::tr1::shared_ptr<ISubscriberContainer> subscribersds(new SubscribersContainer());
    controller->SubscribeToEvents(subscribersds);
    ASSERT_EQUAL(subscribersds->Size(),1);
    //sendevents
    const size_t numberofevents =1000000;

    std::tr1::shared_ptr<ISensor> motiondetector(new MotionDetectorSensor(Location("room_b", 2),numberofevents));
    std::tr1::shared_ptr<ISender> sender(new SenderMvp());
    std::tr1::shared_ptr<IEventQueue> queue(new EventQueue());
    std::tr1::shared_ptr<IReciver> reciver(new MvpReciver(queue));
    EventDistributer eventdist(1,subscribersds,queue,numberofevents);
    
    motiondetector->PublishEvent(reciver);
    eventdist.StartDistributerEvents(0,1000000);
    while(eventdist.GetDistributerLeftCount()){}
    queue->Stop();
    eventdist.StopDistributerEvents();
    motiondetector->WaitForFinishingActivity();
    ASSERT_EQUAL(controller->Size(),numberofevents);

    //ASSERT_EQUAL(queue->Size(),numberofevents);
END_UNIT

UNIT(distribution_flow_1distributedthreads_2controller_2sensors_1M_per_controller)
    
    //subscribed
    std::vector<EventAttribute> vec1;
    std::vector<EventAttribute> vec2;
    
    EventAttribute e1(Location("room_b",2),EVENT_MOTION_DETECTOR);
    EventAttribute e2(Location("room_a",1),EVENT_MOTION_DETECTOR);
    
    vec1.push_back(e1);
    vec2.push_back(e2);
    std::tr1::shared_ptr<IController> controller1(new MonitorDetectorController(vec1));
    std::tr1::shared_ptr<IController> controller2(new MonitorDetectorController(vec2));
    std::tr1::shared_ptr<ISubscriberContainer> subscribersds(new SubscribersContainer());
    controller1->SubscribeToEvents(subscribersds);
    controller2->SubscribeToEvents(subscribersds);
    ASSERT_EQUAL(subscribersds->Size(),2);
    //sendevents
    const size_t numberofevents =1000000;

    std::tr1::shared_ptr<IEventQueue> queue(new EventQueue());
    std::tr1::shared_ptr<IReciver> reciver(new MvpReciver(queue));
    std::tr1::shared_ptr<ISensor> motiondetector1(new MotionDetectorSensor(Location("room_b", 2),numberofevents));
    std::tr1::shared_ptr<ISensor> motiondetector2(new MotionDetectorSensor(Location("room_a", 1),numberofevents));        
    std::tr1::shared_ptr<ISender> sender(new SenderMvp());
    EventDistributer eventdist(1,subscribersds,queue,numberofevents*2);
    motiondetector1->PublishEvent(reciver);
    motiondetector2->PublishEvent(reciver);
    eventdist.StartDistributerEvents(0,2000000);
    while(eventdist.GetDistributerLeftCount()){}
    queue->Stop();
    eventdist.StopDistributerEvents();
    motiondetector1->WaitForFinishingActivity();
    motiondetector2->WaitForFinishingActivity();

    ASSERT_EQUAL(controller1->Size(),numberofevents);
    ASSERT_EQUAL(controller2->Size(),numberofevents);

    //ASSERT_EQUAL(queue->Size(),numberofevents);
END_UNIT

UNIT(mvp01_all_package_test_250000events_simulation1_distrubute_250000)

    std::vector<EventAttribute> vec;
    SmartHomeSystem app(250000,IFactory::FACTORY_SIMULATION1);
    app.RunApplication();
    app.WaitForFinishing();
    std::vector<std::tr1::shared_ptr<IDeviceAgent> > a_agents;
    app.GetDevices(a_agents);
    std::vector<std::tr1::shared_ptr<IController> > testvec;
    std::vector<std::tr1::shared_ptr<IDeviceAgent> >::iterator itr = a_agents.begin();
    for(;itr!= a_agents.end();++itr)
    if((*itr)->GetController()){ 
        testvec.push_back((*itr)->GetController());
    }   
    ASSERT_EQUAL(testvec.size(),1);
    ASSERT_EQUAL(testvec[0]->Size(),250000);
    if(testvec[0]->CheckQueueOrder())
    {
        ASSERT_PASS();
    }
    else{
        ASSERT_FAIL("NO FIFO!");
    }
    
END_UNIT

UNIT(mvp01_all_package_test_500000events_simulation2_distrubute_750000)

 std::vector<EventAttribute> vec;
    SmartHomeSystem app(500000,IFactory::FACTORY_SIMULATION2);
    app.RunApplication();
    app.WaitForFinishing();
    std::vector<std::tr1::shared_ptr<IDeviceAgent> > a_agents;
    app.GetDevices(a_agents);
    std::vector<std::tr1::shared_ptr<IController> > testvec;
    std::vector<std::tr1::shared_ptr<IDeviceAgent> >::iterator itr = a_agents.begin();
    for(;itr!= a_agents.end();++itr)
    if((*itr)->GetController()){ 
        testvec.push_back((*itr)->GetController());
    }   
    ASSERT_EQUAL(testvec.size(),2);

    ASSERT_EQUAL(testvec[0]->Size(),250000);
    ASSERT_EQUAL(testvec[1]->Size(),500000);    
    
    for(std::vector<std::tr1::shared_ptr<IController> >::iterator itr = testvec.begin();
    itr!= testvec.end();++itr){
        if((*itr)->CheckQueueOrder()){
            ASSERT_PASS();
        }
        else{
           ASSERT_FAIL("NO FIFO!"); 
        }
    }
  
END_UNIT

UNIT(mvp01_all_package_test_500000events_simulation3_distrubute_1000000)

    
 std::vector<EventAttribute> vec;
    SmartHomeSystem app(500000,IFactory::FACTORY_SIMULATION3);
    app.RunApplication();
    app.WaitForFinishing();
    std::vector<std::tr1::shared_ptr<IDeviceAgent> > a_agents;
    app.GetDevices(a_agents);
    std::vector<std::tr1::shared_ptr<IController> > testvec;
    std::vector<std::tr1::shared_ptr<IDeviceAgent> >::iterator itr = a_agents.begin();
    for(;itr!= a_agents.end();++itr)
    if((*itr)->GetController()){ 
        testvec.push_back((*itr)->GetController());
    }   
    ASSERT_EQUAL(testvec.size(),3);

    ASSERT_EQUAL(testvec[0]->Size(),250000);
    ASSERT_EQUAL(testvec[1]->Size(),250000);    
    ASSERT_EQUAL(testvec[2]->Size(),500000);    
    for(std::vector<std::tr1::shared_ptr<IController> >::iterator itr = testvec.begin();
    itr!= testvec.end();++itr){
        if((*itr)->CheckQueueOrder()){
            ASSERT_PASS();
        }
        else{
           ASSERT_FAIL("NO FIFO!"); 
        }
    }

  

END_UNIT

UNIT(mvp01_all_package_test_1000000events_simulation4_distrubute_2750000)
    std::vector<EventAttribute> vec;
    SmartHomeSystem app(1000000,IFactory::FACTORY_SIMULATION4);
    app.RunApplication();
    app.WaitForFinishing();
    std::vector<std::tr1::shared_ptr<IDeviceAgent> > a_agents;
    app.GetDevices(a_agents);
    std::vector<std::tr1::shared_ptr<IController> > testvec;
    std::vector<std::tr1::shared_ptr<IDeviceAgent> >::iterator itr = a_agents.begin();
    for(;itr!= a_agents.end();++itr)
    if((*itr)->GetController()){ 
        testvec.push_back((*itr)->GetController());
    }   
    ASSERT_EQUAL(testvec.size(),5);

    ASSERT_EQUAL(testvec[0]->Size(),250000);
    ASSERT_EQUAL(testvec[1]->Size(),500000);    
    ASSERT_EQUAL(testvec[2]->Size(),1000000);
    ASSERT_EQUAL(testvec[3]->Size(),250000);
    ASSERT_EQUAL(testvec[4]->Size(),750000);    
    for(std::vector<std::tr1::shared_ptr<IController> >::iterator itr = testvec.begin();
    itr!= testvec.end();++itr){
        if((*itr)->CheckQueueOrder()){
            ASSERT_PASS();
        }
        else{
           ASSERT_FAIL("NO FIFO!"); 
        }
    }

END_UNIT

TEST_SUITE(mvp  smart_home mu test)
// TEST(recive_flow_fromsensor_to_queue)
// TEST(subscriber_flow_fromcontroller_to_subscribercontainer)
// TEST(Unsubscriber_flow_fromcontroller_to_subscribercontainer)
//TEST(distribution_flow_1distributedthreads_1_controller_1sensor_1M_events)
//TEST(distribution_flow_1distributedthreads_2controller_2sensors_1M_per_controller)
TEST(mvp01_all_package_test_250000events_simulation1_distrubute_250000)
TEST(mvp01_all_package_test_500000events_simulation2_distrubute_750000)
TEST(mvp01_all_package_test_500000events_simulation3_distrubute_1000000)
TEST(mvp01_all_package_test_1000000events_simulation4_distrubute_2750000)
END_SUITE

//need to add tests that check fifo for "hard" policy controllers ,
//i have at mine what to do
