#include "event_queue.hpp"

namespace pikachu{

std::tr1::shared_ptr<EventBase> EventQueue::Dequeue()
{
    std::tr1::shared_ptr<EventBase> a_event;
    m_queue.Dequeue(a_event);
    return a_event;
}
void EventQueue::Enqueue(const std::tr1::shared_ptr<EventBase> a_event)
{

    m_queue.Enqueue(a_event);
}
size_t EventQueue::Size()const
{
    return m_queue.Occupancy();
}

void EventQueue::Stop()
{
    m_queue.Stop();
}
}//pikachu