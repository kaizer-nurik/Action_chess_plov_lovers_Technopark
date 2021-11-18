#ifndef MAINMENU_H
#define MAINMENU_H

#include <boost/asio.hpp>
#include <map>

#include "ClientData.h"
#include "ClientMover.h"
#include "MainMenuWriter.h"
#include "RoomController.h"

class MainMenu: public IClientMover {
public:
    MainMenu();
    
    std::map<unsigned int, Room> getAllRooms();

    void addClient(const ClientData& clientData) override;
    void removeClient(unsigned int id) override;
    boost::asio::ip::tcp::socket& getClientSocket(unsigned int id) override;
    bool haveClient(unsigned int id) override;

private:
    MainMenuWriter m_writer;
    std::map<unsigned int, ClientData*> m_clients;
    RoomController roomController;
};

#endif // MAINMENU_H
