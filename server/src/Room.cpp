#include "Room.h"

Room::Room(const std::string& id, unsigned int maxClientNumber): m_id(id), m_maxClientNumber(maxClientNumber), m_game(m_id) {}

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

void Room::removeClient(const std::string& id) {
    m_clients.erase(id);
}

boost::asio::ip::tcp::socket& Room::getClientSocket(const std::string& id) {
    return m_clients[id]->socket;
}

bool Room::haveClient(const std::string& id) {
    return m_clients.find(id) != m_clients.end();    
}

const ClientData* Room::getClient(const std::string& id) {
    if (haveClient(id)) {
        return m_clients[id];
    } else {
        return nullptr;
    }
}

void Room::broadcast(const std::string& id, const std::string& msg) {
    for (auto &client: m_clients) {
        if (client.first != id) {
            m_writer.onMessage(client.second->socket, *getClient(id), msg);
        }
    }
}

void Room::startGame() {
    m_game.start();    
}

bool Room::gameStarted() {
    return m_gameStarted;
}

Room::~Room() {
    for (const auto &client: m_clients) {
        delete client.second;
    }
}
