#pragma once

#include "Particles.h"

class Projectile
{
private:
    bool explosion=0;
    float velocityX=0;
    float velocityY=0;
    float speed=0;
    float radius=10;
    int size=3;
    float positionX = 0;

    float positionY=0;
    float timeRender = 0;
    sf::Sprite sprite;
    sf::Texture texture;
    float rotation=0;
    std::vector<Particles>& particlesF;
    float timeLeft = 0;
    float& timeF;
    std::vector<std::vector<int>> map;
public:
    sf::Clock clock;
    float time = 0;
    Projectile(const Projectile& other);
    bool isActive();
    Projectile(float positionX, float positionY, float velocityXS, float velocityYS, float speed, float& time,
        std::vector<Particles>& particles,
        std::vector<std::vector<int>>& maps);
    void applyVelocity();
    void update();
    bool isExplosion();
    vt getCoordinate();
    float getRadius();
    int getSize();
    void explosions();
    void render(sf::RenderWindow& window);
    void outOfMap();
    bool operator==(const Projectile& other) const {
        return this == &other;
    }
    Projectile& operator=(const Projectile& other)
    {
        if (this == &other) // Проверка на самоприсваивание
            return *this;

        // Копируем данные из other в текущий объект
        explosion = other.explosion;
        velocityX = other.velocityX;
        velocityY = other.velocityY;
        speed = other.speed;
        radius = other.radius;
        size = other.size;
        positionX = other.positionX;
        positionY = other.positionY;
        timeRender = other.timeRender;
        sprite = other.sprite;
        texture = other.texture;
        rotation = other.rotation;
        particlesF = other.particlesF;
        timeLeft = other.timeLeft;
        timeF = other.timeF;

       
        return *this;
    }
};