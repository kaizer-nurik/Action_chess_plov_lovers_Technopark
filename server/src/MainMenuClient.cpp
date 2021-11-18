#include "MainMenuClient.h"

MainMenuClient::MainMenuClient(boost::asio::ip::tcp::socket& socket): m_socket(socket) {

}

void MainMenuClient::onRequestRoomsInfo() {
    
}
