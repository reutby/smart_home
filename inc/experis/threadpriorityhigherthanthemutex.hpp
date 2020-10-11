#ifndef THREADPRIORITYHIGHERTHENTHEMUTEX_H
#define THREADPRIORITYHIGHERTHENTHEMUTEX_H
#include <exception>
#include <iostream>
namespace experis{
class ThreadPriorityHigherThanTheMutex: public std::exception{
public:
   
    explicit ThreadPriorityHigherThanTheMutex(const char* message)
    : msg_(message)
    {}
    explicit ThreadPriorityHigherThanTheMutex(const std::string& message)
    : msg_(message)
    {}

    virtual ~ThreadPriorityHigherThanTheMutex() throw (){}
    
    virtual const char* what() const throw (){
       return  msg_.c_str();
    }

protected:
    std::string  msg_;
};
}//experis

#endif //THREADPRIORITYHIGHERTHENTHEMUTEX_H
