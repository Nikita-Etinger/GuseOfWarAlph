#include "Projectile.h"
const float gravity = 0.0005f; //для замедления полета

Projectile::Projectile(float positionXS,float positionYS, float velocityXS, float velocityYS, float speedS,float& time)
    :positionX(positionXS), positionY(positionYS), velocityX(velocityXS),velocityY(velocityYS), speed(speedS), timeF(time) {

    //std::cout << "Create projectile" << std::endl;
}

void Projectile::applyVelocity() {
    if (!explosion) {
        // Обновляем вертикальную скорость с учетом гравитации
        velocityY += gravity;
    }
}

void Projectile::update() {
    if (!explosion) {
        // Обновляем позицию снаряда на основе скорости
        positionX += velocityX * speed* timeF;
        positionY += velocityY * speed* timeF;

        // Уменьшаем скорость снаряда постепенно
        //speed *= 0.99f; // 0.99 - коэффициент замедления
        //speed += gravity;

        // Обновляем вертикальную скорость с учетом гравитации
        velocityY += gravity;
    }
}
void Projectile::draw(sf::RenderWindow& window) {
    if (!explosion) {

        sf::RectangleShape projectileShape(sf::Vector2f(5, 5));

        projectileShape.setPosition(positionX*BLOCK_SIZE, positionY * BLOCK_SIZE);

        window.draw(projectileShape);
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
    explosion = 1;
}