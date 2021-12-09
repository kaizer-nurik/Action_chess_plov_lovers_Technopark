#ifndef GAMEWRITER_H
#define GAMEWRITER_H

#include <boost/asio/ip/tcp.hpp>
#include <string>

class GameWriter {
public:
    GameWriter() = default;

    void onEvent(boost::asio::ip::tcp::socket& socket, const std::string& msg);

    ~GameWriter() = default;
};

#endif // GAMEWRITER_H
