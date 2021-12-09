#ifndef GAME_H
#define GAME_H

#include <boost/asio/ip/tcp.hpp>
#include <map>
#include <string>

#include "ClientData.h"
#include "ClientMover.h"
#include "GameWriter.h"

class Game: public IClientMover {
public:
    Game() = default;

    void addClient(const ClientData& clientData) override;
    void removeClient(std::string id) override;
    boost::asio::ip::tcp::socket& getClientSocket(std::string id) override;
    bool haveClient(std::string id) override;

    void broadcast(const ClientData& clientData, std::string msg);
    void makeAction(const ClientData& clientData, std::string msg);
    void start();
    void onEnd();

    ~Game() = default;

private:
    GameWriter m_writer;
    
    std::map<std::string, ClientData*> m_clients;
};

#endif // GAME_H
