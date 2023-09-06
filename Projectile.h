#pragma once
#include <vector>
#include "Player.h"
class Projectile
{
private:
    std::vector<Player>& players;
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
    Projectile(std::vector<std::vector<int>>& mapS, std::vector<Player>& playersS, float velocityX, float velocityY, float speed, float startPositionX, float startPositionY);
    
    void update();
    bool getStatus();
    bool isValidPosition(int x, int y);
};