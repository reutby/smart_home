#ifndef MUTEX_ALREADY_LOCKED_H
#define MUTEX_ALREADY_LOCKED_H
#include <exception>
#include <iostream>
namespace experis{
class MutexAlreadyLocked: public std::exception{
public:
   
    explicit MutexAlreadyLocked(const char* message)
    : msg_(message)
    {}
    explicit MutexAlreadyLocked(const std::string& message)
    : msg_(message)
    {}

    virtual ~MutexAlreadyLocked() throw (){}
    
    virtual const char* what() const throw (){
       return  msg_.c_str();
    }

protected:
    std::string  msg_;
};
}//experis

#endif //MUTEX_ALREADY_LOCKED_H
