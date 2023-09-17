#include "LandScape.h"
#include <thread>



LandScape::LandScape(sf::RenderWindow& windows) : Map(windows)
{
    map.resize(WINDOW_H / BLOCK_SIZE, std::vector<int>(WINDOW_W / BLOCK_SIZE, 0));
    mapTexture.create(WINDOW_W, WINDOW_H);

    
}
bool LandScape::getNeedClose() {
    return needClose;
}
void LandScape::run()
{
    
    {
        std::lock_guard<std::mutex> lock(mutex);
        loadMapFromFile();
    }
    std::thread myThreadPhysics([this]() {

        applyPhysics();
     });

    std::thread myThreadProjectileCollision([this]() {
        
        scanCollicionProjectile();
     });
    
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

            /*std::cout << "need Close: " << needClose << '\n';*/
            // «авершаем поток myThread
            {
                std::lock_guard<std::mutex> lock(mutex);
                std::cout << "thread close " << '\n';
                map.clear();
                projectile.clear();
            }
            myThreadPhysics.join();
            myThreadProjectileCollision.join();

                // ”станавливаем флаг needClose в 0 (false)
                needClose = false;
                // ќчищаем другие ресурсы и выходим из цикла
                players.clear();
                projectile.clear();
                particlesF.clear();

            break;
        }
        std::cout << "Particles size: " << particlesF.size()<<'\n';
        time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;
        render();

    }
}
    




void LandScape::update() {
    handleEvents();

    if (!needClose) {
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

        //int count = 0;
        for (auto& par : particlesF) {

            if (!par.getStatus()) {
                //count++;
                par.update();
                par.draw(window);
            }
        }
        //std::cout << projectile.size() << '\n';
    }

}
void LandScape::render()
{
    window.clear();
    if (!needClose) {
        drawMap();
        for (auto& but : buttons) {
            but.render(window);
        }
        if (particlesF.size() > 3) {
            /*std::cout << particlesF[particlesF.size() - 2].getStatus() << '\n';*/
            if (particlesF[particlesF.size() - 2].getStatus()) {
                {
                    std::lock_guard<std::mutex> lock(mutex);
                    particlesF.clear();
                }
                std::cout << " PART CLEAR" << '\n';
            }
        }
        if (!projectile.empty()) {
            if (projectile[projectile.size() - 1].getStatus()) {
                {
                    std::lock_guard<std::mutex> lock(mutex);
                    projectile.clear();
                }
                std::cout << " PROJECTILE CLEAR" << '\n';
            }

            {
                std::lock_guard<std::mutex> lock(mutex);
                for (auto& pr : projectile) {
                        pr.draw(window);
                }
            }

        }

        update();
    }
    if (!needClose) {
        window.display();
    }
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
                        std::lock_guard<std::mutex> lock(mutex);
                        needClose = true;
                        return;
                    }
                }
            }
            // —оздаем снар€д и добавл€ем его в вектор
            {
                std::lock_guard<std::mutex> lock(mutex);
                projectile.push_back(Projectile(mapX, mapY, 0.1f, -0.1f, 0.5f, time, particlesF));
            }

        }
        

    }
    
}
std::vector<std::vector<int>>& LandScape::getMap() {
    return map;
}


void LandScape::scanCollicionProjectile() {
    while (!map.empty()) {
        {
            std::lock_guard<std::mutex> lock(mutex);
            //как правило снар€д всегда один, но работает со всеми
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
                                    int x_check = positionPr.x + i;
                                    int y_check = positionPr.y + j;

                                    if (x_check >= 1 && x_check < map[0].size() - 1 && y_check >= 1 && y_check < map.size() - 1) {
                                        // ѕроверка на контакт с блоками карты
                                        if (map[y_check][x_check] > 0) {
                                            pr.explosions();
                                            exp = 1;
                                            explosion(vt(positionPr.y, positionPr.x), radiusPr);
                                        }
                                    }
                                    else {
                                        // ѕроверка на край карты
                                        pr.outOfMap();
                                        exp = 1;
                                    }

                                    if (exp) break;
                                }
                                if (exp) break;
                            }
                        }
                    }
                    if (!pr.getStatus()) {
                        pr.update();
                    }


                }

            }
        }
    }



}