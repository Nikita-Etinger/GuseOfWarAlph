#include "Projectile.h"



const float gravity = 0.0001f; //дл€ замедлени€ полета

Projectile::Projectile(float positionX, float positionY, float velocityXS, float velocityYS, float speed, float& time,
    std::vector<Particles>& particles,

    std::vector<std::vector<int>>& maps):
    positionX(positionX), positionY(positionY),
    velocityX(velocityXS), velocityY(velocityYS),
    speed(speed), timeF(time),
        particlesF(particles),
        map(maps) 
{
    //std::cout << "Create projectile" << std::endl;
    texture.loadFromFile("projectile.png");
    std::cout << "projectile create" << '\n';
    
}

bool Projectile::isActive() {
    //таймер с какого момента снар€д становитс€ активен
    return (1/*timeLeft > 00000*0.8*/);
}
void Projectile::applyVelocity() {
    //if (!explosion) {
    //    // ќбновл€ем вертикальную скорость с учетом гравитации
    //    velocityY += gravity;
    //}
}

void Projectile::update() {
    //time = clock.getElapsedTime().asMicroseconds();
    //clock.restart();
    //time = time / 2000;
    std::cout << timeF << '\n';
    if (!explosion) {
        // ќбновл€ем позицию снар€да на основе скорости
        positionX += velocityX * speed / 1000*timeF/ 8;
        positionY += velocityY * speed / 1000*timeF/ 8;

        // ќбновл€ем вертикальную скорость с учетом гравитации
        velocityY += gravity * timeF/8;
        bool flag = rand() % (1 + 1);
        if (1) {

            particlesF.push_back(Particles(1, positionX, positionY, timeF, ""));

        }
        // ”станавливаем угол поворота спрайта
        rotation = std::atan2(velocityY, velocityX) * 180 / 3.14159265f;


        if (positionX >= 2 && positionX < map[0].size() - 2 && positionY >= 2 && positionY < map.size() - 2) {
            if (map[positionY][positionX] > 0) {
                explosions();
            }
        }
        else {
            explosion = 1;
        }
    }

}
void Projectile::outOfMap() {
    explosion = 1;
}
void Projectile::render(sf::RenderWindow& window) {
    if (!explosion) {

        sprite.setTexture(texture);
        sprite.setPosition(positionX * BLOCK_SIZE, positionY * BLOCK_SIZE);
         //”станавливаем угол поворота спрайта
        sprite.setRotation(rotation);
        window.draw(sprite);
        
    }

}
void Projectile::explosions() {
    
    particlesF.push_back(Particles(2, positionX, positionY, timeF, ""));
    //for (int i = 0; i < 10; i++) {
    //    int x = rand() % (10 - (-10) + 1) + (-10);
    //    int y = rand() % (10 - (-10) + 1) + (-10);
    //    particlesF.push_back(Particles(1, positionX + x, positionY + y, timeF, ""));
    //}
    explosion = 1;
}
bool Projectile::isExplosion() {
    return explosion;
}
vt Projectile::getCoordinate() {
    return vt(positionX, positionY);
}
float Projectile::getRadius() {
    return radius;
}
int Projectile::getSize() {
    return size;
}

//bool Projectile::operator==(Projectile& other){
//    return (*this == other);
//}
//
//bool Projectile::operator!=( Projectile& other){
//    return !(*this == other);
//}
////void Projectile::operator=(Projectile& other) {
////    other = *this;
////
////}

Projectile::Projectile(const Projectile& other)
    : explosion(other.explosion),
    velocityX(other.velocityX),
    velocityY(other.velocityY),
    speed(other.speed),
    radius(other.radius),
    size(other.size),
    positionX(other.positionX),
    positionY(other.positionY),
    timeRender(other.timeRender),
    sprite(other.sprite),
    texture(other.texture),
    rotation(other.rotation),
    particlesF(other.particlesF),
    timeLeft(other.timeLeft),
    timeF(other.timeF),
    map(other.map)
{}
