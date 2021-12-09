#ifndef ROOM_H
#define ROOM_H

#include <boost/asio/ip/tcp.hpp>
#include <map>
#include <string>

#include "ClientData.h"
#include "Game.h"
#include "RoomWriter.h"

class Room: public IClientMover {
public:
    Room(unsigned int maxClientNumber);

    unsigned int getCurrentClientNumber();
    unsigned int getMaxClientNumber();

    void addClient(const ClientData& clientData) override;
    void removeClient(std::string id) override;
    boost::asio::ip::tcp::socket& getClientSocket(std::string id) override;
    bool haveClient(std::string id) override;

    void broadcast(const ClientData& clientData, std::string msg);
    void startGame();
    bool gameStarted();

    ~Room();

private:
    RoomWriter m_writer;

    std::map<std::string, const ClientData*> m_clients;
    unsigned int m_currentClientNumber = 0;
    unsigned int m_maxClientNumber;
    
    Game m_game;
};

#endif // ROOM_H
