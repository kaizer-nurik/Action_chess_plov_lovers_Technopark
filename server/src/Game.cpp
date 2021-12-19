#include "Game.h"

Game::Game(const std::string& id): m_id(id) {}

void Game::addClient(const ClientData& clientData) {
    m_clients.insert({clientData.id, &clientData});
}

const ClientData* Game::removeClient(const std::string& id) {
    const ClientData* clientData = m_clients[id];
    m_clients.erase(id);
    return clientData;
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

void Game::broadcast(const std::string& id, const std::string& response) {
    for (auto &client: m_clients) {
        if (client.first != id) {
            m_writer.onAction(client.second->socket, response);
        }
    }
}

return_after_move Game::makeAction(const std::string& id, const std::string& action) {
    return m_session->makeMove(action, id);
}

void Game::start() {
    m_session = new GameSession(m_id, (*m_clients.begin()).first, (*(++m_clients.begin())).first);
}

void Game::onEnd() {
    // ...

    delete m_session;
}
