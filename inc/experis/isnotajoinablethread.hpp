#ifndef ISNOTAJOINABLETHREAD_H
#define ISNOTAJOINABLETHREAD_H
#include <exception>

namespace experis{
class IsNotAJoinableThread: public std::exception{
public:
   
    explicit IsNotAJoinableThread(const char* message)
    : msg_(message)
    {}
    explicit IsNotAJoinableThread(const std::string& message)
    : msg_(message)
    {}

    virtual ~IsNotAJoinableThread() throw (){}
    
    virtual const char* what() const throw (){
       return  msg_.c_str();
    }

protected:
    std::string  msg_;
};
}//experis

#endif //ISNOTAJOINABLETHREAD_H
