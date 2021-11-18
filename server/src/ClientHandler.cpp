#include "ClientHandler.h"

ClientHandler::ClientHandler(boost::asio::io_context& ioContext, MainMenu& mainMenu)
        : m_strand(boost::asio::make_strand(ioContext)),
          m_socket(m_strand),
          m_clientData(m_socket),
          m_mainMenu(mainMenu) {

}

void ClientHandler::start() {

}

void ClientHandler::handleRead(const boost::system::error_code& err) {

}

void ClientHandler::authenticate() {
    
}
