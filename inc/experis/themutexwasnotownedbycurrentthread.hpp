#ifndef THEMUTEXWASNOTOWNEDBYCURRENTTHREAD_H
#define THEMUTEXWASNOTOWNEDBYCURRENTTHREAD_H
#include <exception>
#include <iostream>
namespace experis{
class TheMutexWasNotOwnedByCurrentThread: public std::exception{
public:
   
    explicit TheMutexWasNotOwnedByCurrentThread(const char* message)
    : msg_(message)
    {}
    explicit TheMutexWasNotOwnedByCurrentThread(const std::string& message)
    : msg_(message)
    {}

    virtual ~TheMutexWasNotOwnedByCurrentThread() throw (){}
    
    virtual const char* what() const throw (){
       return  msg_.c_str();
    }

protected:
    std::string  msg_;
};
}//experis

#endif //THEMUTEXWASNOTOWNEDBYCURRENTTHREAD_H
