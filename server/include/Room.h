#ifndef ROOM_H
#define ROOM_H

#include <boost/asio.hpp>
#include <map>
#include <string>

#include "ClientData.h"
#include "Game.h"
#include "RoomClient.h"

class Room: public IClientMover {
public:
    Room(unsigned int maxClientNumber);

    unsigned int getCurrentClientNumber();
    unsigned int getMaxClientNumber();

    void addClient(const ClientData& clientData) override;
    void removeClient(unsigned int id) override;
    boost::asio::ip::tcp::socket& getClientSocket(unsigned int id) override;
    bool haveClient(unsigned int id) override;
    
    void broadcast(const ClientData& clientData, std::string msg);
    void startGame();
    bool gameStarted();

private:
    std::map<unsigned int, RoomClient> m_clients;
    unsigned int currentClientNumber = 0;
    unsigned int maxClientNumber;
    Game game;
};

#endif // ROOM_H
