#ifndef ROOMWRITER_H
#define ROOMWRITER_H

#include <boost/asio.hpp>
#include <string>

#include "ClientData.h"

class RoomWriter {
public:
    void onMessage(boost::asio::ip::tcp::socket& socket, const std::string& msg);
    void onUpdateClientsInfo(boost::asio::ip::tcp::socket& socket, const std::map<unsigned int, ClientData*>& clients);
};

#endif // ROOMWRITER_H
