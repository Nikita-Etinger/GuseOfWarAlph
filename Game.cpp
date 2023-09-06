#include "Game.h"

Game::Game() :window(sf::VideoMode(WINDOW_W, WINDOW_H), "SFML window"),mapEditor(window),backGround(vt(WINDOW_W, WINDOW_H)),landScape(window)
{
}

void Game::actEvent()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		sf::Vector2f localPosition(event.mouseButton.x, event.mouseButton.y);
		for (auto& x : buttons) {

			if (x.getRectangle().getGlobalBounds().contains(localPosition)) {
				std::string str = x.getString();
				if (str == "PLAY") {
					landScape.run();
				}
				else if (str == "MAP EDITOR") {
					mapEditor.run();
				}
				else if (str == "EXIT") window.close();
			}
		}
	}

}

void Game::run()
{
	for (int i = 0; i < 3; i++) {
		buttons.push_back(Button(sf::Vector2f(BUTTON_SIZE*5, BUTTON_SIZE*5 / 2),
			sf::Vector2f(BUTTON_SIZE, BUTTON_SIZE*2+ BUTTON_SIZE*i*3),
			sf::Color::Color(130, 78, 100, 255),
			sf::Color::Color(255, 255, 255, 255),
			40, namesButton[i]));
	}
	backGround.setFillColor(sf::Color::Blue);
	backGround.setPosition(0, 0);
	while (window.isOpen()) {
		update();
		actEvent();
		render();
	}

	
	
}
void Game::update() {

}
void Game::render() {

	window.clear();
	
	window.draw(backGround);
	for (auto& b : buttons) {
		b.render(window);
	}
	

	window.display();
}
