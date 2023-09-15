#include "Projectile.h"


const float gravity = 0.001f; //для замедления полета

Projectile::Projectile(float positionX, float positionY, float velocityXS, float velocityYS, float speed, float& time, std::vector<Particles>& particles)
    : positionX(positionX), positionY(positionY), velocityX(velocityXS), velocityY(velocityYS), speed(speed), timeF(time), particlesF(particles) {
    rotation = std::atan2(velocityY, velocityX) * 180 / 3.14159265f;
    //std::cout << "Create projectile" << std::endl;
}

bool Projectile::isActive() {
    return (timeLeft > 400);
}
void Projectile::applyVelocity() {
    if (!explosion) {
        // Обновляем вертикальную скорость с учетом гравитации
        velocityY += gravity;
    }
}

void Projectile::update() {
    timeLeft += timeF;
    std::cout << "Time: " << timeLeft << "\n";
    if (!explosion) {
        // Обновляем позицию снаряда на основе скорости
        positionX += velocityX * speed* timeF;
        positionY += velocityY * speed* timeF;
        bool t= rand() % (1 - 0 + 1) + 0;
        if(t)particlesF.push_back(Particles(1, positionX, positionY, timeF,""));
        rotation = std::atan2(velocityY, velocityX) * 180 / 3.14159265f;
        // Обновляем вертикальную скорость с учетом гравитации
        velocityY += gravity;
    }
}
void Projectile::draw(sf::RenderWindow& window) {
    if (!explosion) {
        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(10, 10));
        rect.setPosition(sf::Vector2f(positionX * BLOCK_SIZE - 2, positionY * BLOCK_SIZE + 5));
        rect.setFillColor(sf::Color::Yellow);
        rect.setRotation(rotation);
        texture.loadFromFile("projectile.png");
        sprite.setTexture(texture);
        sprite.setPosition(positionX * BLOCK_SIZE, positionY * BLOCK_SIZE);
        // Устанавливаем угол поворота спрайта
        sprite.setRotation(rotation);
        window.draw(rect);
        window.draw(sprite);
        
    }

}
bool Projectile::getStatus() {
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
void Projectile::explosions(){
    particlesF.push_back(Particles(2, positionX, positionY, timeF,""));
    for (int i = 0; i <10; i++) {
        int x = rand() % (10 - (-10) + 1) + (-10);
        int y = rand() % (10 - (-10) + 1) + (-10);
        particlesF.push_back(Particles(1, positionX+x, positionY+y, timeF,""));
    }
    if(!explosion)
    explosion = 1;
}
bool Projectile::operator==(Projectile& other){
    return (*this == other);
}

bool Projectile::operator!=( Projectile& other){
    return !(*this == other);
}
//void Projectile::operator=(Projectile& other) {
//    other = *this;
//
//}