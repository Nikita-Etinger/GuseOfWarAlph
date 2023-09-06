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
    sf::Color colors[9]{ sf::Color::Yellow,
        sf::Color::Green,
        sf::Color::Red,
        sf::Color::Blue,
        sf::Color::Magenta,
        sf::Color::Cyan,
        sf::Color::White,
        sf::Color(255, 128, 0),  // Оранжевый цвет 
        sf::Color(0, 255, 255)   // Ярко-голубой цвет 
    };

    //virtual void handleEvents() = 0;
    //virtual void update() = 0;
    //virtual void render() = 0;
    //virtual void saveMapToFile() = 0;
    virtual void loadMapFromFile(); // Общая реализация для загрузки карты
};