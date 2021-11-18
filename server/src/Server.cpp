#include "Server.h"

Server::Server(const std::string address, const std::string port, std::size_t threadNum)
        : m_threadNum(threadNum),
          m_acceptor(m_ioContext),
          m_mainMenu() {
    
}

void Server::run() {

}

void Server::startAccept() {

}

void Server::onAccept(boost::shared_ptr<ClientHandler> newClient, const boost::system::error_code& err) {

}
