#ifndef RUNABLE_H
#define RUNABLE_H

namespace experis{
namespace common{

class Runable{
public:
    virtual ~Runable(){}
    virtual void Run() = 0;
};

}//common
}//experis
#endif //RUNABLE