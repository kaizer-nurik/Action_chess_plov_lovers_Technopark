#ifndef GAME_H
#define GAME_H

#include <boost/asio.hpp>
#include <map>
#include <string>

#include "ClientData.h"
#include "ClientMover.h"
#include "GameClient.h"

class Game: public IClientMover {
public:
    Game();

    void addClient(const ClientData& clientData) override;
    void removeClient(unsigned int id) override;
    boost::asio::ip::tcp::socket& getClientSocket(unsigned int id) override;
    bool haveClient(unsigned int id) override;

    void broadcast(const ClientData& clientData, std::string msg);
    void makeAction(const ClientData& clientData, std::string msg);
    void start();
    void onEnd();

private:
    std::map<unsigned int, GameClient> m_clients;
};

#endif // GAME_H
