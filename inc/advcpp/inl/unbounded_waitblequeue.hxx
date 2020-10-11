#ifndef UNBOUNDED_WAIRABLEQUEUE_INL_H
#define UNBOUNDED_WAIRABLEQUEUE_INL_H
#include "unbounded_waitablequeue.hpp"

namespace experis{

template<class T>
UnboundedWaitableQueue<T>::UnboundedWaitableQueue()
: m_stop(false)
{

}

template<class T>
UnboundedWaitableQueue<T>::~UnboundedWaitableQueue()
{
    if(!m_stop){
        m_stop = true;
        m_qeueuempty.SignalAll();
    }
}

template<class T>
bool UnboundedWaitableQueue<T>::expression()const
{
    bool result = (m_queue.size() == 0);
    return result;
}
template<class T>
void UnboundedWaitableQueue<T>::Enqueue(const T& _item)
{
    Locker lock(m_criticalMutex);
    if(m_stop){
        return;
    }
    if(m_queue.empty()){
        m_queue.push(_item);
        m_qeueuempty.Signal();
    }else{
        m_queue.push(_item);
    }
}

template<class T>
void UnboundedWaitableQueue<T>::Dequeue(T& a_retItem)
{
    Locker lock(m_criticalMutex);
    if(m_stop){
        return;
    } 
    std::tr1::shared_ptr<IExpression> expression(new MemFuncExpression<UnboundedWaitableQueue<T> >(*this,&UnboundedWaitableQueue<T>::expression));
    m_qeueuempty.Wait(m_criticalMutex,expression);
    if(m_stop){
        return;
    }
    if(!m_queue.empty()){
        a_retItem = m_queue.front();
        m_queue.pop();
    }
}

template<class T>
size_t UnboundedWaitableQueue<T>::Occupancy()const
{
    Locker lock(m_criticalMutex);
    return m_queue.size();
}

template<class T>
void UnboundedWaitableQueue<T>::Clear(std::vector<T>& a_remain)
{
    Stop();
    Locker lock(m_criticalMutex);
    while( m_queue.size()!=0){
        a_remain.push_back(m_queue.front());
        m_queue.pop();
    }
}
template<class T>
bool UnboundedWaitableQueue<T>::IsEmpty()const
{
    Locker lock(m_criticalMutex);
    return m_queue.empty(); 
}

template<class T>
void UnboundedWaitableQueue<T>::Stop()
{
    Locker lock(m_criticalMutex);
    m_stop = true;
    m_qeueuempty.SignalAll();
}
}//experis

#endif//UNBOUNDED_WAIRABLEQUEUE_INL_H
