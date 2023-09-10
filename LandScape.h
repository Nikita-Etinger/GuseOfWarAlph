
#pragma once
#include "Map.h"
#include "Player.h"//projectile.h встроен





class LandScape : public Map {
public:
    LandScape(sf::RenderWindow& window);
    std::vector<std::vector<int>>& getMap();
    void run() override;
    

private:
    
    sf::RenderTexture mapTexture;
    sf::Sprite mapSprite;
    std::vector<Projectile> projectile;
    std::vector<Player> players;
    void handleEvents();
    void update();
    void render();
    int mousePosX;
    int mousePosY;
    bool flagUpdate = 1;
    void updateMapTexture();
    

};

