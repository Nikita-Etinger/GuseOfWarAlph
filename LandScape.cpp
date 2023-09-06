#include "LandScape.h"


LandScape::LandScape(sf::RenderWindow& windows) : Map(windows)
{
    map.resize(WINDOW_H / BLOCK_SIZE, std::vector<int>(WINDOW_W / BLOCK_SIZE, 0));

}

void LandScape::run()
{

    loadMapFromFile();
    players.push_back(Player(map,  window, 1, 3, "Jojo"));

    while (window.isOpen()) {
        handleEvents();
        update();
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
    // ��������� ����������� ������
    for (int x = 0; x < map.size(); ++x) {
        for (int y = 0; y < map[x].size(); ++y) {
            int value = map[x][y];
            if (value >= 1 && value <= 4) {
                sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
                block.setPosition(y * BLOCK_SIZE, x * BLOCK_SIZE);
                block.setFillColor(colors[value - 1]);
                window.draw(block);
            }
        }
    }

    window.display();
}

void LandScape::handleEvents()
{
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

        // ��������� ������� ����� ������ ���� ��� �������� �������
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            // �������� ������� ���� ������������ ����
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

            // ����������� ������� ���� � ���������� �����
            int mapX = mousePosition.x / BLOCK_SIZE;
            int mapY = mousePosition.y / BLOCK_SIZE;

            std::cout << "X: " << mapX << " Y: " << mapY << std::endl;
            // ������� ������ � ��������� ��� � ������
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