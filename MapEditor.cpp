#include "MapEditor.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#define randoms(a, b) (rand() % ((b) - (a) + 1) + (a))


MapEditor::MapEditor(sf::RenderWindow& windows):window(windows)
{
    map.resize(WINDOW_H / BLOCK_SIZE, std::vector<int>(WINDOW_W / BLOCK_SIZE, 0));
    isLeftMouseButtonPressed = false;
    isRightMouseButtonPressed = false;
    
   
}

void MapEditor::run() {
    loadMapFromFile();
    buttons.push_back(Button(sf::Vector2f(BUTTON_SIZE, BUTTON_SIZE/2),
        sf::Vector2f(window.getSize().x-BUTTON_SIZE-2, 0),
        sf::Color::Color(130, 78, 100, 255),
        sf::Color::Color(255, 255, 255, 255),
        10,"SAVE"));
    //srand(time(NULL));
    while (window.isOpen()) {
        handleEvents();
        if (needClose) {
            saveMapToFile();
            needClose = 0;
            return;
        }
        update();
        render();
    }
    saveMapToFile();
}
void MapEditor::colorMenu() {







}
void MapEditor::saveMapToFile() {
    std::ofstream outFile("map.txt");

    if (outFile.is_open()) {
        for (int y = 0; y < map.size(); ++y) {
            for (int x = 0; x < map[y].size(); ++x) {
                outFile << map[y][x] << " ";
            }
            outFile << std::endl; // Переход на новую строку после каждой строки карты
        }

        outFile.close();
    }
    else {
        // Обработка ошибки открытия файла
    }
}
void MapEditor::loadMapFromFile() {
    std::ifstream inFile("map.txt");

    if (inFile.is_open()) {
        // Очистите текущую карту перед загрузкой
        map.clear();

        std::string line;
        while (std::getline(inFile, line)) {
            std::vector<int> row;
            std::istringstream iss(line);
            int value;

            while (iss >> value) {
                row.push_back(value);
            }

            map.push_back(row);
        }

        inFile.close();
    }
    else {
        // Обработка ошибки открытия файла
    }
}
void MapEditor::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        else if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f localPosition(event.mouseButton.x, event.mouseButton.y);
            if (buttons[0].getRectangle().getGlobalBounds().contains(localPosition)) {
                needClose = 1;
                return;
            }
            if (event.mouseButton.button == sf::Mouse::Left) {
                isLeftMouseButtonPressed = true;
            }
            else if (event.mouseButton.button == sf::Mouse::Right) {
                isRightMouseButtonPressed = true;
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                isLeftMouseButtonPressed = false;
            }
            else if (event.mouseButton.button == sf::Mouse::Right) {
                isRightMouseButtonPressed = false;
            }
        }
    }

    if (isLeftMouseButtonPressed || isRightMouseButtonPressed) {
        // Получите координаты мыши и преобразуйте их в индексы матрицы карты
        int x = sf::Mouse::getPosition(window).x / BLOCK_SIZE;
        int y = sf::Mouse::getPosition(window).y / BLOCK_SIZE;

        // Установите значение 1 или 0 в выбранной клетке
        if (x >= 0 && x < map[0].size() && y >= 0 && y < map.size()) {

            int color = randoms(1, 4);
            std::cout << color;
            map[y][x] = (isLeftMouseButtonPressed) ? /*color*/1 : 0;
        }
    }
}

void MapEditor::update() {
    bool hasBlocksReachedBottom = false;

    for (int y = map.size() - 1; y > 0; --y) {
        for (int x = 0; x < map[y].size(); ++x) {
            if (map[y][x] > 0 && y < map.size() - 1 && map[y + 1][x] == 0) {
                map[y + 1][x] = map[y][x];
                map[y][x] = 0;
                hasBlocksReachedBottom = true;
            }
        }
    }

    if (hasBlocksReachedBottom) {
        for (int y = map.size() - 1; y > 0; --y) {
            for (int x = 0; x < map[y].size(); ++x) {
                if (map[y][x] > 0 && y < map.size() - 1) {
                    if (x > 0 && map[y + 1][x] > 0 && map[y + 1][x - 1] == 0) {
                        map[y + 1][x - 1] = map[y][x];
                        map[y][x] = 0;
                    }
                    else if (x < map[y].size() - 1 && map[y + 1][x] > 0 && map[y + 1][x + 1] == 0) {
                        map[y + 1][x + 1] = map[y][x];
                        map[y][x] = 0;
                    }
                    else if (map[y + 1][x] == 0) {
                        map[y + 1][x] = map[y][x];
                        map[y][x] = 0;
                    }
                }
            }
        }
    }
}

void MapEditor::render() {
    window.clear();
    for (auto & but : buttons) {
        but.render(window);
    }
    // Отрисовка заполненных клеток
    for (int y = 0; y < map.size(); ++y) {
        for (int x = 0; x < map[y].size(); ++x) {
            int value = map[y][x];
            if (value >= 1 && value <= 4) {
                sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
                block.setPosition(x * BLOCK_SIZE, y * BLOCK_SIZE);
                block.setFillColor(colors[value - 1]); // Используйте соответствующий цвет из массива
                window.draw(block);
            }
        }
    }

    window.display();
}