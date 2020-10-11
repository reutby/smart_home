#include "consumer.hpp"

namespace experis{

namespace test{


Consumer:: Consumer(const std::tr1::shared_ptr<UnboundedWaitableQueue <std::pair<Cat, size_t> > > &a_queue, size_t _itrNum,AtomicValue<size_t>& a_av, std::queue<std::pair<Cat, size_t> > & a_testqueue)
: m_queue(a_queue)
, m_itrNum(_itrNum)
, m_atomicval(a_av)
, m_testqueue(a_testqueue)
{}


void Consumer::Run(){
    for(size_t i=0; i<m_itrNum;++i){
        std::pair<Cat, size_t> pair;
        m_queue->Dequeue(pair);
        m_testqueue.push(pair);
    }
}

}//test
}//experis
