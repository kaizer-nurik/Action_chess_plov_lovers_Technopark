#include "Game.h"

Game::Game() {

}

void Game::addClient(const ClientData& clientData) {

}

void Game::removeClient(unsigned int id) {

}

boost::asio::ip::tcp::socket& Game::getClientSocket(unsigned int id) {

}

bool Game::haveClient(unsigned int id) {
    
}

void Game::broadcast(const ClientData& clientData, std::string msg) {

}

void Game::makeAction(const ClientData& clientData, std::string msg) {

}


void Game::start() {

}

void Game::onEnd() {

}
