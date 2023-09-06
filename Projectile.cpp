#include "Projectile.h"
#include <cmath>
#include <iostream>
Projectile::Projectile(std::vector<std::vector<int>>& mapS, std::vector<Player>& playersS, float initialVelocityX, float initialVelocityY, float initialSpeed, float startPositionX, float startPositionY)
    : map(mapS), players(playersS), velocityX(initialVelocityX), velocityY(initialVelocityY), speed(initialSpeed), PositionX(startPositionX), PositionY(startPositionY), radius(3), size(2), explosion(false) {
    // ����� ����� �������� ��� ������������� ������� ��� ��������, ���� ����������.
}

void Projectile::update() {
    applyVelocity();
}

void Projectile::applyVelocity() {

    // ��������� ����������
    float gravity = 0.5f;
    velocityY += gravity;

    // ��������� ������� �������
    float newX = velocityX * speed;
    float newY = velocityY * speed;
    speed -= 0.1f;

    if (isValidPosition(newX, newY)) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                map[PositionX + i][PositionY + j] = 0; // ������� ������ �� ������� �������
                map[newX + i][newY + j] = 9; // ��������� ������ � ����� �������
            }
        }
        PositionX = newX;
        PositionY = newY;
    }
    
    
    if (!explosion) {
        // ��������� ������������ � ������
        if (velocityX >= 0 && velocityX < map[0].size() && velocityY >= 0 && velocityY < map.size()) {
            if (map[velocityY][velocityX] == 1) {
                // ������ ���������� � ������, �������� ���� ������ (
                for (int i = 0; i < players.size(); ++i) {
                    int playerX = static_cast<int>(players[i].getX());
                    int playerY = static_cast<int>(players[i].getY());
                    float distance = sqrt(pow(PositionX - playerX, 2) + pow(PositionY - playerY, 2));

                    if (distance <= radius && players[i].getId() >= 3 && players[i].getId() <= 8) {
                        // ��������� ������������ � �������
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
    // ���������, ��� ����� ������� ��������� � �������� ����� � �� ����� ��� �����
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