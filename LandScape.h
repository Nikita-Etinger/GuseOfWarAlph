
#pragma once
#include "Map.h"
#include "Player.h"//projectile.h встроен





class LandScape : public Map {
public:
    LandScape(sf::RenderWindow& window);
    void run() override;



    bool getNeedClose();
private:
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
    void scanCollisionProjectile();
    void ParticlesCleaner();

    bool needClose = 0;
};

