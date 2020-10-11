#ifndef NO_CONTROLLERS_HAVEBEEN_REGISTER_H
#define NO_CONTROLLERS_HAVEBEEN_REGISTER_H
#include <exception>
#include <iostream>
namespace pikachu{
class NoControllersHaveBeenRegister: public std::exception{
public:
   
    explicit NoControllersHaveBeenRegister(const char* message)
    : msg_(message)
    {}
    explicit NoControllersHaveBeenRegister(const std::string& message)
    : msg_(message)
    {}

    virtual ~NoControllersHaveBeenRegister() throw (){}
    
    virtual const char* what() const throw (){
       return  msg_.c_str();
    }

protected:
    std::string  msg_;
};
}//experis

#endif //NO_CONTROLLERS_HAVEBEEN_REGISTER_H
