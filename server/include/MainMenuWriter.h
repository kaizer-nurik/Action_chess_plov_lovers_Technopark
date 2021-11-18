#ifndef MAINMENUWRITER_H
#define MAINMENUWRITER_H

#include <boost/asio.hpp>

#include "Room.h"

class MainMenuWriter {
public:
    void onRequestRoomsInfo(boost::asio::ip::tcp::socket& socket, const std::map<unsigned int, Room>& rooms);
};

#endif // MAINMENUWRITER_H
