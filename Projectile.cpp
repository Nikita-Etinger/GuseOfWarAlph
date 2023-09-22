#include "Projectile.h"


const float gravity = 0.001f; //дл€ замедлени€ полета

Projectile::Projectile(float positionX, float positionY, float velocityXS, float velocityYS, float speed, float& time, std::vector<Particles>& particles)
    : positionX(positionX), positionY(positionY), velocityX(velocityXS), velocityY(velocityYS), speed(speed), timeF(time), particlesF(particles) {
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
    if (!explosion) {
        timeLeft += timeF;
        timeRender += timeF;//сколько времени прошло с последнего обновлени€ 
        timeLeft += timeF;//сколько времени прошло
        //std::cout << "Time: " << timeF << '\n';
        //std::cout << "Time Render: " << timeRender << '\n';
        //std::cout << "TimeLeft: " << timeLeft / timeRender << '\n';
        if (timeRender>100000) {


            //std::cout << "Time: " << timeLeft << "\n";
            bool flag = rand() % (1 + 1);
            if (flag) {

                particlesF.push_back(Particles(1, positionX, positionY, timeF, ""));

            }
                // ќбновл€ем позицию снар€да на основе скорости
            positionX += velocityX * speed / 100 * timeF / 100;
            positionY += velocityY * speed / 100 * timeF / 100;
            

            rotation = std::atan2(velocityY, velocityX) * 180 / 3.14159265f;
            // ќбновл€ем вертикальную скорость с учетом гравитации
            velocityY += gravity;

            timeRender = 0;
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
    
    //particlesF.push_back(Particles(2, positionX, positionY, timeF, ""));
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
    timeF(other.timeF)
{
    // ≈сли вектор particlesF содержит указатели или ссылки на объекты,
    // то нужно убедитьс€, что они правильно копируютс€ или перенос€тс€.
    // ≈сли это объекты класса Particles, убедитесь, что класс Particles имеет
    // корректно определенный оператор копировани€ или перемещени€.
}

