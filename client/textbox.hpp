#pragma once
#include <SFML/Graphics.hpp>

#define MAX_STR_SIZE 256
#define BOX_EDGE_OFFSET 5
#define CURSOR_ANIMATION_TIME 500
#define BACKSPACE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27


class Textbox {
public:
	Textbox(const sf::Font& font,int max_box_length, int char_size, sf::String hint_msg, sf::Vector2f pos,sf::Vector2f size);
    sf::String getText();


	// Change selected state:
	void setFocus(bool state);
	void checkFocus(sf::RenderWindow &window);
	void fit_in_box(const sf::String& str);
	void draw(sf::RenderWindow &window);

	void vvod(sf::Event input);
private:
	bool show_cursor = false;
	sf::Clock cursor_animation;
	sf::Text textbox;
	sf::Rect<float> box;
	sf::String text;
	sf::String to_show;
	sf::String to_show_anim;
    sf::String hint;
	bool focus = false;
	int max_length = 0;


};
