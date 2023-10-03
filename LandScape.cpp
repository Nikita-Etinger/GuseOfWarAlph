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
    //std::thread myThreadUpdateProjectile([this]() {
    //    
    //    updateProjectile();
    // });
    //
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
            //myThreadUpdateProjectile.join();

            


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

    timeSecond += time;
    if (timeSecond >=1000) {
        timeLeft--;
        if (timeLeft <=0) {
            indexPlayer++;
            if(!players[indexPlayer].isLive())indexPlayer++;
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
                    timeLeft = 60;
                    if (!players[indexPlayer].isLive())indexPlayer++;
                    if (indexPlayer >= players.size() - 1) {
                        indexPlayer = 0;
                    }
                }
            }
            else players[i].update(0);
        }
        for (auto& par : particlesF) if (!par.getStatus()) par.update();
    }
    if (!projectileBufer.empty()) {
        Projectile prBuf = projectileBufer[0];
        projectile.push_back(prBuf);
        projectileBufer.clear();
    }
    if (!projectile.empty()){
        if (projectile[0].isExplosion()) {
            for (auto& pl : players) {
                pl.scanContactProjectile(projectile[0].getRadius(), projectile[0].getCoordinate());
            }
            explosion(sf::Vector2f(projectile[0].getCoordinate().y, projectile[0].getCoordinate().x), projectile[0].getRadius());
            projectile.clear();
        }
        else {
            projectile[0].update();
        }
    }

}
void LandScape::ParticlesCleaner() {
    while (!needClose) {
        if (projectile.empty()) {
            
            if (particlesF.size() > 2 &&particlesF[particlesF.size()-1].getStatus()) {
                //particlesF.erase(particlesF.begin()+1);
                particlesF.clear();
                if (particlesF.empty()) std::cout << "Particles clear" << std::endl;
            }
        }
        //std::cout << "Particles size: " << particlesF.size() << '\n';
        
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
                if(projectile.empty())
                projectileBufer.push_back(Projectile(mapX, mapY, 0.5f, -0.6f, 1000, time, particlesF,map));
            }
        }
    }
    
}

//поток обработки контакта 
void LandScape::updateProjectile() {
    while (!needClose) {
        /*if(!projectile.empty())
        projectile[0].update();*/
    }

}


        
    
