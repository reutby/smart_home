#ifndef UNBOUNDED_WAITABLE_QUEUE_H
#define UNBOUNDED_WAITABLE_QUEUE_H
#include "mutex.hpp"
#include "conditionvarible.hpp"
#include "queue_is_close.hpp"
#include <queue>
namespace experis{

template<class T>
class UnboundedWaitableQueue{
public:
    UnboundedWaitableQueue();
    ~UnboundedWaitableQueue();
    void Enqueue(const T& _item);
    void Dequeue(T& _retItem);
    size_t Occupancy()const;
    void Clear(std::vector<T>& a_remain);
    bool IsEmpty()const;
    void Stop();

private:
    bool expression()const;

private:
    ConditionVarible m_qeueuempty;
    mutable Mutex m_criticalMutex;
    std::queue<T> m_queue;
    bool m_stop;
};

}//experis

#include "inl/unbounded_waitblequeue.hxx" 
#endif//UNBOUNDED_WAITABLE_QUEUE_H
