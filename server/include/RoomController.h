#ifndef ROOMCONTROLLER_H
#define ROOMCONTROLLER_H

#include <map>

#include "Room.h"

class RoomController {
public:
    RoomController() = default;

    Room* getRoom(std::string roomId);
    bool haveRoom(std::string id);
    std::map<std::string, Room*> getAllRooms();
    void createRoom(std::string roomId, unsigned int maxClientNumber);
    void deleteRoom(std::string roomId);

    ~RoomController() = default;

private:
    std::map<std::string, Room*> m_rooms;
};

#endif // ROOMCONTROLLER_H
