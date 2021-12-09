#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>

#include "ClientData.h"
#include "MainMenu.h"
#include "Router.h"

#define MAX_IP_PACK_SIZE 8192

class ClientHandler: public boost::enable_shared_from_this<ClientHandler>, private boost::noncopyable {
public:
    ClientHandler(boost::asio::io_context& ioContext, MainMenu& mainMenu, Router& router);

    boost::asio::ip::tcp::socket& getSocket();

    void start();

    ~ClientHandler() = default;

private:
    void handleRead(const boost::system::error_code& err, std::size_t bytes_transferred);
    void handleWrite(const boost::system::error_code& err);
    void authenticate();

    boost::asio::strand<boost::asio::io_context::executor_type> m_strand;
    boost::asio::ip::tcp::socket m_socket;

    ClientData m_clientData;
    MainMenu& m_mainMenu;
    Router& m_router;

    boost::array<char, MAX_IP_PACK_SIZE> m_readBuffer; 
};

#endif // CLIENTHANDLER_H
