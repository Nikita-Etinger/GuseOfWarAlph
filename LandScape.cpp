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
    font.loadFromFile("font.ttf");

    {
        std::lock_guard<std::mutex> lock(mutex);
        loadMapFromFile();
    }
    std::thread myThreadPhysics([this]() {

        applyPhysics();
     });
    std::thread myThreadParticlesCleaner([this]() {

        ParticlesCleaner();
        });
    std::thread myThreadProjectileCollision([this]() {
        
        scanCollisionProjectile();
     });
    
    buttons.push_back(Button(sf::Vector2f(BUTTON_SIZE, BUTTON_SIZE / 2),
        sf::Vector2f(BUTTON_SIZE * 0, 0),
        sf::Color(130, 78, 100, 255),
        sf::Color(255, 255, 255, 255),
        10, "EXIT"));
    if (1 /*создать игроков или одного*/) {
        for (int i = 0; i < 3; i++) {
            players.push_back(Player(map, window, 0, i + 3, "Jojo", projectile,time, particlesF, projectileBufer));
            //std::cout << "Player add:" << i + 3 << std::endl;
        }
        for (int i = 0; i < 3; i++) {
            players.push_back(Player(map, window, 1, i + 6, "Jojo", projectile,time, particlesF, projectileBufer));
            //std::cout << "Player add:" << i + 6 << std::endl;
        }
    }
    else
    players.push_back(Player(map, window, 1, 3, "Jojo", projectile,time,particlesF, projectileBufer));

    
    while (window.isOpen()) {
        if (needClose) {
            // Завершаем поток myThread

            {

                std::lock_guard<std::mutex> lock(mutex);
                std::cout << "thread close " << '\n';
                map.clear();
                //projectile.clear();
                players.clear();
                particlesF.clear();

            }
            myThreadParticlesCleaner.join();
            myThreadPhysics.join();
            myThreadProjectileCollision.join();

            


             needClose = false;
            break;
        }

        
        time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;
        update();
        render();

    }
}
    




void LandScape::update() {
    handleEvents();
    //scanCollisionProjectile();

    timeSecond += time;
    if (timeSecond >=1000) {
        timeLeft--;
        if (timeLeft <=0) {
            indexPlayer++;
            if (indexPlayer >= players.size() - 1) {
                indexPlayer = 0;
            }
            timeLeft = 60;
        }
        timeSecond = 0;
        
    }
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
            else players[i].update(0);
        }
        for (auto& par : particlesF) if (!par.getStatus()) par.update();
    }

}
void LandScape::ParticlesCleaner() {
    while (!needClose) {
        //if (!projectile.empty()) {
        //    bool flag = rand() % (1 + 1);
        //    if (flag)particlesF.push_back(Particles(1, projectile[0].getCoordinate().x, projectile[0].getCoordinate().y, time, ""));
        //}
        if (projectile.empty()) {
            if (particlesF.size() > 2 && particlesF[1].getStatus()) {
                //particlesF.erase(particlesF.begin()+1);
                particlesF.clear();
                if (particlesF.empty()) std::cout << "Particles clear" << std::endl;
            }
        }
        std::cout << "Particles size: " << particlesF.size() << '\n';
        
    }
}
void LandScape::render()
{
    window.clear();
    drawMap();
    for (auto& but : buttons) but.render(window);
    {
        //std::lock_guard<std::mutex> lock(mutex);
        if (!projectile.empty()) {
            projectile[0].render(window);
        }
        for (auto& par : particlesF) if (!par.getStatus())par.render(window);
        for (int i = 0; i < players.size(); i++) {
            players[i].render((i == indexPlayer) ? 1 : 0);
        }
    }
    timeLeftText.setString(std::to_string(timeLeft));
    timeLeftText.setPosition(sf::Vector2f(WINDOW_W/2, 10));
    timeLeftText.setFont(font);
    timeLeftText.setCharacterSize(50);
    timeLeftText.setFillColor(sf::Color::Red);
    window.draw(timeLeftText);
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
        // Преобразуем позицию мыши в координаты карты
        int mapX = mousePosition.x / BLOCK_SIZE;
        int mapY = mousePosition.y / BLOCK_SIZE;
        mousePosX=mapX;
        mousePosY=mapY;
        

        //// Обработка нажатия левой кнопки мыши
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            // Получаем позицию мыши относительно окна
            sf::Vector2f localPosition(event.mouseButton.x, event.mouseButton.y);
            for (auto& x : buttons) {
                if (x.getRectangle().getGlobalBounds().contains(localPosition)) {
                    std::string str = x.getString();
                    if (str == "EXIT") {
                        needClose = true;
                        return;
                    }
                }
            }
            // Создаем снаряд
            {
                std::lock_guard<std::mutex> lock(mutex);
                //particlesF.push_back(Particles(1, mapX, mapY, time, ""));
                if(projectile.empty())
                projectileBufer.push_back(Projectile(mapX, mapY, 0.1f, -0.1f, 1000, time, particlesF));
            }

        }
        

    }
    
}

//поток обработки контакта 
void LandScape::scanCollisionProjectile() {
    while (!needClose) {
        if (!projectileBufer.empty()) {
            Projectile prBuf = projectileBufer[0];
            projectile.push_back(prBuf);
            projectileBufer.clear();
        }
        if (!projectile.empty()) {
            Projectile& pr = projectile[0];

            //if (!pr.isExplosion()) {
            vt positionPr = pr.getCoordinate();
            int sizePr = pr.getSize();
            float radiusPr = pr.getRadius();
            bool exp = false;

            for (auto& pl : players) {
                if (pl.scanContactProjectile(radiusPr, positionPr)) {
                    exp = true;
                    pr.explosions();
                }
            }

            if (!exp) {
                if (positionPr.x >= 1 && positionPr.x < map[0].size() - 1 && positionPr.y >= 1 && positionPr.y < map.size() - 1) {
                    if (map[positionPr.y][positionPr.x] > 0) {
                        pr.explosions();
                        exp = true;
                        {
                            std::lock_guard<std::mutex> lock(mutex);
                            explosion(vt(positionPr.y, positionPr.x), radiusPr);
                        }
                    }
                }
                else {
                    pr.outOfMap();
                    exp = true;
                }
            }

            if (!exp) {
                //std::lock_guard<std::mutex> lock(mutex);
                pr.update();

            }
            else {
                std::lock_guard<std::mutex> lock(mutex);
                projectile.erase(projectile.begin());
            }
        }
    }

}


        
    
