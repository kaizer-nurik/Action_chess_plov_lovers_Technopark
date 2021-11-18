#ifndef MAINMENU_H
#define MAINMENU_H

#include <boost/asio.hpp>
#include <map>

#include "ClientData.h"
#include "ClientMover.h"
#include "MainMenuClient.h"
#include "RoomController.h"

class MainMenu: public IClientMover {
public:
    MainMenu();
    
    std::map<unsigned int, Room> getAllRooms();

    void addClient(const ClientData& clientData) override;
    void removeClient(unsigned int id) override;
    boost::asio::ip::tcp::socket& getClientSocket(unsigned int id) override;
    bool haveClient(unsigned int id) override;

    void moveToRoom(unsigned int clientId, unsigned int roomId);
    void removeFromRoom(unsigned int clientId, unsigned int roomId);

private:
    std::map<unsigned int, MainMenuClient> m_clients;
    RoomController roomController;
};

#endif // MAINMENU_H
