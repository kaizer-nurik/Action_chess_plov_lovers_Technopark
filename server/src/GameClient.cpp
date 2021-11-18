#include "GameClient.h"

GameClient::GameClient(boost::asio::ip::tcp::socket& socket): m_socket(socket) {

}

void GameClient::onEvent(std::string msg) {

}
