#ifndef INSUFFICIENTMEMORYEXISTSTOINIT_H
#define INSUFFICIENTMEMORYEXISTSTOINIT_H
#include <exception>
#include <iostream>
namespace experis{
class InsufficientMemoryExistsToInit: public std::exception{
public:
   
    explicit InsufficientMemoryExistsToInit(const char* message)
    : msg_(message)
    {}
    explicit InsufficientMemoryExistsToInit(const std::string& message)
    : msg_(message)
    {}

    virtual ~InsufficientMemoryExistsToInit() throw (){}
    
    virtual const char* what() const throw (){
       return  msg_.c_str();
    }

protected:
    std::string  msg_;
};
}//experis

#endif //INSUFFICIENTMEMORYEXISTSTOINIT_H
