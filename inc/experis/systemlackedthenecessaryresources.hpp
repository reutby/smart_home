#ifndef SYSTEMLACKEDTHENECESSARYRESOURCES_H
#define SYSTEMLACKEDTHENECESSARYRESOURCES_H
#include <exception>
#include <iostream>
namespace experis{
class SystemLackedTheNecessaryResources: public std::exception{
public:
   
    explicit SystemLackedTheNecessaryResources(const char* message)
    : msg_(message)
    {}
    explicit SystemLackedTheNecessaryResources(const std::string& message)
    : msg_(message)
    {}

    virtual ~SystemLackedTheNecessaryResources() throw (){}
    
    virtual const char* what() const throw (){
       return  msg_.c_str();
    }

protected:
    std::string  msg_;
};
}//experis

#endif //SYSTEMLACKEDTHENECESSARYRESOURCES_H
