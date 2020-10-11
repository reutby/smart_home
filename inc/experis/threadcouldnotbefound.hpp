#ifndef THREADCOULDNOTBEFOUND_H
#define THREADCOULDNOTBEFOUND_H
#include <exception>

namespace experis{
class ThreadCouldNotBeFound: public std::exception{
public:
   
    explicit ThreadCouldNotBeFound(const char* message)
    : msg_(message)
    {}
    explicit ThreadCouldNotBeFound(const std::string& message)
    : msg_(message)
    {}

    virtual ~ThreadCouldNotBeFound() throw (){}
    
    virtual const char* what() const throw (){
       return  msg_.c_str();
    }

protected:
    std::string  msg_;
};
}//experis

#endif //THREADCOULDNOTBEFOUND_H
