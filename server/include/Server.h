#ifndef SERVER_H
#define SERVER_H

#include <boost/asio.hpp>
#include <string>

#include "ClientHandler.h"
#include "MainMenu.h"
#include "Router.h"

class Server {
public:
    Server(const std::string address, const std::string port, std::size_t threadNum);

    void run();
    
    ~Server() = default;

private:
    void startAccept();
    void onAccept(const boost::system::error_code& err);
    void onStop();

    std::size_t m_threadNum;
    boost::asio::io_context m_ioContext;
    boost::asio::signal_set m_signals;
    boost::asio::ip::tcp::acceptor m_acceptor;
    boost::shared_ptr<ClientHandler> m_client;
    MainMenu m_mainMenu;
    Router m_router;
};

#endif // SERVER_H
