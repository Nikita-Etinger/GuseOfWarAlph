#pragma once
#include "Config.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>



class Projectile
{
private:
    float& timeF;
    bool explosion=0;
    float velocityX;
    float velocityY;
    float speed;
    float radius=5;
    int size=3;
    float positionX = 0;

    float positionY=0;
    


public:
    Projectile(float positionX, float positionY, float velocityXS, float velocityYS, float speed,float& time);
    void applyVelocity();
    void update();
    bool getStatus();
    vt getCoordinate();
    float getRadius();
    int getSize();
    void explosions();
    void draw(sf::RenderWindow& window);
    
};