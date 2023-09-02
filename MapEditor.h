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

    void run(); // ����� ��� ������� ��������� �����

private:
    sf::RenderWindow& window;
    std::vector<std::vector<int>> map; // ������� ��� �������� �����, ��� 0 - ������ ������, 1 - �����������
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
    sf::Color::Green,   // ���� ��� �������� 1
    sf::Color::Blue,    // ���� ��� �������� 2
    sf::Color::Red,     // ���� ��� �������� 3
    sf::Color::Yellow   // ���� ��� �������� 4
    };
    void colorMenu();
};