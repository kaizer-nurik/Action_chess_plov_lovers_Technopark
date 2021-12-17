#pragma once
#include <SFML/Graphics.hpp>


enum mouseState  {
    FAR,
    OVER,
    PRESSED
};


class Button {
public:
	Button(const sf::Font &font, int char_size, sf::String str, sf::Vector2f pos, sf::Vector2f size, sf::RenderWindow *window, sf::Color text_cl, sf::Color normal_cl, sf::Color over_cl, sf::Color pressed_cl, void callback(sf::RenderWindow *window));
    void setText(const sf::String& str);

    void set_color(sf::Color color);
	void check_mouse_pos();
    void check_click();
	void draw();
    void setCallback(void (*callback)(sf::RenderWindow *window));
    void changeColor();
    void (*callback)(sf::RenderWindow *window);
	
private:
    sf::Color normal_cl, over_cl, pressed_cl;
    sf::RenderWindow *window;
    mouseState mouse_state = FAR;
	sf::Text caption;
	sf::RectangleShape box;
};
