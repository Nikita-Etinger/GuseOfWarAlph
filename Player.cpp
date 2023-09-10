#include "Player.h"

//map.size() ���������� �� Y map[0].size() ���������� �� X !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define cout std::cout<<

const float gravity = 0.5f;
Player::Player(std::vector<std::vector<int>>& mapS, sf::RenderWindow& windowS, bool com, int newPlayerId, std::string newName, std::vector<Projectile>& projectileS)
    : command(com), map(mapS), window(windowS), playerId(newPlayerId), playerName(newName), projectile(projectileS) {


        playerSize = 3;
        posX = 10;
        //posX = rand() % (map.size() - playerSize);;
        posY = 10;
        PlacePositionOnMap();
    if (!playerTexture.loadFromFile("guse.png")) {
        cout "error load guse.png" << '\n';
    }
    else {
        cout "Load guse.png complite" << '\n';
    }

}


Player::~Player() {
    cout "Player delited"<<'\n';
}
//����������� ������ __________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void Player::PlacePositionOnMap() {
    // �������� ������ �� �����
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (posX + i < map[0].size() && posX + i>2 && posY + j < map.size() && posY + j>2) {
                map[posY + i][posX + j]  =playerId;
            }
        }
    }

}
bool Player::ScanPosition() {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (posX + i < map[0].size() && posX + i>2 && posY + j < map.size() && posY + j>2) {
                if (map[posY + i][posX + j] > 0) return false;
            }
            else return false;
        }
    }
    return true;

}
void Player::applyVelocity() {
    bool onGround = false;
    // ���������, �������� �� ����� �����
    onGround = isOnGround();
    // ��������� ��������� ��������� ������
    cout "PlayerX: " << posX << " PlayerY: " << posY << '\n';
    int initialPosX = posX;
    int initialPosY = posY;
    // ������� ����
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (posX + i < map[0].size() && posX + i>2 && posY + j < map.size() && posY + j>2) {
                map[posY + i][posX + j] = 0;
            }
        }
    }


    // ���� ����� �� �����, �������� ��������� �� Y
    if (onGround) {
        velocityY = 0.0f;
    }
    else {
        
        velocityY += gravity;
    }

    // ����������� ������ �� ����� �������, �������� ��� �������� (velocityX � velocityY)
    posX += velocityX;
    posY += velocityY;


    // ��������� ����� ������� ������
    bool flagValid = ScanPosition();
    if (!flagValid) {
        posY--;//��������� posY � ����� ���������
        flagValid = ScanPosition();
    }

    if (flagValid) {
        // ������� ��������� ������
        PlacePositionOnMap();
    }
    else {
        // ���� �� ������� ���������� ������, ������� ��� �� ��������� ���������
        posX = initialPosX;
        posY = initialPosY;
        // ���������� ������ �� ��������� �������
        PlacePositionOnMap();
    }

    velocityX = 0;
    velocityY = 0;
}

bool Player::isOnGround() {
    if (posY + 2 >= map.size()) { //����� ������ ����� ����� �� Y
        cout "XXXXXXXXXXXX" << '\n';
        return true;
    }

    // ���������, ���� �� ����� ��� ������� � �������� ��� �������������� ������
    for (int i = -1; i <= 1; i++) {
        if (map[posY + 2][posX + i] > 0) return true;
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
void Player::resetStage() {
    stage = 1;
    turnOff = 0;
}
void Player::drawAim() {

    // ������ �������
    float aimRadius = 3.0f; // �������� ��� �������� �� �������� ������ �������

    // ��������� ��������� ������� ������������ ������ ������, �������� ������ �����
    float aimX = posX * BLOCK_SIZE + 60.0f * std::cos(directionShot * 3.14159265f / 180.0f); // ���������� 10f � ����������� directionShot
    float aimY = posY * BLOCK_SIZE + 60.0f * std::sin(directionShot * 3.14159265f / 180.0f);

    // ������� ���������� (������) � ������� ��������
    sf::CircleShape aimCircle(aimRadius);
    aimCircle.setFillColor(sf::Color::Transparent); // ������ ���� ���������� (����������)
    aimCircle.setOutlineColor(sf::Color::White); // ������ ���� ������� (�������)
    aimCircle.setOutlineThickness(2.0f); // ������� �������

    // ������������� ��������� �������
    aimCircle.setPosition(aimX - aimRadius + 3 * BLOCK_SIZE / 2, aimY - aimRadius + 3 * BLOCK_SIZE / 2);


    // ������������ ������ �� ����
    window.draw(aimCircle);
}
void Player::drawHpName() {
    sf::Font font;
    if (!font.loadFromFile("font.ttf")) {

    }

    // ������� ��������� ����������� ��� ����� � �������� ������
    sf::Text playerNameHpText;
    playerNameHpText.setFont(font);
    playerNameHpText.setCharacterSize(10); // ������ ������
    playerNameHpText.setFillColor(command ? sf::Color::Red : sf::Color::Blue); // ������������� ���� ����� � ����������� �� �������

    // ����������� �������� � ����� ������ ����� �������
    std::stringstream hpStream;
    hpStream << std::fixed << std::setprecision(1) << hp;
    std::string hpString = hpStream.str();


    std::string hpNameString = playerName + "\n" + "HP " + hpString;
    playerNameHpText.setString(hpNameString);

    // ��������� ������ ����� �������� �� ������� ������ � ������� ������
    playerNameHpText.setPosition(posX * BLOCK_SIZE, (posY - 1) * BLOCK_SIZE - playerNameHpText.getLocalBounds().height - BLOCK_SIZE * 2);

    // ������������ ��������� ����������� �� ����
    window.draw(playerNameHpText);
}
void Player::drawPlayer() {
    playerSprite.setTexture(playerTexture);

    // ��������� ����� �������� ������� � ��� ��������
    playerSprite.setOrigin(playerSprite.getLocalBounds().width / 2, playerSprite.getLocalBounds().height / 2);

    playerSprite.setScale(1, 1); // ������������� ������� �� ����� ����
    playerSprite.setPosition(vt(posX * BLOCK_SIZE, posY * BLOCK_SIZE));

    if (!direction) {
        // �������� ������ �� ����������� (�����)
        playerSprite.setScale(-1, 1);
    }
    // ����� ������ ��������� � �������� ��������� (������)

    window.draw(playerSprite);
}



//������ � �������� ��������� __________________________________________________________________________________________________________________________________________________________________________________________________________________________________________
// 
// 
// 
// 
void Player::update()
{

    if (stage == 1) {
        drawAim();
    }
    drawHpName();
    drawPlayer();
    //drawCenter();
    applyVelocity();
}
void Player::drawPower() {

}
void Player::drawCenter() {
    // ������ �������
    float aimRadius = 3.0f; // �������� ��� �������� �� �������� ������ �������

    //// ��������� ��������� ������� ������������ ������ ������, �������� ������ �����
    //float aimX = posX * BLOCK_SIZE + 60.0f * std::cos(directionShot * 3.14159265f / 180.0f); // ���������� 10f � ����������� directionShot
    //float aimY = posY * BLOCK_SIZE + 60.0f * std::sin(directionShot * 3.14159265f / 180.0f);

    // ������� ���������� (������) � ������� ��������
    sf::CircleShape aimCircle(aimRadius);
    aimCircle.setFillColor(sf::Color::Red); // ������ ���� ���������� (����������)
    aimCircle.setOutlineColor(sf::Color::White); // ������ ���� ������� (�������)
    aimCircle.setOutlineThickness(2.0f); // ������� �������

    // ������������� ��������� �������
    aimCircle.setPosition(posX * BLOCK_SIZE, posY* BLOCK_SIZE);


    // ������������ ������ �� ����
    window.draw(aimCircle);


}

//direction 0-����� ��������� �����,1-������
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
            velocityX = (event.key.code == sf::Keyboard::A) ? -1.0f : 1.0f;
            cout  ((event.key.code == sf::Keyboard::A) ? "A" : "D") << '\n';
            direction = (event.key.code == sf::Keyboard::A) ? 0 : 1;
        }
    }
    else if (stage == 1) {
        if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D) {
            if (event.key.code == sf::Keyboard::A) {
                directionShot -= 10;
                if (directionShot < 0) {
                    directionShot = 360;
                }
            }
            else {

                directionShot += 10;
                if (directionShot > 360) {
                    directionShot = 0;
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

void Player::hit(float hitCount) {
    //��������� �����
}
