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
    Room(const std::string& roomId, unsigned int maxClientNumber);

    unsigned int getCurrentClientNumber();
    unsigned int getMaxClientNumber();

    void addClient(const ClientData& clientData) override;
    void removeClient(const std::string& id) override;
    boost::asio::ip::tcp::socket& getClientSocket(const std::string& id) override;
    bool haveClient(const std::string& id) override;
    const ClientData* getClient(const std::string& id) override;

    void broadcast(const std::string& id, const std::string&  msg);
    void startGame();
    bool gameStarted();

    ~Room();

private:
    std::string m_id;
    RoomWriter m_writer;

    std::map<const std::string, const ClientData*> m_clients;
    unsigned int m_currentClientNumber = 0;
    unsigned int m_maxClientNumber;
    
    Game m_game;
    bool m_gameStarted = false;
};

#endif // ROOM_H
