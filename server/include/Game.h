#ifndef GAME_H
#define GAME_H

#include <boost/asio/ip/tcp.hpp>
#include <map>
#include <string>

#include "ClientData.h"
#include "ClientMover.h"
#include "GameLogic.h"
#include "GameWriter.h"

class Game: public IClientMover {
public:
    Game(const std::string& id);

    void addClient(const ClientData& clientData) override;
    const ClientData* removeClient(const std::string& id) override;
    boost::asio::ip::tcp::socket& getClientSocket(const std::string& id) override;
    bool haveClient(const std::string& id) override;
    const ClientData* getClient(const std::string& id) override;

    void broadcast(const std::string& id, const std::string& response);
    return_after_move makeAction(const std::string& id, const std::string& action);
    void start();
    void onEnd();

    ~Game() = default;

private:
    const std::string m_id;

    GameSession *m_session;
    GameWriter m_writer;
    
    std::map<const std::string, const ClientData*> m_clients;
};

#endif // GAME_H
