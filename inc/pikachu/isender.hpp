#ifndef ISENDER_H
#define ISENDER_H
#include "event_base.hpp"
#include <tr1/memory>
namespace pikachu{
class IController;
class ISender{

public:
    virtual void SendEvent(std::tr1::shared_ptr<IController> a_controller,const std::tr1::shared_ptr<EventBase> a_event) = 0;
    virtual ~ISender();
};

}//pikachu

#endif//ISENDER_H