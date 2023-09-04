#pragma once
#include "Config.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "fstream"
#include <sstream> 
#include "Button.h"
#include <cstdlib>
#include <iostream>

#pragma once
#include "Map.h"

class MapEditor : public Map {
public:
    MapEditor(sf::RenderWindow& window);
    
    void run() override;
private:
    bool isLeftMouseButtonPressed = false;
    bool isRightMouseButtonPressed = false;
    void handleEvents();
    void update();
    void render();
    void saveMapToFile();
    void colorMenu();
    //void loadMapFromFile() override;
    
};