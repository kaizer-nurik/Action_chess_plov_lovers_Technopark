#include <SFML/Graphics.hpp>
#include "button.hpp"

Button::Button(const sf::Font &font, int char_size, sf::String str, sf::Vector2f pos, sf::Vector2f size, sf::RenderWindow *window, sf::Color text_cl, sf::Color normal_cl, sf::Color over_cl, sf::Color pressed_cl, void callback(sf::RenderWindow *window)) : window(window), normal_cl(normal_cl), over_cl(over_cl), pressed_cl(pressed_cl)
{
    Button::setCallback(callback);
    Button::caption.setColor(text_cl);
    Button::caption.setFont(font);
    Button::caption.setCharacterSize(char_size);
    Button::caption.setString(str);
    Button::caption.setPosition(pos);

    Button::box.setPosition(pos);
    Button::box.setSize(size);

    sf::Vector2f text_pos(pos.x + abs(box.getLocalBounds().width - caption.getLocalBounds().width) / 2, pos.y + abs(box.getLocalBounds().height - caption.getLocalBounds().height) / 2);
    Button::caption.setPosition(text_pos);

    Button::window = window;
    Button::changeColor();
}
void Button::setCallback(void (*callback)(sf::RenderWindow *window))
{
    Button::callback = callback;
}

void Button::setText(const sf::String &str)
{
    Button::caption.setString(str);
}

void Button::set_color(sf::Color color)
{
    Button::box.setFillColor(color);
}

void Button::changeColor()
{
    switch (mouse_state)
    {
    case FAR:
        set_color(normal_cl);
        break;
    case OVER:
        set_color(over_cl);
        break;
    case PRESSED:
        set_color(pressed_cl);
        break;
    }
}
void Button::check_mouse_pos()
{
    if (mouse_state != PRESSED)
    {
        sf::Vector2i pos = sf::Mouse::getPosition(*window);
        Button::mouse_state = (Button::box.getGlobalBounds().contains(Button::window->mapPixelToCoords(pos))) ? OVER : FAR;
        Button::changeColor();
    }
}
void Button::check_click()
{
    if (mouse_state == PRESSED && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i pos = sf::Mouse::getPosition(*window);
        Button::mouse_state = (Button::box.getGlobalBounds().contains(Button::window->mapPixelToCoords(pos))) ? OVER : FAR;
        if (mouse_state == OVER)
        {
            callback(window);
        }
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouse_state == OVER)
    {
        Button::mouse_state = PRESSED;
    }
    Button::changeColor();
}
void Button::draw()
{
    window->draw(box);
    window->draw(caption);
}
