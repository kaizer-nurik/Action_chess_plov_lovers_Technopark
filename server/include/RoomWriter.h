#ifndef ROOMWRITER_H
#define ROOMWRITER_H

#include <boost/asio/ip/tcp.hpp>
#include <string>

#include "ClientData.h"

class RoomWriter {
public:
    RoomWriter() = default;

    void onMessage(boost::asio::ip::tcp::socket& socket, const ClientData& clientData, const std::string& msg);
    void onEnter(boost::asio::ip::tcp::socket& socket, const ClientData& clientData);

    ~RoomWriter() = default;
};

#endif // ROOMWRITER_H
