#include "Room.h"

Room::Room(unsigned int maxClientNumber): m_maxClientNumber(maxClientNumber) {}

unsigned int Room::getCurrentClientNumber() {
    return m_currentClientNumber;
}

unsigned int Room::getMaxClientNumber() {
    return m_maxClientNumber;
}

void Room::addClient(const ClientData& clientData) {
    m_clients.insert({clientData.id, &clientData});
    for (auto &client: m_clients) {
        if (client.first != clientData.id) {
            m_writer.onEnter(client.second->socket, clientData);
        }
    }
}

void Room::removeClient(std::string id) {
    m_clients.erase(id);
}

boost::asio::ip::tcp::socket& Room::getClientSocket(std::string id) {
    return m_clients[id]->socket;
}

bool Room::haveClient(std::string id) {
    return m_clients.find(id) != m_clients.end();    
}

void Room::broadcast(const ClientData& clientData, std::string msg) {
    for (auto &client: m_clients) {
        if (client.first != clientData.id) {
            m_writer.onMessage(client.second->socket, clientData, msg);
        }
    }
}

void Room::startGame() {}

bool Room::gameStarted() {}

Room::~Room() {
    for (const auto &client: m_clients) {
        delete client.second;
    }
}
