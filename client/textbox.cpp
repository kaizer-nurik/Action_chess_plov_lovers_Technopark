#include <SFML/Graphics.hpp>
#include "textbox.hpp"

Textbox::Textbox(const sf::Font &font, int max_box_length, int char_size, sf::String hint_msg, sf::Vector2f pos, sf::Vector2f size) : max_length(max_box_length), hint(hint_msg)
{

    Textbox::textbox.setFont(font);
    Textbox::textbox.setCharacterSize(char_size);
    
    Textbox::textbox.setPosition(pos);
    Textbox::textbox.setString(Textbox::hint);
    Textbox::box.left = pos.x;
    Textbox::box.top = pos.y;
    Textbox::box.width = size.x;
    Textbox::box.height = size.y;
}

sf::String Textbox::getText()
{ //https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1String.php Юра поменяй на тот формат string
    return text;
}

void Textbox::checkFocus(sf::RenderWindow &window)
{
    sf::Vector2i pos = sf::Mouse::getPosition(window);
    Textbox::setFocus(Textbox::box.contains(window.mapPixelToCoords(pos)));
    //std::cout << Textbox::box.contains(window.mapPixelToCoords(pos)) << std::endl;
}
void Textbox::setFocus(bool state)
{
    Textbox::focus = state;
    if (!Textbox::focus)
    {
        show_cursor = false;
        cursor_animation.restart();
        if(text.getSize() > 0){
            Textbox::textbox.setFillColor(sf::Color::Black);
            fit_in_box(text);
        }
        else{
        Textbox::textbox.setFillColor(sf::Color(100,100,100));
        fit_in_box(hint);
        }
    }
    else
    {
        Textbox::textbox.setFillColor(sf::Color::Black);
        fit_in_box(text);
}
}
void  Textbox::fit_in_box(const sf::String& str){
    to_show = text;
    textbox.setString(to_show);
    size_t len_del = 0;
    while(textbox.getGlobalBounds().width > box.width - BOX_EDGE_OFFSET){
            to_show = text.substring(text.getSize() - max_length + len_del,max_length+len_del);
            textbox.setString(to_show);
            len_del++;

        }

    
    
}

void Textbox::draw(sf::RenderWindow &window)
{   
    if(focus){
        if(cursor_animation.getElapsedTime().asMilliseconds()>CURSOR_ANIMATION_TIME){
            show_cursor ^= 1;
            cursor_animation.restart();
        }
    }
    to_show_anim = (show_cursor)? (to_show +'|'):to_show;
    textbox.setString(to_show_anim);
    window.draw(Textbox::textbox);
}

void Textbox::vvod(sf::Event input)
{
    if (focus)
    {
        unsigned int charTyped = input.text.unicode;
        //std::cout << charTyped << std::endl;
        //std::cout << focus << std::endl;

        if (charTyped == BACKSPACE_KEY)
        {
            if (text.getSize() > 0)
            {
                text.erase(text.getSize()-1, 1);
            }
        }
        else if (charTyped == ENTER_KEY || charTyped == ESCAPE_KEY)
        {
            setFocus(false);
        }

        else if (charTyped > 30 && (charTyped < 127 || charTyped > 159))
        {

            if (charTyped != BACKSPACE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY && text.getSize() < MAX_STR_SIZE)
            {
                text += charTyped;
            }
            //std::cout << text.toAnsiString() << std::endl;
            
        }
        fit_in_box(text);
    }
}