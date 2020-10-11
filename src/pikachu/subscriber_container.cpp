#include "subscriber_container.hpp"
#include <vector>
#include <algorithm>
namespace pikachu{
    
// struct InsertSubToVec{
    
//     typedef std::multimap<EventAttribute,std::tr1::shared_ptr<IController> >::iterator multimap_itr;
//     std::vector<std::tr1::shared_ptr<IController> > &m_vec;
//     InsertSubToVec(std::vector<std::tr1::shared_ptr<IController> > &a_vec)
//     : m_vec(a_vec)
//     {}
//     void operator()(multimap_itr& a_itr)
//     {
//         m_vec.push_back(a_itr->second);
//     }
// };


void SubscribersContainer::InsertSubscriber(const EventAttribute& a_attribute,const std::tr1::shared_ptr<IController> a_device )
{
    experis::Locker lock(m_guardMutex);
    std::map<std::tr1::shared_ptr<IController> , size_t>::iterator 
    itr = m_controllersStatus.find(a_device);
    m_subscribersTable.insert(std::make_pair(a_attribute,a_device));
    if( itr == m_controllersStatus.end()){
        if(a_attribute.GetLocation().GetFloor() == EventAttribute::EVENT_ATT_ALL_FLOOERS
        || a_attribute.GetLocation().GetRoom()=="*"){
            m_controllersStatus.insert(std::make_pair(a_device,2));
        }
        else{
            m_controllersStatus.insert(std::make_pair(a_device,1));
                    }
    }
    else{
        itr->second++;
    }
  //  std::cout<<m_controllersStatus.size()<<" blabla bla" << m_subscribersTable.size()<< std::endl;
}

void SubscribersContainer:: selectControllers(const EventAttribute& a_attribute, std::vector<std::tr1::shared_ptr<IController> > &a_vec)
{
    typedef std::multimap<EventAttribute,std::tr1::shared_ptr<IController> >::iterator multimap_itr;
    multimap_itr lowerbound = m_subscribersTable.lower_bound(a_attribute);
    multimap_itr upperbound = m_subscribersTable.upper_bound(a_attribute);
    
    //std::pair <multimap_itr, multimap_itr> ret = m_subscribersTable.equal_range(a_attribute);
    for(multimap_itr itr = lowerbound ;itr!= upperbound;++itr ){
        a_vec.push_back(itr->second);
    }
}
void SubscribersContainer::SelectSubscriber(const EventAttribute& a_attribute,std::vector<std::tr1::shared_ptr<IController> > &a_vec)
{
    experis::Locker lock(m_guardMutex);
    selectControllers(a_attribute,a_vec);
    EventAttribute allbuilding(Location("*",EventAttribute::EVENT_ATT_ALL_FLOOERS),a_attribute.GetEventType());
    selectControllers(allbuilding,a_vec);
    EventAttribute allrooms(Location("*",a_attribute.GetLocation().GetFloor()),a_attribute.GetEventType());
    selectControllers(allrooms,a_vec);
}
bool SubscribersContainer::RemoveSubscriber(const EventAttribute& a_attribute,const std::tr1::shared_ptr<IController> a_device)
{
    experis::Locker lock(m_guardMutex);
    typedef std::multimap<EventAttribute,std::tr1::shared_ptr<IController> >::iterator multimap_itr;
    std::pair <multimap_itr, multimap_itr> ret = m_subscribersTable.equal_range(a_attribute);
    for(multimap_itr itr =ret.first; itr != ret.second; ++itr){
        if(itr->second == a_device)
        {
            m_subscribersTable.erase(itr);
            m_controllersStatus.erase(itr->second);
            return true;
        }
    }

    return false;
}

void SubscribersContainer:: GetMultiAndSingleEventsSubscribers(std::vector<std::tr1::shared_ptr<IController> >& a_multivec, std::vector<std::tr1::shared_ptr<IController> >& a_singlevec)
{
    experis::Locker lock(m_guardMutex);
    for(std::map<std::tr1::shared_ptr<IController> , size_t>::iterator itr = m_controllersStatus.begin()
    ; itr!= m_controllersStatus.end(); ++itr)
    {
        if(itr->second > 1){
            a_multivec.push_back(itr->first);
        }
        else{
            a_singlevec.push_back(itr->first);
        }
    }
}

size_t SubscribersContainer::Size()const
{
    experis::Locker lock(m_guardMutex);
    return m_subscribersTable.size();        
}
}//pikachu