#ifndef QUEUE_IS_CLOSE_H
#define QUEUE_IS_CLOSE_H
#include <exception>
#include <iostream>
namespace experis{
class QueueIsClose: public std::exception{
public:
   
    explicit QueueIsClose(const char* message)
    : msg_(message)
    {}
    explicit QueueIsClose(const std::string& message)
    : msg_(message)
    {}

    virtual ~QueueIsClose() throw (){}
    
    virtual const char* what() const throw (){
       return  msg_.c_str();
    }

protected:
    std::string  msg_;
};
}//experis

#endif //QUEUE_IS_CLOSE_H
