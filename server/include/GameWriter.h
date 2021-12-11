#ifndef GAMEWRITER_H
#define GAMEWRITER_H

#include <boost/asio/ip/tcp.hpp>
#include <string>

class GameWriter {
public:
    GameWriter() = default;

    void onAction(boost::asio::ip::tcp::socket& socket, const std::string& action);

    ~GameWriter() = default;
};

#endif // GAMEWRITER_H
