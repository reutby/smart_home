#ifndef ADEADLOCKWASDDETECTED_H
#define ADEADLOCKWASDDETECTED_H
#include <exception>
#include <iostream>
namespace experis{
class ADeadlockWasdDetected: public std::exception{
public:
   
    explicit ADeadlockWasdDetected(const char* message)
    : msg_(message)
    {}
    explicit ADeadlockWasdDetected(const std::string& message)
    : msg_(message)
    {}

    virtual ~ADeadlockWasdDetected() throw (){}
    
    virtual const char* what() const throw (){
       return  msg_.c_str();
    }

protected:
    std::string  msg_;
};
}//experis

#endif //ADEADLOCKWASDDETECTED_H
