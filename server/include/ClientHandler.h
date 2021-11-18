#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <boost/array.hpp>
#include <boost/asio.hpp>

#include "ClientData.h"
#include "MainMenu.h"
#include "RequestParser.h"

class ClientHandler: public std::enable_shared_from_this<ClientHandler> {
public:
    ClientHandler(boost::asio::io_context& ioContext, MainMenu& mainMenu);
    void start();

private:
    void handleRead(const boost::system::error_code& err);
    void authenticate();

    boost::asio::strand<boost::asio::io_context::executor_type> m_strand;
    boost::asio::ip::tcp::socket m_socket;
    ClientData m_clientData;
    MainMenu& m_mainMenu;
    boost::array<char, MAX_IP_PACK_SIZE> m_readBuffer; 
};

#endif // CLIENTHANDLER_H
