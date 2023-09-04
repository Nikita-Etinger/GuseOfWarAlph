// Landscape.h
#pragma once
#include "Map.h"
#include "Config.h"

class LandScape : public Map {
public:
    LandScape(sf::RenderWindow& window);

    //void loadMapFromFile() override;
    void run() override;

private:
    
    void handleEvents();
    void update();
    void render();
};

