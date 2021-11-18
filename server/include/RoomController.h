#ifndef ROOMCONTROLLER_H
#define ROOMCONTROLLER_H

#include <map>

#include "Room.h"

class RoomController {
public:
    RoomController() = default;
    Room& getRoom(unsigned int roomId);
    std::map<unsigned int, Room> getAllRooms();
    void createRoom(unsigned int roomId);
    void deleteRoom(unsigned int roomId);
    ~RoomController() = default;

private:
    std::map<unsigned int, Room> m_rooms;
};

#endif // ROOMCONTROLLER_H
