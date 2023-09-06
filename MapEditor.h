#pragma once
#include "Config.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "fstream"
#include <sstream> 
#include "Button.h"
#include <cstdlib>
#include <iostream>
#include "Map.h"

class MapEditor : public Map {
public:
    MapEditor(sf::RenderWindow& window);
    
    void run() override;
private:
    bool tapButton=0;
    int paintType=0;
    rs textType;
    std::string namesButton[4]{ "SAVE","PREV","NEXT","CLEAR"};
    std::string namesTypePaint[2]{ "SAND","GRASS"};
    bool isLeftMouseButtonPressed = false;
    bool isRightMouseButtonPressed = false;
    void handleEvents();
    void update();
    void render();
    void saveMapToFile();
    
    
};