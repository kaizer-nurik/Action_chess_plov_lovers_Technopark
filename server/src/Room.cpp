#include "Room.h"

#include <iostream>

Room::Room(const std::string& id, unsigned int maxClientNumber): m_id(id), m_maxClientNumber(maxClientNumber), m_game(m_id) {}

unsigned int Room::getCurrentClientNumber() {
    return m_currentClientNumber;
}

unsigned int Room::getMaxClientNumber() {
    return m_maxClientNumber;
}

void Room::addClient(const ClientData& clientData) {
    m_clients.insert({clientData.id, &clientData});
    m_currentClientNumber++;
    /*
    for (auto &client: m_clients) {
        if (client.first != clientData.id) {
            m_writer.onEnter(client.second->socket, clientData);
        }
    }
    */
}

const ClientData* Room::removeClient(const std::string& id) {
    const ClientData* clientData = m_clients[id];
    m_clients.erase(id);
    m_currentClientNumber--;
    return clientData;
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

void Room::broadcast(const std::string& id, const std::string& method) {
    if (method == "GameStart") {
        for (auto &client: m_clients) {
            if (client.first != id) {
                m_writer.onGameStart(client.second->socket);
            }
        }
    }
}

void Room::startGame() {
    for (auto it = m_clients.cbegin(), nextIt = it; it != m_clients.cend(); it = nextIt) {
        ++nextIt;
        m_game.addClient(*removeClient(it->second->id));
    }
    m_game.start();
}

Game& Room::getGame() {
    return m_game;
}

bool Room::gameStarted() {
    return m_gameStarted;
}

Room::~Room() {
    for (const auto &client: m_clients) {
        delete client.second;
    }
}
