#ifndef IRECIVER_H
#define IRECIVER_H
#include <tr1/memory>
#include "event_base.hpp"
namespace pikachu{

class IReciver{
public:
    //IReciver()// = default
    virtual ~IReciver();
    virtual void ReciveEvent(const std::tr1::shared_ptr<EventBase> a_event) = 0;
};

}//pikachu

#endif//IRECIVER_H