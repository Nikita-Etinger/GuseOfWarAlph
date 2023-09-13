#include "Projectile.h"

Projectile::Projectile(float positionXS,float positionYS, float velocityXS, float velocityYS, float speedS)
    :positionX(positionXS), positionY(positionYS), velocityX(velocityXS),velocityY(velocityYS), speed(speedS) {

    std::cout << "Create projectile" << std::endl;
}

void Projectile::applyVelocity() {

}

void Projectile::update(){

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