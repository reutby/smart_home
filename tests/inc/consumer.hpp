#ifndef CONSUMER_H
#define CONSUMER_H
#include "runable.hpp"
#include <iostream>
#include <tr1/memory>
#include <queue>
#include <exception>
#include "atomicvalue.hpp"
#include "unbounded_waitablequeue.hpp"
#include "cat.hpp"
namespace experis{
namespace test{
class Consumer : public common::Runable{

public:
    Consumer(const std::tr1::shared_ptr<UnboundedWaitableQueue <std::pair<Cat, size_t> > > &a_queue, size_t _itrNum,AtomicValue<size_t>& a_av, std::queue<std::pair<Cat, size_t> > & a_testqueue);
    //virtual ~Consumer();
    virtual void Run();

private:

    std::tr1::shared_ptr<UnboundedWaitableQueue <std::pair<Cat, size_t> > > m_queue;
    size_t m_itrNum;
    AtomicValue<size_t> &m_atomicval;
    std::queue<std::pair<Cat, size_t> > &m_testqueue;
};

}//test
}//experis

#endif //CONSUMER_H
