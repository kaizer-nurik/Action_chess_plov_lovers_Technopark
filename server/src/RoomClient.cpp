#include "RoomClient.h"

RoomClient::RoomClient(boost::asio::ip::tcp::socket& socket): m_socket(socket) {

}

void RoomClient::onMessage(std::string msg) {

}

