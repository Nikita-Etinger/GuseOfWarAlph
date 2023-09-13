#include "Classes.h"



LandScape::LandScape(sf::RenderWindow& windows) : Map(windows)
{
    map.resize(WINDOW_H / BLOCK_SIZE, std::vector<int>(WINDOW_W / BLOCK_SIZE, 0));
    mapTexture.create(WINDOW_W, WINDOW_H);
    loadMapFromFile();
    updateMapTexture();
    
}

void LandScape::run()
{

    loadMapFromFile();
    updateMapTexture();
    if (1 /*создать игроков или одного*/) {
        for (int i = 0; i < 2; i++) {
            players.push_back(Player(map, window, 0, i + 3, "Jojo", projectile));
            //std::cout << "Player add:" << i + 3 << std::endl;
        }
        for (int i = 0; i < 2; i++) {
            players.push_back(Player(map, window, 1, i + 6, "Jojo", projectile));
            //std::cout << "Player add:" << i + 6 << std::endl;
        }
    }
    else
    players.push_back(Player(map, window, 1, 3, "Jojo", projectile));

    while (window.isOpen()) {
        
        //update();
        render();
    }
}



void LandScape::update() {
    handleEvents();
    for (auto& p : projectile) {
        p.update();
    }
    for (auto& p : players) {
        p.update();
        
    }
}
void LandScape::render()
{
    window.clear();

    drawMap();
    for (auto& but : buttons) {
        but.render(window);
    }
    update();
    window.display();
}

void LandScape::handleEvents()
{
    //std::cout << "mouseX: " << mousePosX << " mouseY: " << mousePosY << std::endl;
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            for (auto& p : players) {
                p.handlerEvent(event);
            }
        }
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        // ѕреобразуем позицию мыши в координаты карты
        int mapX = mousePosition.x / BLOCK_SIZE;
        int mapY = mousePosition.y / BLOCK_SIZE;
        mousePosX=mapX;
        mousePosY=mapY;
        

        //// ќбработка нажати€ левой кнопки мыши дл€ создани€ снар€да (ожидает реализации)
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            // ѕолучаем позицию мыши относительно окна
            
            // —оздаем снар€д и добавл€ем его в вектор
            if (1) {
                for (auto& pl : players) {
                    pl.scanContactProjectile(5, vt(mapX, mapY));
                    explosion(vt(mapY, mapX), 5);
                    needUpdateMap = 1;
                    flagUpdate=1;
                }
            }
            else if (projectile[0].getStatus()) {
                projectile.clear();
            }
        }
        

    }
    
}
std::vector<std::vector<int>>& LandScape::getMap() {
    return map;
}


