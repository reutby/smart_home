#ifndef ISUBSCRIBER_MANAGER_H
#define ISUBSCRIBER_MANAGER_H
#include "event_base.hpp"
#include <tr1/memory>
namespace pikachu{

class IController;
class ISubscriberManager{
public:
    virtual void InsertSubscriber(const EventAttribute& a_attribute,const std::tr1::shared_ptr<IController> a_device) = 0;
    virtual bool RemoveSubscriber(const EventAttribute& a_attribute,const std::tr1::shared_ptr<IController> a_device) = 0;
    virtual ~ISubscriberManager();
};

}//pikachu

#endif//ISUBSCRIBER_MANAGER_H