#include "Player.h"

//map.size() ���������� �� Y map[0].size() ���������� �� X !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define cout std::cout<<

const float gravity = 1.5f;
const float speed = 1.5f;
Player::Player(std::vector<std::vector<int>>& mapS, sf::RenderWindow& windowS, bool com, int newPlayerId, std::string newName, std::vector<Projectile>& projectileS,float& time, std::vector<Particles>& particles, std::vector<Projectile> projectileBufer)
    : command(com), map(mapS), window(windowS), playerId(newPlayerId), playerName(newName), projectile(projectileS),projectileBufer(projectileBufer), timeF(time), particlesF(particles) {


        playerSize = 5;
        coorectCollision = playerSize/2;
        posY = rand() % (map.size() - playerSize);
        posX = rand() % (map[0].size() - playerSize);
        while (!ScanPosition()) {
            posY = rand() % (map.size() - playerSize);
            posX = rand() % (map[0].size() - playerSize);

        }
        while (ScanPosition()) {
            posY++;
        }
        posY--;
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
     //�������� ������ �� �����
    //for (int i = -coorectCollision; i <= coorectCollision; i++) {
    //    for (int j = -coorectCollision; j <= coorectCollision; j++) {
    //        if (posX + i < map[0].size() && posX + i>coorectCollision && posY + j < map.size() && posY + j>coorectCollision) {
    //            map[posY + i][posX + j]  =playerId;
    //        }
    //    }
    //}

}
bool Player::ScanPosition() {
    for (int i = -coorectCollision; i <= coorectCollision; i++) {
        for (int j = -coorectCollision; j <= coorectCollision; j++) {
            if (posX + i < map[0].size()-1 && posX + i>1 && posY + j < map.size()-1 && posY + j>1) {
                if (map[posY + i][posX + j] > 0) return false;
            }
            else return false;
        }
    }
    return true;

}
bool Player::scanContactProjectile(float radius, sf::Vector2f coordinatePr)
{
    float distance = std::sqrt(std::pow(coordinatePr.x - posX, 2) + std::pow(coordinatePr.y - posY, 2));

    if (distance <= radius + coorectCollision)
    {
        // ������ ������� �� ������, ����������� ������ 
        float accelerationFactor = distance / 10;
        accelerationX += (posX < coordinatePr.x) ? -accelerationFactor : accelerationFactor;
        accelerationY -= accelerationFactor;
        hit(radius);
        return true;
    }
    else return false;
}
void Player::applyVelocity() {
    bool onGround = false;
    // ���������, �������� �� ����� �����
    onGround = isOnGround();
    // ��������� ��������� ��������� ������
    int initialPosX = posX;
    int initialPosY = posY;

    if (onGround) {
        velocityY = 0.0f;
    }
    else {
        velocityY += gravity;
    }

    // ����������� ������ �� ����� �������, �������� ��� �������� (velocityX � velocityY)
    posX += velocityX + accelerationX * timeF;
    posY += velocityY + accelerationY * timeF;




    // ��������� ����� ������� ������
    bool flagValid = ScanPosition();
    if (!flagValid) {
        posY--;//��������� posY � ����� ��������� (������ �������� �� �� ��� ������� ���� � ������)
        flagValid = ScanPosition();
    }
    if (!flagValid) {
        posY--;//��������� posY � ����� ��������� (������ �������� �� �� ��� ������� 2����� � ������)
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
      
        velocityX = 0;
        velocityY = 0;
    }
    if (accelerationX > 0)accelerationX -= accelerationY / 3 * timeF;
    else if (accelerationX < 0)accelerationX+= accelerationY / 3 * timeF;
    else accelerationX = 0;
    if (accelerationY > 0)accelerationY-= accelerationY / 3 * timeF;
    else if (accelerationY < 0)accelerationY += accelerationY/3 * timeF;
    else accelerationY = 0;
    velocityX = 0;
    velocityY = 0;
}

bool Player::isOnGround() {
    if (posY + 2 >= map.size()) { //����� ������ ����� ����� �� Y
        //cout "XXXXXXXXXXXX" << '\n';
        if (distanceFall > 2) {
            hit(distanceFall);
        }
        distanceFall = 0;
        return true;
    }

    // ���������, ���� �� ����� ��� ������� � �������� ��� �������������� ������
    for (int i = -coorectCollision; i <= coorectCollision; i++) {
        if (map[posY + coorectCollision + 1][posX + i] > 0) {
            if (distanceFall >2) {
                hit(distanceFall);
            }
            distanceFall = 0;
            return true;
        }
    }
    distanceFall++;
    
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
    if (changePowerDirectionMove) {
        aimVector.clear();
        float angleRad = directionShot * 3.14159265f / 180.0f;
        float positionXPr = posX;
        float positionYPr = posY - playerSize;
        float projectileGravity = powerShot * 10.0f;

        float velocityXPr = projectileGravity * std::cos(angleRad);
        float velocityYPr = projectileGravity * std::sin(angleRad);
        float prRealSpeed = 0.03;

        float minPowerShot = 10.0f;
        float maxPowerShot = 1000.0f;
        float minGravity = 0.001f;
        float maxGravity = 0.00001f;

        // ��������� ����������
        float gravityPr = minGravity + (maxGravity - minGravity) * ((projectileGravity - minPowerShot) / (maxPowerShot - minPowerShot));
        cout "Player gravity"<<gravityPr << '\n';
        //��� ������� 
        for (int i = 0; i < 30; i++) {
            float length = std::sqrt(velocityXPr * velocityXPr + velocityYPr * velocityYPr);
            if (length != 0) {
                velocityXPr /= length;
                velocityYPr /= length;
            }
            positionXPr += velocityXPr * prRealSpeed * timeF;
            positionYPr += velocityYPr * prRealSpeed * timeF;
            velocityYPr += gravityPr * timeF; 
            aimVector.push_back(sf::Vector2f(positionXPr * BLOCK_SIZE, positionYPr * BLOCK_SIZE));
        }
        changePowerDirectionMove = false;
    }

    for (auto& aimVect : aimVector) {
        sf::CircleShape aimCircle(10);
        aimCircle.setFillColor(sf::Color::Color(255,255,255,100));
        aimCircle.setPosition(sf::Vector2f(aimVect.x, aimVect.y));
        window.draw(aimCircle);
    }
}
//direction 0-����� ��������� �����,1-������
void Player::handlerEvent(sf::Event& event) {
    if (stage <= 1) {
        if (event.key.code == sf::Keyboard::Enter) {
            stage++;
            if (stage == 2) {
                turnOff = 1;
                // ���� directionShot � �������
                float angleRad = directionShot * 3.14159265f / 180.0f;
                float projectileGravity = powerShot * 10.0f; 
                
                float velocityXPr = std::cos(angleRad);
                float velocityYPr = std::sin(angleRad);
                projectile.push_back(Projectile(posX, posY - playerSize, velocityXPr, velocityYPr, projectileGravity, timeF, particlesF, map));
                //cout posX << " " << posY - playerSize << " " << velocityXPr << " " << velocityYPr << " " << projectileGravity << " " << '\n';
                return;
            }

        }
        else if (event.key.code == sf::Keyboard::BackSpace) {
            stage--;
            if (stage == -1) stage = 0;
        }

        if (stage == 0) {
            if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D) {
                velocityX = (event.key.code == sf::Keyboard::A) ? -0.2f : 0.2f;
                /*cout((event.key.code == sf::Keyboard::A) ? "A" : "D") << '\n';*/
                direction = (event.key.code == sf::Keyboard::A) ? 0 : 1;
            }
        }
        else if (stage == 1) {
            if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::S) {
                if (event.key.code == sf::Keyboard::A) {
                    directionShot -= 5;
                    if (directionShot < 0) {
                        directionShot = 360;
                    }
                }
                else if (event.key.code == sf::Keyboard::D) {

                    directionShot += 5;
                    if (directionShot > 360) {
                        directionShot = 0;
                    }

                }
                else if (event.key.code == sf::Keyboard::S) {
                    powerShot--;
                    if (powerShot < 5)powerShot = 5;

                }
                else if (event.key.code == sf::Keyboard::W) {
                    powerShot++;
                    if (powerShot > 100)powerShot = 100;
                }
                changePowerDirectionMove = 1;
            }
        }
    }
}
void Player::drawHpName() {
    sf::Font font;
    if (!font.loadFromFile("font.ttf")) {

    }

    // ��������� ����������� ��� ����� � �������� ������
    sf::Text playerNameHpText;
    playerNameHpText.setFont(font);
    playerNameHpText.setCharacterSize(10); // ������ ������
    playerNameHpText.setFillColor(command ? sf::Color::Red : sf::Color::Blue); // ������������� ���� ����� � ����������� �� �������

    // �������� � ����� ������ ����� �������
    std::stringstream hpStream;
    hpStream << std::fixed << std::setprecision(1) << hp;
    std::string hpString = hpStream.str();


    std::string hpNameString = playerName + "\n" + "HP " + hpString;
    playerNameHpText.setString(hpNameString);

    // ��������� ������ ����� �������� �� ������� ������ � ������� ������
    playerNameHpText.setPosition(posX * BLOCK_SIZE, (posY - 1) * BLOCK_SIZE - playerNameHpText.getLocalBounds().height - BLOCK_SIZE * 4);

    // ��������� ����������� �� ����
    window.draw(playerNameHpText);
}
void Player::drawPlayer() {
    playerSprite.setTexture(playerTexture);
    float corretSpriteSize = 1.5f;
    // ����� �������� ������� � ��� ��������
    playerSprite.setOrigin(playerSprite.getLocalBounds().width / 2, playerSprite.getLocalBounds().height / 2);
    if (hp > 0) {
        playerSprite.setScale(corretSpriteSize, corretSpriteSize); // ������������� ������� �� ����� ����
        playerSprite.setPosition(vt(posX * BLOCK_SIZE, posY * BLOCK_SIZE - BLOCK_SIZE * 2));
    }
    else {
        playerSprite.setScale(-corretSpriteSize, -corretSpriteSize); // ������������� ������� �� ����� ����
        playerSprite.setPosition(vt(posX * BLOCK_SIZE, posY * BLOCK_SIZE - BLOCK_SIZE * 2));
    }


    if (!direction) {
        //������ �� ����������� (�����)
        playerSprite.setScale(-corretSpriteSize, corretSpriteSize);
    }
    // ����� ������ ��������� � �������� ��������� (������)

    window.draw(playerSprite);
}


void Player::render(bool turn) {
    drawHpName();
    drawPlayer();
    if (turn) {
        if (stage == 1) {
            drawAim();
            drawPower();
        }
    }

    //drawCenter();



}

bool Player::getEndTurn() {
    return turnOff;
}
void Player::update(bool turn)
{
    applyVelocity();
}
void Player::drawPower() {
    //������ ������������� (������)
    sf::RectangleShape backPower;
    backPower.setFillColor(sf::Color::Transparent); // ���������� ����
    backPower.setOutlineColor(sf::Color::Black); // ���� �������
    backPower.setOutlineThickness(2);

    //�������� ������������� (�������)
    sf::RectangleShape frontPower;
    frontPower.setFillColor(sf::Color::Red);

    // ������� ���������������
    int powerSize = playerSize * 20/100*powerShot;
    sf::Vector2f size(playerSize*20 , playerSize);

    //  ������� � ������� ���������������
    backPower.setSize(sf::Vector2f(playerSize * 20, playerSize));
    frontPower.setSize(sf::Vector2f(powerSize, playerSize));

    //  ����� �������� ��������������� � ����� ����������� ����
    backPower.setOrigin(0, size.y / 2);
    frontPower.setOrigin(0, size.y / 2);

     // ���� � �������� �� ������ directionShot
    float angleRad = directionShot * 3.14159265f / 180.0f;

    //  ������� ��������������� �� ����������� ����
    backPower.setRotation(angleRad * 180.0f / 3.14159265f);
    frontPower.setRotation(angleRad * 180.0f / 3.14159265f);

     // ������� ��������������� ��� �������
    sf::Vector2f playerPosition = vt(posX * BLOCK_SIZE, posY * BLOCK_SIZE );
    backPower.setPosition(playerPosition.x, playerPosition.y - playerSize*5);
    frontPower.setPosition(playerPosition.x, playerPosition.y - playerSize * 5);
    



   window.draw(backPower);
   window.draw(frontPower);
}
void Player::drawCenter() {
    // ������ �������
    float aimRadius = 3.0f; // �������� ��� �������� �� �������� ������ �������

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



void Player::hit(float hitCount) {
    // ��������� ���� ������������ �� ������ ����������� �����
    //float knockbackForce = hitCount / 2; 

    //// ���������� ����������� ������������ (��������, � ��������������� ������� �� �����)
    //sf::Vector2f knockbackDirection = sf::Vector2f(coordinatePr.x - posX, coordinatePr.y - posY);

    //// ����������� ������ �����������
    //float length = std::sqrt(knockbackDirection.x * knockbackDirection.x + knockbackDirection.y * knockbackDirection.y);
    //if (length != 0) {
    //    knockbackDirection.x /= length;
    //    knockbackDirection.y /= length;
    //}

    //// ��������� ������������ � �������� ������
    //velocityX = -knockbackDirection.x * knockbackForce;
    //velocityY = -knockbackDirection.y * knockbackForce;


    if (hitCount != 0.0f) {
        std::stringstream hpStream;
        hpStream << std::fixed << std::setprecision(1) << hitCount / 2;
        std::string hpString = "-"+hpStream.str();
        particlesF.push_back(Particles(3, posX, posY , timeF, hpString));
        hp -= hitCount / 2;
    }

}
bool Player::isLive() {
    return(hp > 0) ? 1 : 0;
}

