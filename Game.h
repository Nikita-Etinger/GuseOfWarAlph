#pragma once
#include <SFML/Graphics.hpp>
#include "Config.h"
#include <vector>
#include "MapEditor.h"
#include "Button.h"

class Game
{
private:
	sf::RenderWindow window;
	std::vector<Button> buttons;
	std::string namesButton[3]{ "PLAY","MAP EDITOR","EXIT" };
	MapEditor mapEditor;
	rs backGround;
	//LandScape landScape;

public:
	Game();
	void actEvent();
	void run();
	void update();
	void render();
};

