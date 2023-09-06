
#pragma once
#include "Map.h"
#include "Config.h"
#include "Player.h"
#include "Projectile.h"

class LandScape : public Map {
public:
    LandScape(sf::RenderWindow& window);
    std::vector<std::vector<int>>& getMap();
    void run() override;
    std::vector<Projectile> projectile;

private:
    std::vector<Player> players;
    void handleEvents();
    void update();
    void render();
    

};

