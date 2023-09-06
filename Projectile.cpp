#include "Projectile.h"
#include <cmath>
#include <iostream>

Projectile::Projectile(std::vector<std::vector<int>>& mapS, std::vector<Player>& playersS, float initialVelocityX, float initialVelocityY, float initialSpeed, float startPositionX, float startPositionY)
    : map(mapS), players(playersS), velocityX(initialVelocityX), velocityY(initialVelocityY), speed(initialSpeed), PositionX(startPositionX), PositionY(startPositionY), radius(3), size(2), explosion(false) {

    std::cout << "Create projectile" << std::endl;
}

void Projectile::update() {
    if (!explosion) {
        applyVelocity();
    }
}

void Projectile::applyVelocity() {
    // ѕримен€ем гравитацию
    float gravity = 0.5f;
    velocityY += gravity;

    // ќбновл€ем позицию снар€да
    float newX = PositionX + velocityX * speed;
    float newY = PositionY + velocityY * speed;
    speed -= 0.1f;

    // ѕровер€ем, что нова€ позици€ находитс€ в пределах карты и на песке или земле
    if (isValidPosition(newX, newY)) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                map[static_cast<int>(newY) ][static_cast<int>(newX) ] = 0;
                map[static_cast<int>(newY) + i][static_cast<int>(newX) + j] = 9; // –азмещаем снар€д в новой позиции
            }
        }
        PositionX = newX;
        PositionY = newY;
    }
    else {
        // ≈сли нова€ позици€ недопустима, значит снар€д столкнулс€ с землей
        createExplosion();
    }
}

void Projectile::createExplosion() {
    // —оздаем дыру в земле (заполн€ем радиус вокруг снар€да нул€ми)
    for (int i = -radius; i <= radius; i++) {
        for (int j = -radius; j <= radius; j++) {
            int explosionX = static_cast<int>(PositionX) + i;
            int explosionY = static_cast<int>(PositionY) + j;

            if (explosionX >= 0 && explosionX < map[0].size() && explosionY >= 0 && explosionY < map.size()) {
                map[explosionY][explosionX] = 0;
            }
        }
    }

    // ѕровер€ем столкновение с игроками и наносим урон
    for (int i = 0; i < players.size(); ++i) {
        float playerX = players[i].getX();
        float playerY = players[i].getY();
        float distance = sqrt(pow(PositionX - playerX, 2) + pow(PositionY - playerY, 2));

        if (distance <= radius && players[i].getId() >= 3 && players[i].getId() <= 8) {
            // ќбработка столкновени€ с игроком
            players[i].hit(distance);
        }
    }

    explosion = true;
}

bool Projectile::getStatus() {
    return explosion;
}

bool Projectile::isValidPosition(float x, float y) {
    // ѕровер€ем, что нова€ позици€ находитс€ в пределах карты и на песке или земле
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (x + i < 0 || x + i >= map[0].size() || y + j < 0 || y + j >= map.size()) {
                explosion = true;
                return false;
            }
            if (map[static_cast<int>(y) + i][static_cast<int>(x) + j] != 0) {
                return false;
            }
        }
    }
    return true;
}