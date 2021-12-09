#include "MainMenu.h"

void MainMenu::addClient(const ClientData& clientData) {
    m_clients.insert({clientData.id, &clientData});
}

void MainMenu::removeClient(std::string id) {
    m_clients.erase(id);
}

boost::asio::ip::tcp::socket& MainMenu::getClientSocket(std::string id) {
    return m_clients[id]->socket;
}

bool MainMenu::haveClient(std::string id) {
    return m_clients.find(id) != m_clients.end();
}
