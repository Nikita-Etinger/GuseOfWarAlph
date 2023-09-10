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
    float radius;
    int size;
    float PositionX, PositionY;
    void applyVelocity();
    std::vector<std::vector<int>>& map;

public:
    Projectile(std::vector<std::vector<int>>& mapS);
    
    void update();
    bool getStatus();
    bool isValidPosition(float x, float y);
    void createExplosion();
    
};