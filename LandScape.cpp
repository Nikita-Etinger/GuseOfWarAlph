#include "Classes.h"



LandScape::LandScape(sf::RenderWindow& windows) : Map(windows)
{
    map.resize(WINDOW_H / BLOCK_SIZE, std::vector<int>(WINDOW_W / BLOCK_SIZE, 0));
    mapTexture.create(WINDOW_W, WINDOW_H);

}

void LandScape::run()
{

    loadMapFromFile();
    if (1 /*создать игроков или одного*/) {
        for (int i = 0; i < 10; i++) {
            players.push_back(Player(map, window, 0, i + 3, "Jojo", projectile));
            std::cout << "Player add:" << i + 3 << std::endl;
        }
        for (int i = 0; i < 10; i++) {
            players.push_back(Player(map, window, 1, i + 6, "Jojo", projectile));
            std::cout << "Player add:" << i + 6 << std::endl;
        }
    }
    else
    players.push_back(Player(map, window, 1, 3, "Jojo", projectile));

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

    // Проверяем флаг flagUpdate и обновляем текстуру при необходимости
    /*flagUpdate = 1;*/
    if (flagUpdate) {
        updateMapTexture();
        flagUpdate = 0; // Сбрасываем флаг после обновления текстуры
    }

    // Отображаем карту из текстуры на окне
    window.draw(mapSprite);

    update();
    window.display();
}

void LandScape::handleEvents()
{
    std::cout << "mouseX: " << mousePosX << " mouseY: " << mousePosY << std::endl;
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
        

        //// Обработка нажатия левой кнопки мыши для создания снаряда (ожидает реализации)
        //if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        //    // Получаем позицию мыши относительно окна
        //    
        //    // Создаем снаряд и добавляем его в вектор
        //    if (!projectile.size()) {
        //        /*Projectile newProjectile(getMap(), players, 10, 10, 0.5, mapY, mapX);
        //        projectile.push_back(newProjectile);*/
        //    }
        //    else if (projectile[0].getStatus()) {
        //        projectile.clear();
        //    }
        //}
        

    }
    
}
std::vector<std::vector<int>>& LandScape::getMap() {
    return map;
}
void LandScape::updateMapTexture()
{
    mapTexture.clear(sf::Color::Transparent); // Очищаем текстуру

    for (int x = 0; x < map.size(); ++x) {
        for (int y = 0; y < map[x].size(); ++y) {
            int value = map[x][y];
            if (value >= 0 && value <= 2) {
                sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
                block.setPosition(y * BLOCK_SIZE, (map.size() - x - 1) * BLOCK_SIZE);
                block.setFillColor(colors[value - 1]);
                /*block.setFillColor((value >= 1 && value <= 2)?colors[value - 1]:sf::Color::Black);*/
                /*block.setOutlineThickness(1);*/
                mapTexture.draw(block); // Рисуем блоки на текстуре
            }
        }
    }
    mapSprite.setTexture(mapTexture.getTexture()); // Устанавливаем текстуру из буфера на спрайт
}