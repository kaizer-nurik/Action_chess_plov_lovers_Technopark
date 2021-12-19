#include "chess_game.hpp"
#include "Gamesession.hpp"
#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif

Texture figures;
// std::string index_to_str(int index)
// {
//     char letter = (index / 8) + 'A';
//     char number = (index % 8) + '1';
//     std::string str_coords = "";
//     str_coords += letter;
//     str_coords += number;
//     return str_coords;
// }

Vector2i get_chess_pos(Vector2f pos){
    if (((pos.x>=277) && (pos.x<=(277+65*8))) && ((pos.y>=(618-65*8)) && (pos.y<=(618)))){
        return Vector2i((pos.x - 277) / 65, (618 - pos.y) / 65);
    }
    else{
        return Vector2i(-1,-1);
    }
}

void set_mid_pos(Vector2f pos,Sprite& im){
    //im.setPosition(pos);
    im.setPosition(pos.x - im.getGlobalBounds().width/2,pos.y - im.getGlobalBounds().height/2);
}
void chess_game(sf::RenderWindow &window)
{

    figures.loadFromFile("images/chess_figures.png");
    figures.setSmooth(true);
    Texture background_image;
    background_image.loadFromFile("images/chess_board.png");
    background_image.setSmooth(true);
    


    Sprite background(background_image);
    sf::Font font;
    font.loadFromFile("fonts/gost.ttf");
    Sprite *focused = NULL;
    Text turn_msg;
    Text end_msg;
    turn_msg.setColor(Color::White);
    end_msg.setColor(Color::White);
    turn_msg.setFont(font);
    end_msg.setFont(font);
    turn_msg.setCharacterSize(50);
    end_msg.setCharacterSize(50);
    turn_msg.setPosition(877,56);
    end_msg.setPosition(877,300);
    turn_msg.setString(L"Ход Белых");
    end_msg.setString(L"");



    std::string id0 = "0";
    std::string id1 = "1";
    std::string id2 = "2";
    GameSession game(id0, id1, id2);

    figure_color turn = WHITE;
    bool moving = false;
    Vector2f lastpos;
    int index;
    int new_index;
    Vector2f pos;
    return_after_move answer;

    bool nado = true;
    game.table.set_coords();
    while (window.isOpen()&&nado)
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
                
                    if (moving)
                    {
                        
                        pos = window.mapPixelToCoords(Mouse::getPosition(window));
                        set_mid_pos(pos,game.table.get_table()[index]->image);
                        
                    }
                    
                break;
            }
            case Event::MouseButtonPressed:
            {
                if (e.key.code == Mouse::Left)
                {
                    pos = window.mapPixelToCoords(Mouse::getPosition(window));
                    if (!moving)
                    {
                        Vector2i chess_pos = get_chess_pos(pos);
                        std::cout << chess_pos.x << ' ' << chess_pos.y << std::endl;
                        if ((chess_pos.x < 8) && (chess_pos.x >= 0) && (chess_pos.y < 8) && (chess_pos.y >= 0))
                        {
                            index = chess_pos.x + chess_pos.y * 8;
                            std::cout << index << std::endl;
                            if (game.table.get_table()[index] != NULL)
                            {
                                lastpos = game.table.get_table()[index]->image.getPosition();
                                moving = true;
                                focused = &game.table.get_table()[index]->image;
                                set_mid_pos(pos,game.table.get_table()[index]->image);
                            }
                        }
                    }
                    else
                    {
                        set_mid_pos(pos,game.table.get_table()[index]->image);
                    }
                }
#ifdef DEBUG
                sf::Vector2i lp = sf::Mouse::getPosition(window);
                std::cout << lp.x << ' ' << lp.y << std::endl;
#endif

                break;
            }
            case Event::MouseButtonReleased:
            {
                if (e.key.code == Mouse::Left)
                {
                    if(moving)
                    {
                        focused = NULL;
                        moving = false;
                        pos = window.mapPixelToCoords(Mouse::getPosition(window));

                        Vector2i chess_pos = get_chess_pos(pos);
                        std::cout << chess_pos.x << ' ' << chess_pos.y << std::endl;

                        if ((chess_pos.x < 8) && (chess_pos.x >= 0) && (chess_pos.y < 8) && (chess_pos.y >= 0))
                        {
                            new_index = chess_pos.x + chess_pos.y * 8;
                            std::string str_move = index_to_str(index)+index_to_str(new_index);
                            std::cout << str_move << std::endl;
                            if (turn  == WHITE){
                                answer = game.makeMove(str_move,id1);
                                std::cout << "WHITE" << std::endl;
                            }
                            else{
                                answer = game.makeMove(str_move,id2);
                                std::cout << "BLACK" << std::endl;
                            }
                            if(answer.moveStatus != MOVE_ERROR){
                                if (turn == WHITE){
                                    turn = BLACK;
                                    turn_msg.setString(L"Ход Черных");
                                }
                                else{
                                    turn = WHITE;
                                    turn_msg.setString(L"Ход Белых");
                                }
                                
                                set_mid_pos(Vector2f(310+(answer.move_to%8) *65,585-(answer.move_to/8) *65),game.table.get_table()[new_index]->image);
                                switch (answer.moveStatus)
                                {
                                case MOVE_CAST:
                                {
                                    game.table.set_coords();
                                    end_msg.setString(L"Рокировка");
                                    break;
                                }
                                case MOVE_EAT:
                                {
                                    end_msg.setString(L"Съеден");
                                    break;
                                }
                                case MOVE_CHECK_WHITE:{
                                    end_msg.setString(L"Шах белым");
                                    break;
                                }
                                case MOVE_CHECK_BLACK:{
                                    end_msg.setString(L"Шах Черным");
                                    break;
                                }
                                case MOVE_CHECKMATE_WHITE:{
                                    end_msg.setString(L"Мат Белым");
                                    break;
                                }
                                case MOVE_CHECKMATE_BLACK:{
                                    end_msg.setString(L"Мат Черным");
                                    break;
                                }
                                case MOVE_DRAW:{
                                    end_msg.setString(L"Ничья");
                                    break;
                                }
                                case MOVE_ENPASSANT:
                                {
                                    end_msg.setString(L"Взятие на \n проходе");
                                    break;
                                }
                                case WHITE_LEAVE:
                                {
                                    end_msg.setString(L"Белый вышел");
                                    break;
                                }
                                case BLACK_LEAVE:
                                {
                                    end_msg.setString(L"Черный вышел");
                                    break;
                                }
                                default:
                                    end_msg.setString(L"");
                                    break;
                                }
                                
                               
                            }
                            else{
                                new_index = -1;
                                game.table.get_table()[index]->image.setPosition(lastpos);
                            }

                        }
                        else{
                            game.table.get_table()[index]->image.setPosition(lastpos);
                        }
                    }

                }
                break;
            }
            }
        }

        window.clear();
        window.draw(background);
        game.table.Draw_table(window);
        window.draw(turn_msg);
        window.draw(end_msg);
        if (focused != NULL)
        {
            window.draw(*focused);
        }
        
        window.display();
    }
}