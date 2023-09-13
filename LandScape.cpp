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
            players.push_back(Player(map, window, 0, i + 3, "Jojo", projectile,time));
            //std::cout << "Player add:" << i + 3 << std::endl;
        }
        for (int i = 0; i < 2; i++) {
            players.push_back(Player(map, window, 1, i + 6, "Jojo", projectile,time));
            //std::cout << "Player add:" << i + 6 << std::endl;
        }
    }
    else
    players.push_back(Player(map, window, 1, 3, "Jojo", projectile,time));


    sf::Clock clock;

    while (window.isOpen()) {
        time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 500;
        //std::cout << "time: " << time << '\n';
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
    scanCollicionProjectile();
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
                    projectile.push_back(Projectile(mapX, mapY, 0.1f, -0.1f, 0.1f,time));
                    /*pl.scanContactProjectile(5, vt(mapX, mapY));*/
                    //explosion(vt(mapY, mapX), 5);
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


void LandScape::scanCollicionProjectile() {
    //как правило снар€д всегда один
    for (auto& pr : projectile) {
        pr.update();
        pr.draw(window);

        for (auto& pl : players) {
            if (pl.scanContactProjectile(pr.getRadius(), pr.getCoordinate())) {
                
                if (pr.getStatus()==false) {
                    std::cout << "BOOM1" << '\n';
                    pr.explosions();//мен€ет статус снар€да как взорван
                    
                }
            }
            
        }
        //если взрыва не произашло, провер€етс€ контакт с землЄй
        if (!pr.getStatus()) {
            for (int i = -pr.getSize(); i <= pr.getSize(); i++) {
                for (int j = -pr.getSize(); j <= pr.getSize(); j++) {

                    if (pr.getCoordinate().x + i < map[0].size() - 1 && pr.getCoordinate().x + i>1 && pr.getCoordinate().y + j < map.size() - 1 && pr.getCoordinate().y + j>1) {
                        
                        if (map[pr.getCoordinate().y + j][pr.getCoordinate().x + j] > 0) {
                            pr.explosions();
                            std::cout << "BOOM2" << '\n';
                            
                        }
                    }
                    else pr.explosions();
                    if (pr.getStatus())break;

                }
                if (pr.getStatus())break;
            }
        }

        if (pr.getStatus()) {
            projectile.pop_back();
            explosion(vt(pr.getCoordinate().y, pr.getCoordinate().x), pr.getRadius());// создаЄт дыру в месте взрыва
        }
    }



}