#include "MainMenu.h"

void MainMenu::addClient(const ClientData& clientData) {
    m_clients.insert({clientData.id, &clientData});
}

const ClientData* MainMenu::removeClient(const std::string& id) {
    const ClientData* clientData = m_clients[id];
    m_clients.erase(id);
    return clientData;
}

boost::asio::ip::tcp::socket& MainMenu::getClientSocket(const std::string& id) {
    return m_clients[id]->socket;
}

bool MainMenu::haveClient(const std::string& id) {
    return m_clients.find(id) != m_clients.end();
}

const ClientData* MainMenu::getClient(const std::string& id) {
    if (haveClient(id)) {
        return m_clients[id];
    } else {
        return nullptr;
    }
}
