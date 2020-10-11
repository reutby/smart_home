#ifndef THREAD_ASNOT_BEEN_TERMINATED_H
#define THREAD_ASNOT_BEEN_TERMINATED_H
#include <exception>
#include <string>
namespace experis{
class ThreadAsNotBeenTerminated: public std::exception{
public:
   
    explicit ThreadAsNotBeenTerminated(const char* message)
    : msg_(message)
    {}
    explicit ThreadAsNotBeenTerminated(const std::string& message)
    : msg_(message)
    {}

    virtual ~ThreadAsNotBeenTerminated() throw (){}
    
    virtual const char* what() const throw (){
       return  msg_.c_str();
    }

protected:
    std::string  msg_;
};
}//experis

#endif //THREAD_ASNOT_BEEN_TERMINATED_H
