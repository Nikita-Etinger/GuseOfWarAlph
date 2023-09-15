
#pragma once
#include "Map.h"
#include "Player.h"//projectile.h встроен





class LandScape : public Map {
public:
    LandScape(sf::RenderWindow& window);
    std::vector<std::vector<int>>& getMap();
    void run() override;
    

private:
    std::vector<Particles> particlesF;
    std::vector<Projectile> projectile;
    std::vector<Player> players;
    void handleEvents();
    float stabilityTimeMin = 0;
    float stabilityTimeMax = 0;
    float stabilityTimeSr = 0;
    int indexPlayer = 0;
    void update();
    void render();

    int mousePosX;
    int mousePosY;
    bool flagUpdate = 1;
    void scanCollicionProjectile();

    bool needClose = 0;
};

