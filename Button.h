#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
class Button
{
private:
	sf::RectangleShape rectangle;
	sf::Font font;
	sf::Text text;
	sf::Vector2f size;
	sf::Color colorFont;
	int fontSize;

public:
	Button(sf::Vector2f size, sf::Vector2f position, sf::Color colorBack, sf::Color colorFont, int fontSize,std::string newText);
	void render(sf::RenderWindow& window);
	void changeBackColor(sf::Color colorBack);
	void setFontColor(sf::Color color);
	sf::RectangleShape& getRectangle();
	sf::Color getFontColor();
	sf::Color getBackColor();
	std::string getString();


};

