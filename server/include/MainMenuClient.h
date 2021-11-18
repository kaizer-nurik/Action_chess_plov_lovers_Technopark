#ifndef MAINMENUCLIENT_H
#define MAINMENUCLIENT_H

#include <boost/asio.hpp>

class MainMenuClient {
public:
    MainMenuClient(boost::asio::ip::tcp::socket& socket);
    void onRequestRoomsInfo();

private:
    boost::asio::ip::tcp::socket& m_socket;
};

#endif // MAINMENUCLIENT_H
