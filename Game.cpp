#include "Game.h"
#include "MapEditor.h"
#include "Config.h"
Game::Game() :window(sf::VideoMode(WINDOW_W, WINDOW_H), "SFML window")
{
}

void Game::run()
{
	MapEditor mapEditor(window);
	rs backGround(vt(WINDOW_W, WINDOW_H));
	
	for (int i = 0; i < 2; i++) {
		buttons.push_back(Button(sf::Vector2f(BUTTON_SIZE, BUTTON_SIZE / 2),
			sf::Vector2f(window.getSize().x/2-BUTTON_SIZE/2, BUTTON_SIZE+ BUTTON_SIZE*i),
			sf::Color::Color(130, 78, 100, 255),
			sf::Color::Color(255, 255, 255, 255),
			10, namesButton[i]));
	}
	while (window.isOpen()) {
		update();
		render();
	}

	
	
}
void Game::update() {

}
void Game::render() {
	window.clear();
	for (auto& b : buttons) {
		b.render(window);
	}
	window.display();
}
