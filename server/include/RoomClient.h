#ifndef ROOMCLIENT_H
#define ROOMCLIENT_H

#include <boost/asio.hpp>
#include <string>

class RoomClient {
public:
    RoomClient(boost::asio::ip::tcp::socket& socket);
    void onMessage(std::string msg);

private:

    boost::asio::ip::tcp::socket& m_socket;
};

#endif // ROOMCLIENT_H
