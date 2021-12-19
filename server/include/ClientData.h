#ifndef CLIENTDATA_H
#define CLIENTDATA_H

#include <boost/asio/ip/tcp.hpp>
#include <string>

enum class Location {
    MainMenu,
    Room,
    Game
};

struct ClientData {
    ClientData(boost::asio::ip::tcp::socket& socket): socket(socket) {}; 

    boost::asio::ip::tcp::socket& socket;
    std::string id;
    std::pair<Location, std::string> position;
    std::string nickname;
};

#endif // CLIENTDATA_H
