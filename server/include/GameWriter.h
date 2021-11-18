#ifndef GAMEWRITER_H
#define GAMEWRITER_H

#include <boost/asio.hpp>
#include <string>

class GameWriter {
public:
    void onEvent(boost::asio::ip::tcp::socket& socket, const std::string& msg);
};

#endif // GAMEWRITER_H
