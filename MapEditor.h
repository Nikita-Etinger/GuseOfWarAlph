#pragma once
#include "Config.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "fstream"
#include <sstream> 
#include "Button.h"
#define random(a,b) a-rand()%(a-b+1)

class MapEditor {
public:
    MapEditor(sf::RenderWindow& windows);

    void run(); // Метод для запуска редактора карты

private:
    sf::RenderWindow& window;
    std::vector<std::vector<int>> map; // Матрица для хранения карты, где 0 - пустая клетка, 1 - заполненная
    bool isLeftMouseButtonPressed = false;
    bool isRightMouseButtonPressed = false;
    bool needClose = 0;
    void handleEvents();
    void update();
    void render();
    void saveMapToFile();
    void loadMapFromFile();
    int choiseColor = 1;

    std::vector<Button> buttons;
    sf::Color colors[4] = {
    sf::Color::Green,   // Цвет для значения 1
    sf::Color::Blue,    // Цвет для значения 2
    sf::Color::Red,     // Цвет для значения 3
    sf::Color::Yellow   // Цвет для значения 4
    };
    void colorMenu();
};