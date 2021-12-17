#include <SFML/Graphics.hpp>
#include <time.h>

#include "menu_window.hpp"
#include "chess_game.hpp"
using namespace sf;

#define DEBUG

#ifdef DEBUG
    #include <iostream>
#endif


int main()
{

    RenderWindow window(VideoMode(1080, 720), "PlovLovers Chess game");

    while(window.isOpen()){
        menu_window(window);
        if(window.isOpen()){
            chess_game(window);
        }
    
    }




    return 0;
}