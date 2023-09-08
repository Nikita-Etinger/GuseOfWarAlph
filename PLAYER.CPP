#include "Player.h"
#include "iostream"
#include "Config.h"
#include <cmath>


const float gravity = 0.01f;

Player::Player(std::vector<std::vector<int>>& mapS, sf::RenderWindow& windowS, bool com, int newPlayerId, std::string newName)
    : command(com), map(mapS), window(windowS), playerId(newPlayerId), playerName(newName) {

    accelerationY = 0.0f;
    accelerationX = 0.0f;
    placePlayersOnMap();
}

void Player::update()
{
    applyVelocity();
}


void Player::placePlayersOnMap() {
    int playerSize = 2;
    srand(time(NULL));
    int playerY = 0;
   
    // Ќачинаем с верхней строки и идем вниз, пока не найдем пустую €чейку
    int playerX = rand() % (map.size() - playerSize);
    for (; playerY < map.size()-playerSize-1; playerY++) {
        if (map[playerX][playerY+playerSize] != 0)break;

    }
    playerY = 10;
    //for (int x = 0; x < map.size() - 1; x++) {
    //    for (int y = 0; y < map[x].size() - 1; y++) {
    //        std::cout << map[x][y];
    //    }
    //    std::cout << std::endl;
    //}



    // ѕомещаем игрока на карту
    playerY -= playerSize;
    for (int i = 0; i < playerSize; i++) {
        for (int j = playerSize; j > 0; j--) {
            map[playerY + i][playerX + j] = playerId; // –азмещаем игрока
        }
    }
    std::cout << "playerX: " << playerX << " playerY: " << playerY << std::endl;
    // ”станавливаем начальные координаты игрока
    posX = playerX;
    posY = playerY;

}
void Player::applyVelocity() {
    // ѕровер€ем, касаетс€ ли игрок земли
    bool onGround = isOnGround();
    //std::cout << isOnGround();
    // —охран€ем начальное положение игрока
    int initialPosX = posX;
    int initialPosY = posY;

    // ќчистка старой позиции
    for (int i = 2; i >= 0; i--) {
        for (int j = 2; j >= 0; j--) {
            if (posY + i >= 0 && posY + i < map.size() && posX + j >= 0 && posX + j < map[0].size()) {
                map[posY + i][posX + j] = 0; // ѕомечаем старую позицию как пустую
            }
        }
    }

    // ≈сли игрок на земле, сбросить ускорение по Y
    if (onGround) {
        velocityY = 0.0f;
        accelerationY = 0.0f;
    }
    else {
        // »наче, увеличить ускорение по Y (например, на гравитацию)
        accelerationY += gravity; // gravity - константа гравитации
        velocityY += accelerationY;
    }

    // ѕереместить игрока на новую позицию, учитыва€ его скорость (velocityX и velocityY)
    if (posX + velocityX >= 0 && posX + velocityX + 2 < map[0].size()) {
        posX += velocityX;
    }

    if (posY + velocityY >= 0 && posY + velocityY + 2 < map.size()) {
        posY += velocityY;
    }

    bool flagValid = 1;

    // ѕерва€ попытка разместить игрока
    for (int i = 2; i >= 0; i--) {
        for (int j = 2; j >= 0; j--) {
            if (posY + i >= 0 && posY + i < map.size() && posX + j >= 0 && posX + j < map[0].size()) {
                if (map[posY + i][posX + j] > 0) {
                    posY--;
                    flagValid = 0;
                }
            }
        }
    }

    if (flagValid == 0) {
        // ¬тора€ попытка разместить игрока
        flagValid = 1;
        for (int i = 2; i >= 0; i--) {
            for (int j = 2; j >= 0; j--) {
                if (posY + i >= 0 && posY + i < map.size() && posX + j >= 0 && posX + j < map[0].size()) {
                    if (map[posY + i][posX + j] > 0) {
                        flagValid = 0;
                    }
                }
            }
        }
    }

    if (flagValid) {
        // ”спешно размещаем игрока
        for (int i = 2; i >= 0; i--) {
            for (int j = 2; j >= 0; j--) {
                if (posY + i >= 0 && posY + i < map.size() && posX + j >= 0 && posX + j < map[0].size()) {
                    map[posY + i][posX + j] = playerId;
                }
            }
        }
    }
    else {
        // ≈сли не удалось разместить игрока после второй попытки, вернуть его на начальное положение
        posX = initialPosX;
        posY = initialPosY;
        for (int i = 2; i >= 0; i--) {
            for (int j = 2; j >= 0; j--) {
                if (posY + i >= 0 && posY + i < map.size() && posX + j >= 0 && posX + j < map[0].size()) {
                    map[posY + i][posX + j] = playerId;
                }
            }
        }
    }

    velocityX = 0;
    velocityY = 0;
}

bool Player::isOnGround() {
    // ѕровер€ем, есть ли земл€ над верхними блоками игрока (x, y и x+1, y)
    for (int j = 0; j < 2; j++) {
        int centerX = posX + j;  // Ѕлок по X
        int topY = posY + 3;  // Ѕлок выше игрока

        if (topY >= 0 && centerX >= 0 && centerX < map[0].size()) {
            // ѕровер€ем, есть ли земл€ над текущим блоком
            if (map[topY][centerX] == 1 || map[topY][centerX] == 2) {
                return true;
            }
        }
    }

    return false;
}


void Player::handlerEvent(sf::Event& event) {
    if (event.key.code == sf::Keyboard::A) {
        velocityX -=0.5f;
        std::cout << "A" << '\n';
        direction = 0;
    }
    else if (event.key.code == sf::Keyboard::D) {
        velocityX += 0.5f;
        std::cout << "D" << '\n';
        direction = 1;
    }

}


int Player::getId() {
    return playerId;
}
float Player::getX() {
    return posX;
}
float Player::getY() {
    return posY;
}
void Player::hit(float radius) {
    //получение урона
}
