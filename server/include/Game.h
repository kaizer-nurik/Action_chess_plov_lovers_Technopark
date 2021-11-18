#ifndef GAME_H
#define GAME_H

#include <boost/asio.hpp>
#include <map>
#include <string>

#include "ClientData.h"
#include "ClientMover.h"
#include "GameWriter.h"

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
    GameWriter m_writer;
    std::map<unsigned int, ClientData*> m_clients;
};

#endif // GAME_H
