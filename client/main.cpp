#include <SFML/Graphics.hpp>
#include <time.h>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "menu_window.hpp"
#include "chess_game.hpp"

#include "Client.hpp"

using namespace sf;

#define DEBUG

#ifdef DEBUG
    #include <iostream>
#endif


int main() {
    boost::asio::io_context io_context;
    Client c(io_context, "127.0.0.1", "8080");
    std::thread thread(boost::bind(&boost::asio::io_context::run, &io_context));

    RenderWindow window(VideoMode(1080, 720), "PlovLovers Chess game");

    while(window.isOpen()){
        menu_window(window);
        if(window.isOpen()){
            chess_game(window);
        }
    
    }

    thread.join();

    return 0;
}