#include "RoomController.h"

Room* RoomController::getRoom(std::string roomId) {
    if (haveRoom(roomId)) {
        return m_rooms[roomId];
    } else {
        return nullptr;
    }
}

bool RoomController::haveRoom(std::string id) {
    return m_rooms.find(id) != m_rooms.end();    
}

std::map<std::string, Room*> RoomController::getAllRooms() {
    return m_rooms;
}

void RoomController::createRoom(std::string roomId, unsigned int maxClientNumber) {
    m_rooms.insert({roomId, new Room(maxClientNumber)});
}

void RoomController::deleteRoom(std::string roomId) {
    delete getRoom(roomId);
    m_rooms.erase(roomId);
}
