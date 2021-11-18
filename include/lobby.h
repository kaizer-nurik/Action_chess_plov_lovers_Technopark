#ifndef LOBBY_H
#define LOBBY_H
#include <string>
#include <vector>

#include "game.h"
#include "lobbychat.h"

class Lobby
{
private:
    std::vector<User> users;
    Game game;
    LobbyChat chat;
    std::string lobbyName;
    int lobbyId;


public:
    Lobby(/* args */);
    ~Lobby();
    std::vector<User> getUsers();
    std::string getLobbyName();
    int getLobbyId();
    bool addUser();
    bool kickUser();


};

Lobby::Lobby(/* args */)
{
}

Lobby::~Lobby()
{
}

#endif // LOBBY_H