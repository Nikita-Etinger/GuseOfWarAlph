#include "Projectile.h"
#include <cmath>
#include <iostream>
Projectile::Projectile(std::vector<std::vector<int>>& mapS, std::vector<Player>& playersS, float initialVelocityX, float initialVelocityY, float initialSpeed, float startPositionX, float startPositionY)
    : map(mapS), players(playersS), velocityX(initialVelocityX), velocityY(initialVelocityY), speed(initialSpeed), PositionX(startPositionX), PositionY(startPositionY), radius(3), size(2), explosion(false) {
    // Здесь можно добавить код инициализации снаряда при создании, если необходимо.
}

void Projectile::update() {
    applyVelocity();
}

void Projectile::applyVelocity() {

    // Применяем гравитацию
    float gravity = 0.5f;
    velocityY += gravity;

    // Обновляем позицию снаряда
    float newX = velocityX * speed;
    float newY = velocityY * speed;
    speed -= 0.1f;

    if (isValidPosition(newX, newY)) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                map[PositionX + i][PositionY + j] = 0; // Убираем снаряд из текущей позиции
                map[newX + i][newY + j] = 9; // Размещаем снаряд в новой позиции
            }
        }
        PositionX = newX;
        PositionY = newY;
    }
    
    
    if (!explosion) {
        // Проверяем столкновение с землей
        if (velocityX >= 0 && velocityX < map[0].size() && velocityY >= 0 && velocityY < map.size()) {
            if (map[velocityY][velocityX] == 1) {
                // Снаряд столкнулся с землей, вызываем урон игроку (
                for (int i = 0; i < players.size(); ++i) {
                    int playerX = static_cast<int>(players[i].getX());
                    int playerY = static_cast<int>(players[i].getY());
                    float distance = sqrt(pow(PositionX - playerX, 2) + pow(PositionY - playerY, 2));

                    if (distance <= radius && players[i].getId() >= 3 && players[i].getId() <= 8) {
                        // Обработка столкновения с игроком
                        players[i].hit(distance);
                    }
                }
                explosion = true;
            }
        }
    }
}

bool Projectile::getStatus() {
    return explosion;
}
bool Projectile::isValidPosition(int x, int y) {
    // Проверяем, что новая позиция находится в пределах карты и на песке или земле
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (x + i < 0 || x + i >= map.size() || y + j < 0 || y + j >= map[0].size()) {
                explosion = true;
                return false;
            }
            if (map[x + i][y + j] != 1 && map[x + i][y + j] != 2) {
                return false;
            }
        }
    }
    return true;
}