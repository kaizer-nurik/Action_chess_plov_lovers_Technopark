#ifndef ROOMCLIENT_H
#define ROOMCLIENT_H

#include <boost/asio.hpp>
#include <queue>
#include <string>

class RoomClient {
public:
    RoomClient(boost::asio::ip::tcp::socket& socket);
    void onMessage(std::string msg);

private:
    void writeMessageQueue(const boost::system::error_code& err);

    boost::asio::ip::tcp::socket& m_socket;
    std::queue<std::string> m_messageQueue;
};

#endif // ROOMCLIENT_H
