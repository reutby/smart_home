#ifndef LOCATION_H
#define LOCATION_H
#include <string>
namespace pikachu{

class Location{
public: 
    Location();
    Location(const std::string &a_room, size_t m_floor);
    size_t GetFloor()const;
    const std::string& GetRoom()const;
    void SetFloor(size_t floor);
    void SetRoom(std::string& room);
private:
    std::string m_room;
    size_t m_floor;
};

bool operator==(const Location&a_tocompare,const Location& a_comparewith);
}//pikachu


#endif//LOCATION_H