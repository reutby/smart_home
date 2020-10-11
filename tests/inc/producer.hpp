#ifndef PRODUCER_H
#define PRODUCER_H
#include "runable.hpp"
#include "cat.hpp"
#include <iostream>
#include <tr1/memory>
#include "unbounded_waitablequeue.hpp"
#include "atomicvalue.hpp"
namespace experis{
namespace test{


class Producer : public common::Runable{
public:

    Producer(const  std::tr1::shared_ptr<UnboundedWaitableQueue <std::pair<Cat,size_t> > >&a_queue, size_t a_start,size_t a_end, AtomicValue<size_t>& atomicval);
    //virtual ~Producer();
    virtual void Run();

private:
    std::tr1::shared_ptr<UnboundedWaitableQueue <std::pair<Cat,size_t> > >m_queue;
    size_t m_start;
    size_t m_end;
    AtomicValue<size_t>&m_atomicval;
};


}//test
}//experis
#endif //PRODUCER_H
