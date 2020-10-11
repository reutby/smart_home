#ifndef UNCOPYABLE_H
#define UNCOPYABLE_H

namespace experis{

class UnCopyable{
public:

private:
    UnCopyable(const UnCopyable& _uc);
    UnCopyable& operator=(const UnCopyable& _uc);
protected:
    UnCopyable(){}
};

}//experis
#endif //UNCOPYABLE_H