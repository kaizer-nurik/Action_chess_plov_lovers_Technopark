#include "RoomWriter.h"

void RoomWriter::onMessage(boost::asio::ip::tcp::socket& socket, const std::string& msg) {

}

void RoomWriter::onUpdateClientsInfo(boost::asio::ip::tcp::socket& socket, const std::map<unsigned int, ClientData*>& clients) {
    
}
