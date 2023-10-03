#pragma once
#include "Config.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

class Particles
{
private:
    const float speed = 100;
    float& timeS;
    float timeLeft = 0;

    bool needDelete = false;
    float positionX = 0;
    float positionY = 0;

    int typeS = 0;
    float timeLive = 0;
    float sizeVape = 0;
    sf::Color colorVape;
    float visible = 255;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Text text;
    sf::Font font;
    int randSize;

public:
    static sf::Texture vapeTexture;
    static sf::Texture explosionTexture;

    Particles(int type, float positionXS, float positionYS, float& time, std::string newtext);


    void update();
    void render(sf::RenderWindow& window);
    bool getStatus();

    bool operator!=(Particles& other);

    void setTexture();
    Particles& operator=(const Particles& other) {
        if (this != &other) {  // Проверка на самоприсваивание
            // Копируйте значения всех членов класса
            timeS = other.timeS;
            timeLeft = other.timeLeft;
            needDelete = other.needDelete;
            positionX = other.positionX;
            positionY = other.positionY;
            typeS = other.typeS;
            timeLive = other.timeLive;
            sizeVape = other.sizeVape;
            colorVape = other.colorVape;
            visible = other.visible;
            sprite = other.sprite;
            texture = other.texture;
        }
        return *this;  // Вернуть *this для поддержки цепочки присваиваний
    }
};

