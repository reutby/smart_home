#ifndef CAT_H
#define CAT_H
#include <string>
namespace experis{
namespace test{

class Cat{
public:
    Cat():m_name("snow"){}
    Cat(std::string a_name):m_name(a_name){}
    virtual ~Cat(){}
    
    std::string GetName()const{return m_name;} 
private:
    std::string m_name;
};

class Lion: public Cat{
public:
    Lion(std::string a_name,double a_weigth)
    : Cat(a_name)
    , m_weigth(a_weigth)
    {}
    double GetWeigth()const{return m_weigth;}
private:
    double m_weigth;
};

}//test

}//experis

#endif//CAT_H