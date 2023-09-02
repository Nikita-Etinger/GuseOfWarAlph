#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Config.h"
#include "Button.h"
class Game
{
private:
	sf::RenderWindow window;
	std::vector<Button> buttons;
	std::string namesButton[3]{ "Play","Map editor","Exit" };
public:
	Game();

	void run();
	void update();
	void render();
};

