#include "Player.h"
#include "iostream"
#include "Config.h"




Player::Player(std::vector<std::vector<int>>& mapS, sf::RenderWindow& windowS, bool com, int newPlayerId, std::string newName)
    : command(com), map(mapS), window(windowS), playerId(newPlayerId), playerName(newName) {


    placePlayersOnMap();
}

void Player::update()
{
    applyVelocity();
}


void Player::placePlayersOnMap() {
    int playerSize = 4;
    srand(time(NULL));
    int playerX = rand() % (map.size() - playerSize);
    int playerY = 0; // �������� � ������� ������

    // ���� ������� ������� �����
    while (playerY < map[0].size() - playerSize && map[playerX][playerY] == 0) {
        playerY++;
    }

    // �������� ������ �� �����
    for (int i = 0; i < playerSize; i++) {
        for (int j = 0; j < playerSize; j++) {
            map[playerX + i][playerY + j] = playerId; // ��������� ������
        }
    }

    // ������������� ��������� ���������� ������
    posX = playerX;
    posY = playerY;
}
void Player::applyVelocity() {
    // ��������� ��������� � ������� ������
    int newX = posX + velocityX;
    int newY = posY +velocityY;

    if (isValidPosition(newX, newY)) {
        // ���� ����� ������� ���������, ���������� ������
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                map[posX + i][posY + j] = 0; // ������� ������ �� ������� �������
                map[newX + i][newY + j] = playerId; // ��������� ������ � ����� �������
            }
        }
        posX = newX;
        posY = newY;
    }
    // �������� ��������� ����� �����������
    velocityX = 0.0f;
    velocityY = 0.0f;
}

bool Player::isValidPosition(int x, int y) {
    // ���������, ��� ����� ������� ��������� � �������� ����� � �� ����� ��� �����
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (x + i < 0 || x + i >= map.size() || y + j < 0 || y + j >= map[0].size()) {
                return false;
            }
            if (map[x + i][y + j] != 1 && map[x + i][y + j] != 2) {
                return false;
            }
        }
    }
    return true;
}

void Player::handlerEvent(sf::Event event) {
    while (window.pollEvent(event)) { 
        std::cout << "event Cath" << '\n';
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::A) {
                velocityX -= 0.1f; 
            }
            else if (event.key.code == sf::Keyboard::D) {
                velocityX += 0.1f; 
            }
        }
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
    //��������� �����
}