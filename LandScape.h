
#pragma once
#include "Map.h"
#include "Player.h"//projectile.h �������





class LandScape : public Map {
public:
    LandScape(sf::RenderWindow& window);
    void run() override;



    bool getNeedClose();
private:
    sf::Text timeLeftText;
    sf::Font font;
    int timeLeft = 60;
    float timeSecond = 0;
    std::vector<Particles> particlesF;
    std::vector<Projectile> projectile;
    std::vector<Player> players;
    void handleEvents();
    int indexPlayer = 0;
    void update();
    void render();
    std::vector<Projectile> projectileBufer;
    int mousePosX;
    int mousePosY;
    bool flagUpdate = 1;
    void updateProjectile();
    void ParticlesCleaner();

    bool needClose = 0;
};

