#ifndef THECURRENTTHREADNOTOWNTHEMUTEX_H
#define THECURRENTTHREADNOTOWNTHEMUTEX_H
#include <exception>

namespace experis{
class TheCurrentThreadNotOwnTheMutex: public std::exception{
public:
   
    explicit TheCurrentThreadNotOwnTheMutex(const char* message)
    : msg_(message)
    {}
    explicit TheCurrentThreadNotOwnTheMutex(const std::string& message)
    : msg_(message)
    {}

    virtual ~TheCurrentThreadNotOwnTheMutex() throw (){}
    
    virtual const char* what() const throw (){
       return  msg_.c_str();
    }

protected:
    std::string  msg_;
};
}//experis

#endif //THECURRENTTHREADNOTOWNTHEMUTEX_H
