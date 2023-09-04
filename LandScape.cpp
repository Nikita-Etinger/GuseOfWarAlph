#include "LandScape.h"




LandScape::LandScape(sf::RenderWindow& windows) : Map(windows)
{
    map.resize(WINDOW_H / BLOCK_SIZE, std::vector<int>(WINDOW_W / BLOCK_SIZE, 0));
}

void LandScape::run()
{
    loadMapFromFile();
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}


void LandScape::update()
{


}

void LandScape::render()
{
    window.clear();
    for (auto& but : buttons) {
        but.render(window);
    }
    // Отрисовка заполненных клеток
    for (int y = 0; y < map.size(); ++y) {
        for (int x = 0; x < map[y].size(); ++x) {
            int value = map[y][x];
            if (value >= 1 && value <= 4) {
                sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
                block.setPosition(x * BLOCK_SIZE, y * BLOCK_SIZE);
                block.setFillColor(colors[value - 1]); 
                window.draw(block);
            }
        }
    }

    window.display();
}

void LandScape::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}
