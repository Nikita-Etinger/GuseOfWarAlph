#include "Projectile.h"

Projectile::Projectile(std::vector<std::vector<int>>& mapS)
    : map(mapS) {

    std::cout << "Create projectile" << std::endl;
}

void Projectile::update() {
    if (!explosion) {
    }
}

void Projectile::applyVelocity() {

}

void Projectile::createExplosion() {

}

bool Projectile::getStatus() {
    return explosion;
}

bool Projectile::isValidPosition(float x, float y) {
    return true;
}