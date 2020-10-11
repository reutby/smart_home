#ifndef ATOMIC_VALUE_H
#define ATOMIC_VALUE_H
#include <string>
#include "uncopyable.hpp"

namespace experis{

template<class T>
class AtomicValue : private UnCopyable{
public:
    
    AtomicValue(T a_val = T(0));
    //AtomicValue(const AtomicValue& )// = defailt
    //AtomicValue& AtomicValue(const AtomicValue& )// = defailt
    //~AtomicValue()// = defailt
    T operator++();
    T operator+=(T a_add);
    T operator--();
    T operator-=(T a_add);
    T Value();
    bool Set(T a_set);
    bool IsZero()const;

private:
    T m_value;
};

template<class T>
inline AtomicValue<T>::AtomicValue(T a_val)
: m_value(T(a_val))
{
}
template<class T>
T AtomicValue<T>::operator++()
{
    return __sync_add_and_fetch(&m_value, 1 );
}

template<class T>
inline T AtomicValue<T>::operator--()
{
    return __sync_sub_and_fetch(&m_value, 1 );
}

template<class T>
inline T AtomicValue<T>::operator-=(T a_sub)
{
    return __sync_sub_and_fetch(&m_value, a_sub);
}
template<class T>
inline T AtomicValue<T>::operator+=(T a_add)
{
    return __sync_add_and_fetch(&m_value, a_add);
}

template<class T>
inline bool AtomicValue<T>:: Set(T a_val)
{
    return __sync_bool_compare_and_swap(&m_value,m_value,a_val);
}
template<class T>
inline bool AtomicValue<T>::IsZero()const
{
    return Value() == T(0);
}
template<class T>
inline T AtomicValue<T>::Value()
{
    return __sync_add_and_fetch(&m_value, 0);
    //return __sync_val_compare_and_swap(&m_value, m_value,m_value);
}

}//experis

#endif//ATOMIC_VALUE_H