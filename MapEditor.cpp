#include "MapEditor.h"
#include <ctime>  // Для использования time
#include <fstream>

#define randoms(a, b) (rand() % ((b) - (a) + 1) + (a))

MapEditor::MapEditor(sf::RenderWindow& windows) : Map(windows)
{
    map.resize(WINDOW_H / BLOCK_SIZE, std::vector<int>(WINDOW_W / BLOCK_SIZE, 0));
    isLeftMouseButtonPressed = false;
    isRightMouseButtonPressed = false;
}

void MapEditor::run() {
    bool tapButton = false;
    loadMapFromFile();
    for (int i = 0; i < 4; i++) {
        buttons.push_back(Button(sf::Vector2f(BUTTON_SIZE, BUTTON_SIZE / 2),
            sf::Vector2f(BUTTON_SIZE * i, 0),
            sf::Color(130, 78, 100, 255),
            sf::Color(255, 255, 255, 255),
            10, namesButton[i]));
    }
    buttons.push_back(Button(sf::Vector2f(BUTTON_SIZE * 3, BUTTON_SIZE / 2),
        sf::Vector2f(BUTTON_SIZE, BUTTON_SIZE / 2),
        sf::Color(130, 78, 100, 255),
        sf::Color(255, 255, 255, 255),
        10, namesTypePaint[0]));

    while (window.isOpen()) {
        handleEvents();
        if (needClose) {
            saveMapToFile();
            needClose = false;
            return;
        }
        update();
        render();
    }
    saveMapToFile();
}

void MapEditor::saveMapToFile() {
    std::ofstream outFile("map.txt");

    if (outFile.is_open()) {
        for (int x = 0; x < map.size(); ++x) {
            for (int y = 0; y < map[x].size(); ++y) {
                outFile << map[x][y] << " ";
            }
            outFile << std::endl; // Переход на новую строку после каждой строки карты
        }

        outFile.close();
    }
    else {
        // Обработка ошибки открытия файла
        std::cerr << "Error: Unable to open the file." << std::endl;
    }
}

void MapEditor::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f localPosition(event.mouseButton.x, event.mouseButton.y);
                for (auto& x : buttons) {
                    if (x.getRectangle().getGlobalBounds().contains(localPosition)) {
                        std::string str = x.getString();
                        if (str == "SAVE") {
                            needClose = true;
                            tapButton = true;
                        }
                        else if (str == "PREV") {
                            paintType--;
                            if (paintType < 0) paintType = 1;
                            tapButton = true;
                        }
                        else if (str == "NEXT") {
                            paintType++;
                            if (paintType > 1) paintType = 0;
                            tapButton = true;
                        }
                        else if (str == "CLEAR") {
                            map.clear();
                            map.resize(WINDOW_H / BLOCK_SIZE, std::vector<int>(WINDOW_W / BLOCK_SIZE, 0));
                            tapButton = true;
                        }
                    }
                }
                if (!tapButton) {
                    isLeftMouseButtonPressed = true;
                }
            }
            else if (event.mouseButton.button == sf::Mouse::Right) {
                isRightMouseButtonPressed = true;
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                isLeftMouseButtonPressed = false;
                tapButton = false;
            }
            else if (event.mouseButton.button == sf::Mouse::Right) {
                isRightMouseButtonPressed = false;
            }
        }
    }

    if (isLeftMouseButtonPressed || isRightMouseButtonPressed) {
        // Координаты мыши и преобразование их в индексы матрицы карты
        int y = sf::Mouse::getPosition(window).x / BLOCK_SIZE;
        int x = sf::Mouse::getPosition(window).y / BLOCK_SIZE;
        
        // Установите значение 1 или 0 в выбранной клетке
        if (y >= 0 && y < map[0].size() && x >= 0 && x < map.size()) {
            map[x][y] = (isLeftMouseButtonPressed) ? paintType + 1 : 0;
        }
    }
}

void MapEditor::update() {
    bool hasBlocksReachedBottom = false;

    for (int x = map.size() - 1; x > 0; --x) {
        for (int y = 0; y < map[x].size(); ++y) {
            if (map[x][y] == 2) {
                // Возможно, здесь должна быть какая-то логика для случая map[x][y] == 2
            }
            else if (map[x][y] > 0 && x < map.size() - 1 && map[x + 1][y] == 0) {
                map[x + 1][y] = map[x][y];
                map[x][y] = 0;
                hasBlocksReachedBottom = true;
            }
        }
    }

    if (hasBlocksReachedBottom) {
        for (int x = map.size() - 1; x > 0; --x) {
            for (int y = 0; y < map[x].size(); ++y) {
                if (map[x][y] == 2) {
                    // Возможно, здесь должна быть какая-то логика для случая map[x][y] == 2
                }
                else if (map[x][y] > 0 && x < map.size() - 1) {
                    if (y > 0 && map[x + 1][y] > 0 && map[x + 1][y - 1] == 0) {
                        map[x + 1][y - 1] = map[x][y];
                        map[x][y] = 0;
                    }
                    else if (y < map[x].size() - 1 && map[x + 1][y] > 0 && map[x + 1][y + 1] == 0) {
                        map[x + 1][y + 1] = map[x][y];
                        map[x][y] = 0;
                    }
                    else if (map[x + 1][y] == 0) {
                        map[x + 1][y] = map[x][y];
                        map[x][y] = 0;
                    }
                }
            }
        }
    }
}

void MapEditor::render() {
    window.clear();
    buttons[4].setText(namesTypePaint[paintType]);
    for (auto& but : buttons) {
        but.render(window);
    }

    // Отрисовка заполненных клеток
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