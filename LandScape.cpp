#include "LandScape.h"


LandScape::LandScape(sf::RenderWindow& windows) : Map(windows)
{
    map.resize(WINDOW_H / BLOCK_SIZE, std::vector<int>(WINDOW_W / BLOCK_SIZE, 0));

}

void LandScape::run()
{

    loadMapFromFile();
    //for (int i = 0; i < 3; i++) {
    //    players.push_back(Player(map, window, 0, i+3, "Jojo"));
    //    std::cout << "Player add:" << i+3 << std::endl;
    //}
    //for (int i = 0; i < 3; i++) {
    //    players.push_back(Player(map, window, 1, i+6, "Jojo"));
    //    std::cout << "Player add:" << i + 6 << std::endl;
    //}
    players.push_back(Player(map, window, 1, 3, "Jojo"));

    while (window.isOpen()) {
        handleEvents();
        //update();
        render();
    }
}


void LandScape::update()
{
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
    
    for (auto& but : buttons) {
        but.render(window);
    }
    // Отрисовка заполненных клеток
    for (int x = 0; x < map.size(); ++x) {
        for (int y = 0; y < map[x].size(); ++y) {
            int value = map[x][y];
            if (value >= 1 && value <= 8) {
                sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
                block.setPosition(y * BLOCK_SIZE, x * BLOCK_SIZE);
                block.setFillColor(colors[value - 1]);
                block.setOutlineThickness(1);
                window.draw(block);
            }
            //else {
            //    sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
            //    block.setPosition(y * BLOCK_SIZE, x * BLOCK_SIZE);
            //    block.setFillColor(sf::Color::Black);
            //    block.setOutlineThickness(1);
            //    window.draw(block);
            //}
        }
    }
    update();
    window.display();
}

void LandScape::handleEvents()
{
    std::cout << "X: " << mousePosX << " Y: " << mousePosY << std::endl;
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
        // Преобразуем позицию мыши в координаты карты
        int mapX = mousePosition.x / BLOCK_SIZE;
        int mapY = mousePosition.y / BLOCK_SIZE;
        mousePosX=mapX;
        mousePosY=mapY;
        

        // Обработка нажатия левой кнопки мыши для создания снаряда (ожидает реализации)
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            // Получаем позицию мыши относительно окна
            



            /*std::cout << "X: " << mapX << " Y: " << mapY << std::endl;*/
            // Создаем снаряд и добавляем его в вектор
            if (!projectile.size()) {
                /*Projectile newProjectile(getMap(), players, 10, 10, 0.5, mapY, mapX);
                projectile.push_back(newProjectile);*/
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