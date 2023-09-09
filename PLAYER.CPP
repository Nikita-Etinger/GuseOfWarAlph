#include "Player.h"
#include "iostream"
#include "Config.h"
#include <cmath>
#include <ctime>
#include <algorithm>
#define cout std::cout<<

const float gravity = 0.1f;

Player::Player(std::vector<std::vector<int>>& mapS, sf::RenderWindow& windowS, bool com, int newPlayerId, std::string newName)
    : command(com), map(mapS), window(windowS), playerId(newPlayerId), playerName(newName) {

    accelerationY = 0.0f;
    accelerationX = 0.0f;
    placePlayersOnMap();
}



//законченные методы __________________________________________________________________________________________________________________________________________________________________________________________________________________________________________
void Player::placePlayersOnMap() {
    playerSize = 2;
    
    int playerY = 0;
   
    // Начинаем с верхней строки и идем вниз, пока не найдем пустую ячейку

    int playerX = rand() % (map.size() - playerSize);
    for (; playerY < map.size()-playerSize-1; playerY++) {
        if (map[playerX][playerY+playerSize] != 0)break;

    }
    playerY = 10;




    // Помещаем игрока на карту
    for (int i = playerSize; i >0; i--) {
        for (int j = playerSize; j > 0; j--) {
            map[playerY + i][playerX + j] = playerId; // Размещаем игрока
        }
    }
    
    // Устанавливаем начальные координаты игрока
    posX = playerX;
    posY = playerY;

}
void Player::applyVelocity() {
    bool onGround = false;
    // Проверяем, касается ли игрок земли
    onGround = isOnGround();
    //std::cout << isOnGround();
    // Сохраняем начальное положение игрока
    int initialPosX = posX;
    int initialPosY = posY;

    // Очистка старой позиции
    for (int i = 0; i <= playerSize; i++) {
        for (int j = playerSize; j >= 0; j--) {
            if (posY + i >= 0 && posY + i < map.size() && posX + j >= 0 && posX + j < map[0].size()) {
                map[posY + i][posX + j] = 0; // Помечаем старую позицию как пустую
            }
        }
    }

    // Если игрок на земле, сбросить ускорение по Y
    if (onGround) {
        velocityY = 0.0f;
        accelerationY = 0.0f;
    }
    else {
        // Иначе, увеличить ускорение по Y (например, на гравитацию)
        accelerationY += gravity; // gravity - константа гравитации
        velocityY += accelerationY;
    }

    // Переместить игрока на новую позицию, учитывая его скорость (velocityX и velocityY)
    if (posX + velocityX >= 0 && posX + velocityX + 2 < map[0].size()) {
        posX += velocityX;
    }

    if (posY + velocityY >= 0 && posY + velocityY + 2 < map.size()) {
        posY += velocityY;
    }

    bool flagValid = 1;

    // Первая попытка разместить игрока
    for (int i = 0; i <= playerSize; i++) {
        for (int j = playerSize; j >= 0; j--) {
            if (posY + i >= 0 && posY + i < map.size() && posX + j >= 0 && posX + j < map[0].size()) {
                if (map[posY + i][posX + j] > 0) {
                    posY--;

                    flagValid = 0;
                    break;
                }
            }
            if (!flagValid) break;
        }
    }

    if (flagValid == 0) {
        // Вторая попытка разместить игрока
        flagValid = 1;
        for (int i = 0; i <= playerSize; i++) {
            for (int j = playerSize; j >= 0; j--) {
                if (posY + i >= 0 && posY + i < map.size() && posX + j >= 0 && posX + j < map[0].size()) {
                    if (map[posY + i][posX + j] > 0) {
                        flagValid = 0;
                        break;
                    }
                }
                if (!flagValid)break;
            }
        }
    }

    if (flagValid) {
        // Успешно размещаем игрока
        for (int i = 0; i <= playerSize; i++) {
            for (int j = playerSize; j >= 0; j--) {
                if (posY + i >= 0 && posY + i < map.size() && posX + j >= 0 && posX + j < map[0].size()) {
                    map[posY + i][posX + j] = playerId;
                }
            }
        }
    }
    else {
        // Если не удалось разместить игрока после второй попытки, вернуть его на начальное положение
        posX = initialPosX;
        posY = initialPosY;
        for (int i = 0; i <= playerSize; i++) {
            for (int j = playerSize; j >= 0; j--) {
                if (posY + i >= 0 && posY + i < map.size() && posX + j >= 0 && posX + j < map[0].size()) {
                    map[posY + i][posX + j] = playerId;
                }
            }
        }
    }
    cout posX << " " << posY << '\n';
    

    velocityX = 0;
    velocityY = 0;
}
bool Player::isOnGround() {

    for (int j = 0; j <= playerSize; j++) {
        int centerX = posX + j;  
        int topY = posY + 3; 

        if (topY >= 0 && centerX >= 0 && centerX < map[0].size()-1) {

            if (map[topY][centerX] >0) {
                return true;
            }
        }
    }

    return false;
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
void Player::resetStage() {
    stage = 1;
    turnOff = 0;
}

//методы в процессе доработки __________________________________________________________________________________________________________________________________________________________________________________________________________________________________________
// 
// 
// 
// 
void Player::update()
{
    cout "correctAimX: " << correctAimX<<'\n';
    cout "Stage " << stage << '\n';
    if (stage == 1) {
        draw();
    }
    //std::cout << "cplayerX: " << posX << " cplayerY: " << posY << std::endl;
    applyVelocity();
}


//direction 0-игрок направлен влево,1-вправо
void Player::handlerEvent(sf::Event& event) {
    if (event.key.code == sf::Keyboard::Enter) {
        stage++;
        if (stage == 4) {
            turnOff = 1;
            return;
        }
    }

    if (stage == 0) {
        if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D) {
            velocityX = (event.key.code == sf::Keyboard::A) ? -0.5f : 0.5f;
            /* std::cout << ((event.key.code == sf::Keyboard::A) ? "A" : "D") << '\n';*/
            direction = (event.key.code == sf::Keyboard::A) ? 0 : 1;
        }
    }
    else if (stage == 1) {
        if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D) {
            if (event.key.code == sf::Keyboard::A) {
                directionShot += 20;
                //std::cout << "DirectionShot: " << directionShot << '\n';
                if (directionShot > 360) {
                    directionShot = 0;
                }
                //correctAimX++;
            }
            else {
                //std::cout << "DirectionShot: " << directionShot << '\n';
                directionShot -= 20;
                //correctAimX--;
                if (directionShot < 0) {
                    directionShot = 360;
                }
            }
        }
    }
    else if (stage == 2) {
        if (event.key.code == sf::Keyboard::A) {
            powerShot--;
            if (powerShot < 5)powerShot = 5;
        }
        else if (event.key.code == sf::Keyboard::D) {
            powerShot++;
            if (powerShot > 100)powerShot = 100;
        }
    }
}
    void Player::draw() {
        // Размер блока в вашем мире


        // Радиус прицела
        float aimRadius = 3.0f; // Замените это значение на желаемый размер прицела

        // Вычисляем положение прицела относительно центра игрока, учитывая размер блока
        float aimX = posX * BLOCK_SIZE + 30.0f * std::cos(directionShot * 3.14159265f / 180.0f); // Расстояние 10f в направлении directionShot
        float aimY = posY * BLOCK_SIZE + 30.0f * std::sin(directionShot * 3.14159265f / 180.0f);

        // Создаем окружность (прицел) с красной обводкой
        sf::CircleShape aimCircle(aimRadius);
        aimCircle.setFillColor(sf::Color::Transparent); // Задаем цвет заполнения (прозрачный)
        aimCircle.setOutlineColor(sf::Color::White); // Задаем цвет обводки (красный)
        aimCircle.setOutlineThickness(2.0f); // Толщина обводки

        // Устанавливаем положение прицела
        aimCircle.setPosition(aimX - aimRadius+3*BLOCK_SIZE/2, aimY - aimRadius+ 3 * BLOCK_SIZE / 2);


        // Отрисовываем прицел на окне
        window.draw(aimCircle);
    }