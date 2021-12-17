#include <SFML/Graphics.hpp>
#include <time.h>

#include "menu_window.hpp"
#include "textbox.hpp"
#include "button.hpp"
using namespace sf;

bool nado = true;

#ifdef DEBUG
    #include <iostream>
#endif

void button_callback(sf::RenderWindow *window){
    #ifdef DEBUG
        std::cout<<"Pressed"<<std::endl;
    #endif

    nado = false;
}

void menu_window(sf::RenderWindow& window){
    nado = true;
    Texture menu;
    menu.loadFromFile("images/menu.jpg");
    menu.setSmooth(true);
    Sprite background(menu);
    sf::Font font;
    font.loadFromFile("gost.ttf");
    Textbox IdBox(font, 20, 30, L"Введите ID", Vector2f(402, 352), Vector2f(262, 39));
    Textbox RoomBox(font, 20, 30, L"Введите ID", Vector2f(402, 452), Vector2f(262, 39));
    Button StartButton(font,20,L"Подключиться",Vector2f(430,600),Vector2f(200,50),&window, Color::Black,Color(100,100,100),Color(130,130,130),Color(150,150,150),button_callback);

    while (nado)
    {

        Event e;
        while (window.pollEvent(e))
        {
            switch (e.type)
            {
            case Event::Closed:
            {
                window.close();
                break;
            }
            case Event::MouseMoved:
                {
                    StartButton.check_mouse_pos();
                    break;
                }
            case Event::MouseButtonPressed:
            {

                IdBox.checkFocus(window);
                RoomBox.checkFocus(window);
                StartButton.check_click();
                #ifdef DEBUG
                    sf::Vector2i lp = sf::Mouse::getPosition(window);
                    std::cout << lp.x << ' ' << lp.y << std::endl;
                #endif
                
                break;
            }
            case Event::MouseButtonReleased:
            {
                StartButton.check_click();
                break;
            }
            case Event::TextEntered:
            {
                IdBox.vvod(e);
                RoomBox.vvod(e);
                break;
            }
            }

        }
    
        window.clear();
        window.draw(background);
        IdBox.draw(window);
        RoomBox.draw(window);
        StartButton.draw();
        window.display();
    }

    window.clear();
}