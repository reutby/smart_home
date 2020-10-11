#include "location.hpp"

namespace pikachu{

Location::Location()
: m_room()
, m_floor(0)
{}

Location::Location(const std::string &a_room, size_t a_floor)
: m_room(a_room)
, m_floor(a_floor)
{
}

void Location::SetFloor(size_t a_floor)
{
    m_floor = a_floor;
}
void Location::SetRoom(std::string& a_room)
{
    m_room.assign(a_room);
}
size_t Location::GetFloor()const
{
    return m_floor;
}

const std::string& Location::GetRoom()const
{
    return m_room;
}

bool operator==(const Location&a_tocompare,const Location& a_comparewith)
{
    if(a_tocompare.GetFloor() == a_comparewith.GetFloor() 
    && a_tocompare.GetRoom() == a_comparewith.GetRoom()){
        return true;
    }
    return false;
}
}//pikachu
