#ifndef IENQUEUE_H
#define IENQUEUE_H
#include <tr1/memory>
#include "event_base.hpp"
namespace pikachu{

class IEnqueue{
public:
    //IEnqueue()//=default
    virtual void Enqueue(const std::tr1::shared_ptr<EventBase> a_event) = 0;
    virtual ~IEnqueue();
};


}//pikachu

#endif//IENQUEUE_H