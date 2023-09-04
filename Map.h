#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include <fstream>
#include "sstream"

class Map {
public:
    Map(sf::RenderWindow& windowS);

    virtual void run()=0;

protected:
    sf::RenderWindow& window;
    std::vector<std::vector<int>> map;
    bool needClose;
    std::vector<Button> buttons;
    sf::Color colors[4];

    //virtual void handleEvents() = 0;
    //virtual void update() = 0;
    //virtual void render() = 0;
    //virtual void saveMapToFile() = 0;
    virtual void loadMapFromFile(); // Общая реализация для загрузки карты

    virtual void colorMenu() = 0;
};