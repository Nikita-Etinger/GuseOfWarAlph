#pragma once

#include "Particles.h"


class Projectile
{
private:
    float& timeF;
    bool explosion=0;
    float velocityX;
    float velocityY;
    float speed;
    float radius=10;
    int size=3;
    float positionX = 0;

    float positionY=0;
    float timeRender = 0;
    sf::Sprite sprite;
    sf::Texture texture;
    float rotation;
    std::vector<Particles>& particlesF;
    float timeLeft = 0;
public:
    bool isActive();
    Projectile(float positionX, float positionY, float velocityXS, float velocityYS, float speed,float& time, std::vector<Particles>& particles);
    void applyVelocity();
    void update();
    bool getStatus();
    vt getCoordinate();
    float getRadius();
    int getSize();
    void explosions();
    void draw(sf::RenderWindow& window);
    bool operator==(Projectile& other);
    bool operator!=(Projectile& other);
    void outOfMap();
    //копирование только ссылки
    //void operator=(Projectile& other);
};