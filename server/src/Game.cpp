#include "Game.h"

void Game::addClient(const ClientData& clientData) {}

void Game::removeClient(std::string id) {}

boost::asio::ip::tcp::socket& Game::getClientSocket(std::string id) {}

bool Game::haveClient(std::string id) {}

void Game::broadcast(const ClientData& clientData, std::string msg) {}

void Game::makeAction(const ClientData& clientData, std::string msg) {}

void Game::start() {}

void Game::onEnd() {}
