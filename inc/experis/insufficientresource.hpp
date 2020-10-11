#ifndef INSUFFICIENTRESOURCE_H
#define INSUFFICIENTRESOURCE_H
#include <exception>
#include <string>
namespace experis{
class InsufficientResource: public std::exception{
public:
   
    explicit InsufficientResource(const char* message)
    : msg_(message)
    {}
    explicit InsufficientResource(const std::string& message)
    : msg_(message)
    {}

    virtual ~InsufficientResource() throw (){}
    
    virtual const char* what() const throw (){
       return  msg_.c_str();
    }

protected:
    std::string  msg_;
};
}//experis

#endif //INSUFFICIENTRESOURCE_H
