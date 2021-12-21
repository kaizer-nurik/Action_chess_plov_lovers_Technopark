#include "RoomWriter.h"

#include <boost/asio/write.hpp>
#include <iostream>

void RoomWriter::onMessage(boost::asio::ip::tcp::socket& socket, const ClientData& clientData, const std::string& msg) {
    std::string buffer = clientData.id + " prints: " + msg;
    boost::asio::write(socket, boost::asio::buffer(buffer.data(), buffer.size()));
}

void RoomWriter::onEnter(boost::asio::ip::tcp::socket& socket, const ClientData& clientData) {
    std::string buffer = clientData.id + " entered";
    boost::asio::write(socket, boost::asio::buffer(buffer.data(), buffer.size()));
}

void RoomWriter::onGameStart(boost::asio::ip::tcp::socket& socket) {
    std::string buffer = "GameStarted ";
    boost::asio::write(socket, boost::asio::buffer(buffer.data(), buffer.size()));
}

