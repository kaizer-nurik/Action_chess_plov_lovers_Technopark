#ifndef CLIENTDATA_H
#define CLIENTDATA_H

#include <boost/asio.hpp>
#include <string>

enum class Location {
    MainMenu,
    Room,
    Game
};

struct ClientData {
    ClientData(boost::asio::ip::tcp::socket& socket): m_socket(socket) {}; 

    boost::asio::ip::tcp::socket& m_socket;
    unsigned int m_id;
    std::pair<Location, unsigned int> m_position;
    std::string m_nickname;
};

#endif // CLIENTDATA_H
