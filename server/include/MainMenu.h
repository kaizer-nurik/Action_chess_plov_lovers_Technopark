#ifndef MAINMENU_H
#define MAINMENU_H

#include <boost/asio/ip/tcp.hpp>
#include <map>

#include "ClientData.h"
#include "ClientMover.h"
#include "RoomController.h"

class MainMenu: public IClientMover {
public:
    MainMenu() = default;
    
    void addClient(const ClientData& clientData) override;
    const ClientData* removeClient(const std::string& id) override;
    boost::asio::ip::tcp::socket& getClientSocket(const std::string& id) override;
    bool haveClient(const std::string& id) override;
    const ClientData* getClient(const std::string& id) override;

    ~MainMenu() = default;

public:
    RoomController roomController;

private:
    std::map<std::string, const ClientData*> m_clients;
};

#endif // MAINMENU_H
