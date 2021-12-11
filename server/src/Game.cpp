#include "Game.h"

Game::Game(const std::string& id): m_id(id) {}

void Game::addClient(const ClientData& clientData) {
    m_clients.insert({clientData.id, &clientData});
}

void Game::removeClient(const std::string& id) {
    m_clients.erase(id);
}

boost::asio::ip::tcp::socket& Game::getClientSocket(const std::string& id) {
    return m_clients[id]->socket;
}

bool Game::haveClient(const std::string& id) {
    return m_clients.find(id) != m_clients.end();    
}

const ClientData* Game::getClient(const std::string& id) {
    if (haveClient(id)) {
        return m_clients[id];
    } else {
        return nullptr;
    }
}

void Game::broadcast(const std::string& id, const std::string& action) {}

void Game::makeAction(const std::string& id, const std::string& action) {
    m_session->makeMove(action, id);
}

void Game::start() {
    m_session = new GameSession(m_id, (*m_clients.begin()).first, (*(m_clients.begin()++)).first);
}

void Game::onEnd() {
    // ...

    delete m_session;
}
