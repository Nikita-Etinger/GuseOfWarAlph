#pragma once
#include "Config.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>



class Projectile
{
private:
    bool explosion=0;
    float velocityX;
    float velocityY;
    float speed;
    float radius=5;
    int size=2;
    float positionX = 0;
    float positionY=0;
    


public:
    Projectile(float positionX, float positionY, float velocityXS, float velocityYS, float speed);
    void applyVelocity();
    void update();
    bool getStatus();
    vt getCoordinate();
    float getRadius();
    int getSize();
    void explosions();
    
};