#include "RoomWriter.h"

#include <boost/asio/write.hpp>
#include <iostream>

void RoomWriter::onMessage(boost::asio::ip::tcp::socket& socket, const ClientData& clientData, const std::string& msg) {
    std::string writeBuffer = clientData.id + " prints: " + msg;
    boost::asio::write(socket, boost::asio::buffer(msg.data(), msg.size()));
}

void RoomWriter::onEnter(boost::asio::ip::tcp::socket& socket, const ClientData& clientData) {
    std::string msg = clientData.id + " entered";
    boost::asio::write(socket, boost::asio::buffer(msg.data(), msg.size()));
}
