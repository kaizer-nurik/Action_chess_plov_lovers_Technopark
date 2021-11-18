#include "Room.h"

Room::Room(unsigned int maxClientNumber) {

}

unsigned int Room::getCurrentClientNumber() {

}

unsigned int Room::getMaxClientNumber() {

}

void Room::addClient(const ClientData& clientData) {

}

void Room::removeClient(unsigned int id) {

}

boost::asio::ip::tcp::socket& Room::getClientSocket(unsigned int id) {

}

bool Room::haveClient(unsigned int id) {
    
}

void Room::broadcast(const ClientData& clientData, std::string msg) {

}

void Room::startGame() {

}

bool Room::gameStarted() {

}
