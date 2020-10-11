#ifndef NOPRIVILEGETOPERFORMTHEOPERATION_H
#define NOPRIVILEGETOPERFORMTHEOPERATION_H
#include <exception>
#include <iostream>
namespace experis{
class NoPrivilegeToPerformTheOperation: public std::exception{
public:
   
    explicit NoPrivilegeToPerformTheOperation(const char* message)
    : msg_(message)
    {}
    explicit NoPrivilegeToPerformTheOperation(const std::string& message)
    : msg_(message)
    {}

    virtual ~NoPrivilegeToPerformTheOperation() throw (){}
    
    virtual const char* what() const throw (){
       return  msg_.c_str();
    }

protected:
    std::string  msg_;
};
}//experis

#endif //NOPRIVILEGETOPERFORMTHEOPERATION_H
