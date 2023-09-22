#include "Player.h"

//map.size() расстояние по Y map[0].size() расстояние по X !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
//законченные методы __________________________________________________________________________________________________________________________________________________________________________________________________________________________________________

void Player::PlacePositionOnMap() {
     //Помещаем игрока на карту
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
        // Снаряд долетел до игрока, отбрасываем игрока 
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
    // Проверяем, касается ли игрок земли
    onGround = isOnGround();
    // Сохраняем начальное положение игрока
    int initialPosX = posX;
    int initialPosY = posY;

    if (onGround) {
        velocityY = 0.0f;
    }
    else {
        velocityY += gravity;
    }

    // Переместить игрока на новую позицию, учитывая его скорость (velocityX и velocityY)
    posX += velocityX + accelerationX * timeF;
    posY += velocityY + accelerationY * timeF;




    // Проверяем новую позицию игрока
    bool flagValid = ScanPosition();
    if (!flagValid) {
        posY--;//уменьшаем posY и снова проверяем (тоесть проверка на то что впереди блок в высоту)
        flagValid = ScanPosition();
    }
    if (!flagValid) {
        posY--;//уменьшаем posY и снова проверяем (тоесть проверка на то что впереди 2блока в высоту)
        flagValid = ScanPosition();
    }

    if (flagValid) {
        // Успешно размещаем игрока
        PlacePositionOnMap();
    }
    else {
        // Если не удалось разместить игрока, вернуть его на начальное положение
        posX = initialPosX;
        posY = initialPosY;
      
        //velocityX = 0;
        //velocityY = 0;
    }
    if (accelerationX > 0)accelerationX -= accelerationY / 3 * timeF;
    else if (accelerationX < 0)accelerationX+= accelerationY / 3 * timeF;
    else accelerationX = 0;
    if (accelerationY > 0)accelerationY-= accelerationY / 3 * timeF;
    else if (accelerationY < 0)accelerationY += accelerationY/3 * timeF;
    else accelerationY = 0;

}

bool Player::isOnGround() {
    if (posY + 2 >= map.size()) { //игрок достиг конца карты по Y
        //cout "XXXXXXXXXXXX" << '\n';
        if (distanceFall > 2) {
            hit(distanceFall);
        }
        distanceFall = 0;
        return true;
    }

    // Проверяем, есть ли блоки под игроком в пределах его горизонтальной ширины
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

    // Радиус прицела
    float aimRadius = 3.0f; // размер прицела

    // положение прицела относительно центра игрока, учитывая размер блока
    float aimX = (posX+playerSize/2) * BLOCK_SIZE + 50.0f * std::cos(directionShot * 3.14159265f / 180.0f); // Расстояние в направлении directionShot
    float aimY = (posY+playerSize / 2)* BLOCK_SIZE + 50.0f * std::sin(directionShot * 3.14159265f / 180.0f);

    //  окружность (прицел) с красной обводкой
    sf::CircleShape aimCircle(aimRadius);
    aimCircle.setFillColor(sf::Color::Transparent); // цвет заполнения (прозрачный)
    aimCircle.setOutlineColor(sf::Color::White); //цвет обводки (красный)
    aimCircle.setOutlineThickness(2.0f); // Толщина обводки

    // положение прицела
    aimCircle.setPosition(aimX - aimRadius  * BLOCK_SIZE / 2,aimY - aimRadius  * BLOCK_SIZE / 2);


    // Отрисовываем прицел на окне
    window.draw(aimCircle);
}
void Player::drawHpName() {
    sf::Font font;
    if (!font.loadFromFile("font.ttf")) {

    }

    // текстовое отображение для имени и здоровья игрока
    sf::Text playerNameHpText;
    playerNameHpText.setFont(font);
    playerNameHpText.setCharacterSize(10); // Размер шрифта
    playerNameHpText.setFillColor(command ? sf::Color::Red : sf::Color::Blue); // Устанавливаем цвет имени в зависимости от команды

    // здоровье с одним знаком после запятой
    std::stringstream hpStream;
    hpStream << std::fixed << std::setprecision(1) << hp;
    std::string hpString = hpStream.str();


    std::string hpNameString = playerName + "\n" + "HP " + hpString;
    playerNameHpText.setString(hpNameString);

    // Положение текста будет зависеть от позиции игрока и размера шрифта
    playerNameHpText.setPosition(posX * BLOCK_SIZE, (posY - 1) * BLOCK_SIZE - playerNameHpText.getLocalBounds().height - BLOCK_SIZE * 4);

    // текстовое отображение на окне
    window.draw(playerNameHpText);
}
void Player::drawPlayer() {
    playerSprite.setTexture(playerTexture);
    float corretSpriteSize = 1.5f;
    // центр вращения спрайта в его середину
    playerSprite.setOrigin(playerSprite.getLocalBounds().width / 2, playerSprite.getLocalBounds().height / 2);
    if (hp > 0) {
        playerSprite.setScale(corretSpriteSize, corretSpriteSize); // Устанавливаем масштаб по обеим осям
        playerSprite.setPosition(vt(posX * BLOCK_SIZE, posY * BLOCK_SIZE - BLOCK_SIZE * 2));
    }
    else {
        playerSprite.setScale(-corretSpriteSize, -corretSpriteSize); // Устанавливаем масштаб по обеим осям
        playerSprite.setPosition(vt(posX * BLOCK_SIZE, posY * BLOCK_SIZE - BLOCK_SIZE * 2));
    }


    if (!direction) {
        //спрайт по горизонтали (влево)
        playerSprite.setScale(-corretSpriteSize, corretSpriteSize);
    }
    // Иначе спрайт останется в исходном положении (вправо)

    window.draw(playerSprite);
}


void Player::render(bool turn) {
    if (turn) {
        if (stage == 1) {
            //drawAim();
            drawPower();
        }
    }
    drawHpName();
    drawPlayer();
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
    //задний прямоугольник (черный)
    sf::RectangleShape backPower;
    backPower.setFillColor(sf::Color::Transparent); // Прозрачный цвет
    backPower.setOutlineColor(sf::Color::Black); // Цвет границы
    backPower.setOutlineThickness(2);

    //передний прямоугольник (красный)
    sf::RectangleShape frontPower;
    frontPower.setFillColor(sf::Color::Red);

    // Размеры прямоугольников
    int powerSize = playerSize * 20/100*powerShot;
    sf::Vector2f size(playerSize*20 , playerSize);

    //  размеры и позиции прямоугольников
    backPower.setSize(sf::Vector2f(playerSize * 20, playerSize));
    frontPower.setSize(sf::Vector2f(powerSize, playerSize));

    //  центр вращения прямоугольников в левый центральный угол
    backPower.setOrigin(0, size.y / 2);
    frontPower.setOrigin(0, size.y / 2);

     // угол в радианах на основе directionShot
    float angleRad = directionShot * 3.14159265f / 180.0f;

    //  поворот прямоугольников на вычисленный угол
    backPower.setRotation(angleRad * 180.0f / 3.14159265f);
    frontPower.setRotation(angleRad * 180.0f / 3.14159265f);

     // позиции прямоугольников над игроком
    sf::Vector2f playerPosition = vt(posX * BLOCK_SIZE, posY * BLOCK_SIZE );
    backPower.setPosition(playerPosition.x, playerPosition.y - playerSize*5);
    frontPower.setPosition(playerPosition.x, playerPosition.y - playerSize * 5);
    



   window.draw(backPower);
   window.draw(frontPower);
}
void Player::drawCenter() {
    // Радиус прицела
    float aimRadius = 3.0f; // Замените это значение на желаемый размер прицела

    // Создаем окружность (прицел) с красной обводкой
    sf::CircleShape aimCircle(aimRadius);
    aimCircle.setFillColor(sf::Color::Red); // Задаем цвет заполнения (прозрачный)
    aimCircle.setOutlineColor(sf::Color::White); // Задаем цвет обводки (красный)
    aimCircle.setOutlineThickness(2.0f); // Толщина обводки

    // Устанавливаем положение прицела
    aimCircle.setPosition(posX * BLOCK_SIZE, posY* BLOCK_SIZE);


    // Отрисовываем прицел на окне
    window.draw(aimCircle);


}

//direction 0-игрок направлен влево,1-вправо
void Player::handlerEvent(sf::Event& event) { 
    if (stage <= 1) {
        if (event.key.code == sf::Keyboard::Enter) {
            stage++;
            if (stage == 2) {
                turnOff = 1;
                // угол directionShot в радианы
                float angleRad = directionShot * 3.14159265f / 180.0f;

                //конвертер диапазона
                ////////////////////////////////////////////////////////////////////////
                //входной и выходной диапазоны
                float inputMin = 5.0f;
                float inputMax = 100.0f;
                float outputMin = 0.1f;
                float outputMax = 0.4f;


                float inputValue = powerShot;


                float inputRange = inputMax - inputMin;
                float outputRange = outputMax - outputMin;
                float outputValue = ((inputValue - inputMin) / inputRange) * outputRange + outputMin;


                ////////////////////////////////////////////////////////////////////

               // Вычислите компоненты velocityX и velocityY на основе угла
                float projectileSpeed = outputValue;
                float velocityXPr = projectileSpeed * std::cos(angleRad);
                float velocityYPr = projectileSpeed * std::sin(angleRad);



                // Создайте снаряд с вычисленными компонентами
                projectile.push_back(Projectile(posX, posY-playerSize, velocityXPr, velocityYPr, outputValue*10, timeF, particlesF,map));
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
            if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D|| event.key.code == sf::Keyboard::W|| event.key.code == sf::Keyboard::S) {
                if (event.key.code == sf::Keyboard::A) {
                    directionShot -= 5;
                    if (directionShot < 0) {
                        directionShot = 360;
                    }
                }
                else if (event.key.code == sf::Keyboard::D){

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
            }
        }
        else if (stage == 2) {

        }
    }
}

void Player::hit(float hitCount) {
    //получение урона
        // Форматируем здоровье с одним знаком после запятой
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

