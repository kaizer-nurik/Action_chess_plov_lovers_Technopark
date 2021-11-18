#ifndef SERVER_H
#define SERVER_H

#include <boost/asio.hpp>
#include <string>

#include "ClientHandler.h"
#include "MainMenu.h"

class Server {
public:
    Server(const std::string address, const std::string port, std::size_t threadNum);
    void run();
    
private:
    void startAccept();
    void onAccept(boost::shared_ptr<ClientHandler> newClient, const boost::system::error_code& err);

    std::size_t m_threadNum;
    boost::asio::io_context m_ioContext;
    boost::asio::ip::tcp::acceptor m_acceptor;
    MainMenu m_mainMenu;
};

#endif // SERVER_H
