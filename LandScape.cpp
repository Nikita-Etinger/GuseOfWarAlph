#include "LandScape.h"



LandScape::LandScape(sf::RenderWindow& windows) : Map(windows)
{
    map.resize(WINDOW_H / BLOCK_SIZE, std::vector<int>(WINDOW_W / BLOCK_SIZE, 0));
    mapTexture.create(WINDOW_W, WINDOW_H);
    loadMapFromFile();
    updateMapTexture();
    
}

void LandScape::run()
{
    mapTexture.create(WINDOW_W, WINDOW_H);
    loadMapFromFile();
    updateMapTexture();
    buttons.push_back(Button(sf::Vector2f(BUTTON_SIZE, BUTTON_SIZE / 2),
        sf::Vector2f(BUTTON_SIZE * 0, 0),
        sf::Color(130, 78, 100, 255),
        sf::Color(255, 255, 255, 255),
        10, "EXIT"));
    if (1 /*создать игроков или одного*/) {
        for (int i = 0; i < 3; i++) {
            players.push_back(Player(map, window, 0, i + 3, "Jojo", projectile,time, particlesF));
            //std::cout << "Player add:" << i + 3 << std::endl;
        }
        for (int i = 0; i < 3; i++) {
            players.push_back(Player(map, window, 1, i + 6, "Jojo", projectile,time, particlesF));
            //std::cout << "Player add:" << i + 6 << std::endl;
        }
    }
    else
    players.push_back(Player(map, window, 1, 3, "Jojo", projectile,time,particlesF));


    sf::Clock clock;

    while (window.isOpen()) {
        if (needClose) {
            players.clear();
            projectile.clear();
            particlesF.clear();
            needClose = 0;
            break;
        }
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


    for (int i = 0; i < players.size(); i++) {
        if (i == indexPlayer) {
            players[i].update(1);
            if (players[i].getEndTurn()) {
                players[i].resetStage();
                indexPlayer++;
                if (indexPlayer >= players.size() - 1) {
                    indexPlayer = 0;
                }

            }
        }
        else {
            players[i].update(0);
        }

    }
    scanCollicionProjectile();

    for (auto& par : particlesF) {
        par.update();
        par.draw(window);
    }

}
void LandScape::render()
{
    window.clear();

    drawMap();
    for (auto& but : buttons) {
        but.render(window);
    }
    if (particlesF.size()>3) {
        std::cout << particlesF[particlesF.size() - 2].getStatus() << '\n';
        if (particlesF[particlesF.size() - 2].getStatus()) {
            particlesF.clear();
            std::cout << " PART CLEAR" << '\n';
        }
    }
    if (!projectile.empty()) {
        if (projectile.empty()) {
            if (projectile[projectile.size() - 1].getStatus()) {
                projectile.clear();
                std::cout << " PART CLEAR" << '\n';
            }
        }
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
            players[indexPlayer].handlerEvent(event);
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
            sf::Vector2f localPosition(event.mouseButton.x, event.mouseButton.y);
            for (auto& x : buttons) {
                if (x.getRectangle().getGlobalBounds().contains(localPosition)) {
                    std::string str = x.getString();
                    if (str == "EXIT") {
                        needClose = true;
                    }
                }
            }
            // —оздаем снар€д и добавл€ем его в вектор
            projectile.push_back(Projectile(mapX, mapY, 0.1f, -0.1f, 0.5f, time, particlesF));
            //if (1) {
            //    for (auto& pl : players) {
            //        
            //        /*needUpdateMap = 1;
            //        flagUpdate=1;*/
            //    }
            //}
        }
        

    }
    
}
std::vector<std::vector<int>>& LandScape::getMap() {
    return map;
}


void LandScape::scanCollicionProjectile() {
    //как правило снар€д всегда один
    for (auto& pr : projectile) {
        if (!pr.getStatus()) {
            
            vt positionPr = pr.getCoordinate();
            int sizePr = pr.getSize();
            float radiusPr = pr.getRadius();
            bool exp = 0;
            if (pr.isActive()) {
                for (auto& pl : players) {
                    if (pl.scanContactProjectile(radiusPr, positionPr)) {

                        if (pr.getStatus() == false) {
                            /*std::cout << "BOOM1" << '\n';*/
                            exp = 1;

                        }
                    }

                }

                if (exp) {
                    pr.explosions();//мен€ет статус снар€да как взорван
                }
                //если взрыва не произашло, провер€етс€ контакт с землЄй
                if (!exp) {
                    for (int i = -sizePr; i <= sizePr; i++) {
                        for (int j = -sizePr; j <= sizePr; j++) {

                            if (positionPr.x + i < map[0].size() - 2 && positionPr.x + i>1 && positionPr.y + j < map.size() - 2 && positionPr.y + j>1) {

                                if (map[positionPr.y + j][positionPr.x + j] > 0) {
                                    pr.explosions();
                                    exp = 1;
                                    std::cout << "BOOM2" << '\n';
                                }
                            }
                            else {
                                pr.explosions();
                                exp = 1;
                            }
                            if (exp)break;

                        }
                        if (exp)break;
                    }
                }
            }

            if (pr.getStatus()) {
                //pr.explosions();
                explosion(vt(positionPr.y, positionPr.x), radiusPr);// создаЄт дыру в месте взрыва
                
            }
            if (!pr.getStatus()) {
                pr.update();
                pr.draw(window);
            }
        }
        
    }



}