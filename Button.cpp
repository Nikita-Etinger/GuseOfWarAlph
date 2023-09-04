#include "Button.h"



Button::Button(sf::Vector2f size, sf::Vector2f position, sf::Color colorBack, sf::Color colorFont, int fontSize,std::string newText) :
	rectangle(size)
{
	this->colorFont = colorFont;
	this->fontSize = fontSize;
	rectangle.setFillColor(colorBack);
	rectangle.setPosition(position);
	rectangle.setOutlineColor(colorFont);
	rectangle.setOutlineThickness(2);
	text.setFillColor(colorFont);
	text.setCharacterSize(fontSize);
	text.setString(newText);





}

void Button::render(sf::RenderWindow& window)
{
	window.draw(rectangle);
	text.setFont(font);
	font.loadFromFile("font.ttf");
	text.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2 - text.getGlobalBounds().getSize().x/2, rectangle.getPosition().y+rectangle.getSize().y/2 - text.getGlobalBounds().getSize().y/1.5);
	window.draw(text);


}

void Button::changeBackColor(sf::Color colorBack)
{
	rectangle.setFillColor(colorBack);
}

void Button::setFontColor(sf::Color color)
{
	this->colorFont = color;
	text.setFillColor(color);
}
void Button::setText(std::string& texts) {
	text.setString(texts);
}

sf::RectangleShape& Button::getRectangle()
{
	return rectangle;
}

sf::Color Button::getFontColor()
{
	return colorFont;
}

sf::Color Button::getBackColor()
{
	return rectangle.getFillColor();
}

std::string Button::getString()
{
	return text.getString();
}
