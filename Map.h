#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include <fstream>
#include "sstream"
#include "Config.h"
#include <mutex>

class Map {
public:
    Map(sf::RenderWindow& windowS);
    std::mutex mutex;
    virtual void run()=0;
    virtual void explosion(vt coordinate, float radius);
    bool mapUpdateComlite = 0;
    bool needClose;
protected:
    sf::Sprite backGroundSprite;
    sf::Texture backGroundTexture;
    sf::RenderTexture mapTexture;
    sf::Sprite mapSprite;
    sf::RenderWindow& window;
    std::vector<std::vector<int>> map;
    std::vector<std::vector<int>> mapBuf;
    sf::Clock clock;
    
    std::vector<Button> buttons;
    bool needUpdateMap=false;
    sf::Color colors[9]{ sf::Color::Color(255, 250, 205),
        sf::Color::Green,
        sf::Color::Red,
        sf::Color::Blue,
        sf::Color::Magenta,
        sf::Color::Cyan,
        sf::Color::White,
        sf::Color(255, 128, 0),  // ��������� ���� 
        sf::Color(0, 255, 255)   // ����-������� ���� 
    };
    bool flagUpdate = false;
    float time = 0;

    //���������� � map
    virtual void applyPhysics();
    virtual void loadMapFromFile(); // ����� ���������� ��� �������� �����
    virtual void drawMap();
    virtual void updateMapTexture();
    //���������� � �����������
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void handleEvents() = 0;

    
};