#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include <boost/asio.hpp>
#include <string>

class GameClient {
public:
    GameClient(boost::asio::ip::tcp::socket& socket);
    void onEvent(std::string msg);

private:
    boost::asio::ip::tcp::socket& m_socket;
};

#endif // GAMECLIENT_H
