#include "Button.h"
#include "config.h"



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
	text.setPosition(position.x + (size.x - text.getLocalBounds().width) / 2.0f, position.y + (size.y - text.getLocalBounds().height) / 2.0f);



}

void Button::render(sf::RenderWindow& window)
{
	window.draw(rectangle);
	text.setFont(font);
	font.loadFromFile("arial.ttf");
	text.setPosition(rectangle.getPosition().x + (size.x + text.getLocalBounds().width) / 2.0f, rectangle.getPosition().y + (size.y + text.getLocalBounds().height) / 2.0f);
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
