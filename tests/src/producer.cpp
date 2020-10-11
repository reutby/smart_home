#include "producer.hpp"
#include <sstream>
namespace experis{

namespace test{


Producer:: Producer(const  std::tr1::shared_ptr<UnboundedWaitableQueue <std::pair<Cat,size_t> > >&a_queue, size_t a_start,size_t a_end, AtomicValue<size_t>& atomicval)
: m_queue(a_queue)
, m_start(a_start)
, m_end(a_end)
, m_atomicval(atomicval)
{}

void Producer::Run()
{
    for(size_t i=m_start; i<m_end;++i){
        std::stringstream ss;
        ss << "felix" << i+1;
        Cat c(ss.str());
        m_queue->Enqueue(std::make_pair(c,++m_atomicval));
    }
}


}//test
}//experis
