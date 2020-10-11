#ifndef ISUBSCRIBER_CONTAINER_H
#define ISUBSCRIBER_CONTAINER_H
#include <string>
#include "uncopyable.hpp"
#include "isubscriber_manager.hpp"
#include "isubscriber_selector.hpp"
namespace pikachu{

class ISubscriberContainer : public ISubscriberManager, public ISubscriberSelector, private experis::UnCopyable{
public:
//for debug
    virtual size_t Size()const = 0;
    virtual ~ISubscriberContainer();
};
}//pikachu

#endif//ISUBSCRIBER_CONTAINER_H