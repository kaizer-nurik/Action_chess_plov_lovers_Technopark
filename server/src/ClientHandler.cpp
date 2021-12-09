#include "ClientHandler.h"

#include <boost/bind.hpp>
#include <iostream>

ClientHandler::ClientHandler(boost::asio::io_context& ioContext, MainMenu& mainMenu, Router& router)
        : m_strand(boost::asio::make_strand(ioContext)),
          m_socket(m_strand),
          m_clientData(m_socket),
          m_mainMenu(mainMenu),
          m_router(router) {}

boost::asio::ip::tcp::socket& ClientHandler::getSocket() {
    return m_socket;
}

void ClientHandler::start() {
    m_clientData.id = m_socket.remote_endpoint().address().to_string() + ":" + std::to_string(m_socket.remote_endpoint().port());
    // m_clientData.nickname = m_clientData.id;

    m_socket.async_read_some(boost::asio::buffer(m_readBuffer),
                             boost::bind(&ClientHandler::handleRead, shared_from_this(),
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}

void ClientHandler::handleRead(const boost::system::error_code& err, std::size_t bytes_transferred) {
    if (!err) {
        std::cout << "Read (" << m_clientData.id << "): " << m_readBuffer.data() << std::endl;

        std::string writeBuffer = m_router.processRoute(std::string(m_readBuffer.data()), m_clientData, m_mainMenu);

        std::cout << "Write (" << m_clientData.id << "): " << writeBuffer << std::endl;

        boost::asio::async_write(m_socket, boost::asio::buffer(writeBuffer.data(), writeBuffer.size()),
                                 boost::bind(&ClientHandler::handleWrite, shared_from_this(),
                                             boost::asio::placeholders::error));
    } else {
        std::cout << "Сonnection was broken: " << m_clientData.id << std::endl;
    }
}

void ClientHandler::handleWrite(const boost::system::error_code& err) {
    m_socket.async_read_some(boost::asio::buffer(m_readBuffer),
                             boost::bind(&ClientHandler::handleRead, shared_from_this(),
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}

void ClientHandler::authenticate() {}
