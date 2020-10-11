#include "mvpreciver.hpp"

namespace pikachu{

MvpReciver::MvpReciver(const std::tr1::shared_ptr<IEnqueue> a_enqueue)
: m_enqueue(a_enqueue)
{

}

void MvpReciver::ReciveEvent(const std::tr1::shared_ptr<EventBase> a_event)
{
    {
        experis::Locker lock(m_gaurd);
        a_event->SetEnequeueSeq(m_seq.Value());
    }
    ++m_seq;
    m_enqueue->Enqueue(a_event);
}

}//pikachu