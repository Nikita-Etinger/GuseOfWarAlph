#include "Projectile.h"





Projectile::Projectile(float positionX, float positionY, float velocityXS, float velocityYS, float powerShot, float& time,
    std::vector<Particles>& particles,

    std::vector<std::vector<int>>& maps):
    positionX(positionX), positionY(positionY),
    velocityX(velocityXS), velocityY(velocityYS),
    pushGravity(powerShot), timeF(time),
        particlesF(particles),
        map(maps) 
{
    texture.loadFromFile("projectile.png");
    std::cout << "projectile create" << '\n';

    float minPowerShot = 10.0f;
    float maxPowerShot = 1000.0f;
    float minGravity = 0.001f;
    float maxGravity = 0.00001f;


    std::cout << positionX << " " << positionY << " " << velocityX << " " << velocityY << " " << pushGravity << '\n';
    gravity = minGravity + (maxGravity - minGravity) * ((pushGravity - minPowerShot) / (maxPowerShot - minPowerShot));
    std::cout<<"projectile gravity" << std::to_string(gravity) << '\n';
}


void Projectile::normalizeVector(float& x, float& y) {
    float length = std::sqrt(x * x + y * y);
    if (length != 0) {
        x /= length;
        y /= length;
    }
}

void Projectile::update() {

    //std::cout << timeF << '\n';
    if (!explosion) {
        // Нормализуем вектор скорости
        normalizeVector(velocityX, velocityY);
        positionX += velocityX * speed *timeF;
        positionY += velocityY * speed *timeF;
        velocityY += gravity * timeF;


        bool flag = rand() % (1 + 1);
        if (1) {

            particlesF.push_back(Particles(1, positionX, positionY, timeF, ""));
        }
        // Устанавливаем угол поворота спрайта
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
         //Устанавливаем угол поворота спрайта
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
    map(other.map),
    gravity(other.gravity)
{}
